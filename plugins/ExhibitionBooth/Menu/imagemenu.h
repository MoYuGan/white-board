#ifndef IMAGEMENU_H
#define IMAGEMENU_H

#include <QWidget>
#include <QPainter>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QDateTime>
#include <QScroller>
#include "Public/publicfunction.h"
#include "Custom/PushButton/custompushbutton_2.h"
#include "Extern/extern.h"
#include "Custom/PushButton/custompushbutton_5.h"
#include "ExportFile/exportfile.h"

namespace Ui {
class ImageMenu;
}

class ImageMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ImageMenu(QWidget *parent = 0);
    ~ImageMenu();
    void resize();
    int getBorder();
    void showSaveWidget(bool bo);
    void setContastModel(bool bo);
    void addItem(const QPixmap &pixmap);
    void addCameraItem(const QString &deviceName);
    void clearCameraItem();
    int getItemSize();
    void getPixmap(int id, QPixmap *pixmap, int *angle);
    int getCheckedIndex();
    int getCheckedNum();
    int getAllCheckedNum();
    void clearChecked();
    void rotateItem(int id, int angle);
    void setItemChecked(int index);
    void setCameraItemChecked(int index, bool checked);
    void setCameraItemEnabled(bool enabled);
    void showImageList();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ImageMenu *ui;
    QList<CustomPushButton_2 *> m_BtnList;
    QList<CustomPushButton_5 *> m_CameraBtnList;
    CustomPushButton_2 *m_CheckedButton = nullptr;
    CustomPushButton_5 *m_CheckedCameraButton = nullptr;
    bool m_IsContast = false;
    QList<QPixmap> m_PixmapList;

    void initWidget();
    void selectedImageNumChanged(int);

private slots:
    void addLocalPicture();
    void onItemDelete();
    void onItemChecked(bool checked);
    void onCameraItemChecked(bool checked);
    void onCheckBoxClicked();
    void onSaveBtnClicked();

signals:
    void itemNumChanged();
    void itemChecked(bool, int);
    void itemDelete(int);
    void cameraChecked(bool, int);
};

#endif // IMAGEMENU_H
