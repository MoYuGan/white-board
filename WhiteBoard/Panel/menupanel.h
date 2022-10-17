#ifndef MENUPANEL_H
#define MENUPANEL_H

#include <QWidget>
#include <QPainter>
#include "Public/public_function.h"
#include "applicationconfig.h"
#include "menupanel_export.h"
#include "GlobalSignal/globalsignal.h"
#include <QButtonGroup>

namespace Ui {
class MenuPanel;
}

class MenuPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPanel(QWidget *parent = 0);
    ~MenuPanel();
    void resizeWidget();
    void show();
    void hide();
    bool isSaveEnabled();
    void disableSet();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MenuPanel *ui;
    MenuPanel_Export *m_ExportPanel;
    QButtonGroup *group;

    void initWidget();
    void updateLanguage();
private slots:
    void onBtnExportToggled(bool checked);

signals:
    void panelHide();
    void newBoard();
    void openFile();
    void exportToFile(int);
    void showAboutUs();
    void exitApplication();
    void sendSetBoardSignal();
    void toggleLanguage(bool isUseChinese);
};

#endif // MENUPANEL_H
