#ifndef MINWHITEBOARD_H
#define MINWHITEBOARD_H

#include <QWidget>
#include "Public/public_function.h"
#include "Extern/extern.h"
#include "minwhiteboard_view.h"

namespace Ui {
class MinWhiteboard;
}

class MinWhiteboard : public QWidget
{
    Q_OBJECT

public:
    explicit MinWhiteboard(QWidget *parent = nullptr);
    ~MinWhiteboard();
    void resizeWidget();
    void setTool(MinWhiteBoard_View::ViewTool tool);
    void clearScene();

private:
    Ui::MinWhiteboard *ui;
    MinWhiteBoard_View *m_BoardView;

    void initWidget();
};

#endif // MINWHITEBOARD_H
