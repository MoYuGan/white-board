#include "customtoolbar_1.h"
#include <QtDebug>

CustomToolBar_1::CustomToolBar_1(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->initWidget();
    m_CheckableButtonGroup = new QButtonGroup(this);
    m_CheckableButtonGroup->setExclusive(false);
}

CustomToolBar_1::~CustomToolBar_1()
{
    foreach (QHBoxLayout *layout, m_ActionLayout) {
        layout->deleteLater();
    }
}

void CustomToolBar_1::mAddAction(int id, const QString &text, const QPixmap &icon,
                                const QColor &textColor, const QColor &hoverColor,
                                bool isChecked, const QColor &checkedTextColor, const QPixmap &checkedIcon,
                                 const QColor &checkedColor)
{
    CustomPushButton_1 *button = new CustomPushButton_1(this);
    button->mSetText(text);
    button->mSetIcon(icon, checkedIcon);
    button->mSetTextColor(textColor, checkedTextColor);
    button->mSetColor(hoverColor, QColor(), checkedColor);
    connect(button, &CustomPushButton_1::clicked, [=](){ emit actionClicked(m_ActionBtnMap.key(button)); });
    connect(button, &CustomPushButton_1::checkedClicked, [=](){ emit actionCheckedClicked(m_ActionBtnMap.key(button)); });
    if (isChecked) {
        button->mEnabledChecked();
        m_CheckableButtonGroup->addButton(button);
        connect(button, &CustomPushButton_1::toggled, [=](bool checked) {
            QHBoxLayout *layout = m_ActionLayout.value(m_ActionBtnMap.key(button), nullptr);
            if (nullptr == layout)
                return;

            if (checked) {
                layout->setContentsMargins(0, m_ActionMarginTopChecked, 0, m_ActionMarginBottomChecked);
                button->setFixedHeight(this->height() - m_ActionMarginTopChecked - m_ActionMarginBottomChecked);
            }else {
                layout->setContentsMargins(0, m_ActionMarginTop, 0, m_ActionMarginBottom);
                button->setFixedHeight(this->height() - m_ActionMarginTop - m_ActionMarginBottom);
            }
            emit actionToggled(m_ActionBtnMap.key(button), checked);
        });
    }

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->setSpacing(0);
    hlayout->addWidget(button, 1, Qt::AlignCenter);

    if (m_ActionBtnMap.size() > 0)
        m_Layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    m_Layout->addLayout(hlayout);
    m_ActionLayout.insert(id, hlayout);
    m_ActionBtnMap.insert(id, button);
}

//设置圆角
void CustomToolBar_1::mSetRadius(int topLeft, int topRight, int bottomLeft, int bottomRight)
{
    m_TopLeftRadius = topLeft;
    m_TopRightRadius = topRight;
    m_BottomLeftRadius = bottomLeft;
    m_BottomRightRadius = bottomRight;
}

//设置透明边框（阴影部分）
void CustomToolBar_1::mSetTransparentBorder(int left, int top, int right, int bottom)
{
    m_TransparentBorderTop = top;
    m_TransparentBorderBottom = bottom;
    m_TransparentBorderLeft = left;
    m_TransparentBorderRight = right;
    m_Layout->setContentsMargins(m_MarginLeft + m_TransparentBorderLeft, 0, m_MarginRight + m_TransparentBorderRight, 0);

    m_MaxTransparentBorder = top;
    if (m_MaxTransparentBorder < left)
        m_MaxTransparentBorder = left;
    if (m_MaxTransparentBorder < right)
        m_MaxTransparentBorder = right;
    if (m_MaxTransparentBorder < bottom)
        m_MaxTransparentBorder = bottom;
}

//设置左右边距
void CustomToolBar_1::mSetMargin(int left, int right)
{
    m_MarginLeft = left;
    m_MarginRight = right;
    m_Layout->setContentsMargins(m_MarginLeft + m_TransparentBorderLeft, 0, m_MarginRight + m_TransparentBorderRight, 0);
}

