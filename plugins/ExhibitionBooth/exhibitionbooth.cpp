#include "exhibitionbooth.h"
#include <QtDebug>

ExhibitionBooth::ExhibitionBooth(QObject *parent) :
    ExhibitionBooth_Interface(parent)
{
}

QWidget *ExhibitionBooth::create(QWidget *parent, const QString &closeSlotFunction)
{
    //static MainWidget *widget = nullptr;
    //if (nullptr == widget) {
        e_EmbeddedToWhiteBoard = true;
        m_MainWidget = new MainWidget(parent);
        connect(m_MainWidget, SIGNAL(hideWidget()), parent, closeSlotFunction.toLatin1().data());
    //}
        return m_MainWidget;
}

void ExhibitionBooth::showWidget()
{
    if (nullptr != m_MainWidget)
        m_MainWidget->show();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ExhibitionBooth, ExhibitionBooth)
#endif // QT_VERSION < 0x050000