/*
 * 设置Action的上下边距，
 * 参数一：unchecked时候的上边距，参数二：checked状态是的上边距，
 * 参数三：unchecked时候的下边距，参数四：checked状态是的下边距，
*/
void CustomToolBar_1::mSetActionMargin(int marginTop, int marginTopChecked, int marginBottom, int marginBottomChecked)
{
    m_ActionMarginTop = marginTop;
    m_ActionMarginTopChecked = marginTopChecked;
    m_ActionMarginBottom = marginBottom;
    m_ActionMarginBottomChecked = marginBottomChecked;
    foreach (QHBoxLayout *layout, m_ActionLayout) {
        if (m_ActionBtnMap.value(m_ActionLayout.key(layout))->isChecked())
            layout->setContentsMargins(0, marginTopChecked, 0, marginBottomChecked);
        else
            layout->setContentsMargins(0, marginTop, 0, marginBottom);
    }
}

void CustomToolBar_1::mSetActionSize(int fixWidth, const QSize &iconSize, int radius)
{
    foreach(CustomPushButton_1* button, m_ActionBtnMap.values()) {
        button->mSetIconSize(iconSize);
        button->setFixedWidth(fixWidth);
        if (button->isChecked()) {
            button->setFixedHeight(this->height() - m_ActionMarginTopChecked - m_ActionMarginBottomChecked);
        }else {
            button->setFixedHeight(this->height() - m_ActionMarginTop - m_ActionMarginBottom);
        }
        button->mSetRadius(radius);
        m_ActionLayout.value(m_ActionBtnMap.key(button))->setStretchFactor(button, 5);
    }
}

void CustomToolBar_1::mSetFont(const QFont &font)
{
    foreach(CustomPushButton_1* button, m_ActionBtnMap.values()) {
        button->mSetFont(font);
    }
}

void CustomToolBar_1::mSetExclusive(bool bo)
{
    m_CheckableButtonGroup->setExclusive(bo);
}

void CustomToolBar_1::mSetActionChecked(int id, bool bo)
{
    CustomPushButton_1* button = m_ActionBtnMap.value(id, nullptr);
    if (nullptr != button)
        button->setChecked(bo);
}

int CustomToolBar_1::mGetActionCenterX(int id)
{
    CustomPushButton_1* button = m_ActionBtnMap.value(id, nullptr);
    int x = 0;
    if (nullptr != button) {
        QPoint p = this->mapToParent(button->pos());
        x = p.x() + button->width()/2;
    }
    return x;
}

void CustomToolBar_1::mSetActionCheckedIcon(int id, const QPixmap &pixmap)
{
    CustomPushButton_1* button = m_ActionBtnMap.value(id, nullptr);
    if (nullptr != button)
        button->mSetCheckedIcon(pixmap);
}

void CustomToolBar_1::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::transparent);
    QColor color(135, 135, 135);
    int border = m_MaxTransparentBorder;
    for(int i = 0; i < border; i++)
    {
        QRect rect = QRect(QPoint(m_TransparentBorderLeft - i > 0 ? m_TransparentBorderLeft - i : 0,
                            m_TransparentBorderTop - i > 0 ? m_TransparentBorderTop - i : 0),
                           QPoint(this->width() - (m_TransparentBorderRight - i > 0 ? m_TransparentBorderRight - i : 0),
                            this->height() - (m_TransparentBorderBottom - i > 0 ? m_TransparentBorderBottom - i : 0)));

        QPainterPath path;
        path = PublicFunction::getRoundRectPath(rect, m_TopLeftRadius, m_TopRightRadius, m_BottomLeftRadius, m_BottomRightRadius);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }

        switch(i)
        {
        case 0:
            color.setAlpha(80);
            break;
        case 1:
            color.setAlpha(50);
            break;
        case 2:
            color.setAlpha(20);
            break;
        case 3:
            color.setAlpha(15);
            break;
        case 4:
            color.setAlpha(10);
            break;
        case 5:
            color.setAlpha(7);
            break;
        default:
            break;
        }
        QPen pen;
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void CustomToolBar_1::initWidget()
{
    m_Layout = new QHBoxLayout(this);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->setSpacing(0);
}
