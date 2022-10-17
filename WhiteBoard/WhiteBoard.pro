#-------------------------------------------------
#
# Project created by QtCreator 2020-08-10T08:49:11
#
#-------------------------------------------------

QT  += core gui printsupport network
QT  += multimedia multimediawidgets         # QCamera
#QT += script
#QT  += qml quick quickwidgets            #virtualkeyboard
unix:!macx: {
    QT += x11extras
}

QTPLUGIN += qtvirtualkeyboardplugin         #virtualkeyboard
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmdoxBoard
TEMPLATE = app
DESTDIR += ../bin


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
unix:!macx: {
    DEFINES += IS_UNIX
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

##################   FLAGS   ####################
#解决MSVC编译时编码格式报错
msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
unix:!macx: {
    QMAKE_CXXFLAGS += -fno-pie -no-pie
}




##################   INCLUDE ####################
#INCLUDEPATH += $$PWD/../plugins
#INCLUDEPATH += $$PWD/include

###################   LIBS   #######################
unix:!macx: {
LIBS += -lX11 -lXext
LIBS += -L$$PWD/../libs/mupdf/ -lmupdf  # sudo apt-get install mupdf mupdf-tools  is not fit
LIBS+= -lhidapi-libusb #sudo apt install libhidapi-dev
}



###################   SOURCE  #######################
SOURCES += \
    Common/toolkit.cpp \
    Custom/Frame/frame_2.cpp \
    Custom/Label/label_1.cpp \
    Custom/PushButton/pushbutton_10.cpp \
    Custom/PushButton/pushbutton_11.cpp \
    Custom/PushButton/pushbutton_12.cpp \
    Custom/PushButton/pushbutton_13.cpp \
    Custom/PushButton/pushbutton_7.cpp \
    Custom/PushButton/pushbutton_8.cpp \
    Custom/PushButton/pushbutton_9.cpp \
    Custom/Widget/widget_2.cpp \
    CustomGraphicsItem/cubeitem.cpp \
    GlobalSignal/globalsignal.cpp \
    MiniBoard/checkminiboardnumber.cpp \
    MiniBoard/getpenworker.cpp \
    MiniBoard/getpointworker.cpp \
    MinimizedWhiteboard/minwhiteboard.cpp \
    MinimizedWhiteboard/minwhiteboard_erasetask.cpp \
    MinimizedWhiteboard/minwhiteboard_scene.cpp \
    MinimizedWhiteboard/minwhiteboard_view.cpp \
    Panel/backgroundstyle.cpp \
    Panel/setboard.cpp \
    Shape/Base/baseshapeobject.cpp \
    Shape/OperRecord/borderchangedrecord.cpp \
    Shape/OperRecord/fillchangedrecord.cpp \
    Shape/OperRecord/pathchangedrecord.cpp \
    Shape/OperRecord/poschangedrecord.cpp \
    Shape/OperRecord/recordmanager.cpp \
    Shape/OperRecord/rotatechangedrecord.cpp \
    Shape/OperRecord/shapeaddandremoverecord.cpp \
    Shape/OperRecord/zindexchanegedrecord.cpp \
    VersionUpdate/versionupdate.cpp \
    changebackgroundpixmapthread.cpp \
    main.cpp \
    mod_http/db_httpworker.cpp \
    mod_http/db_httpthread.cpp \
    mod_http/db_httpinterface.cpp \
    mod_draw/boardscene.cpp \
    mod_draw/boardview.cpp \
    drawingboard.cpp \
    mainwidget.cpp \
    mod_draw/ItemTool/itemtool.cpp \
    mod_draw/ItemTool/itemtool_borderpanel.cpp \
    mod_draw/ItemTool/itemtool_fillcolorpanel.cpp \
    mod_draw/ItemTool/itemtool_flippanel.cpp \
    mod_draw/ItemTool/itemtool_mirrorpanel.cpp \
    ExportFile/exportfile.cpp \
    Extern/extern.cpp \
    CustomGraphicsItem/ChiGui/customitem_zhichi.cpp \
    CustomGraphicsItem/ChiGui/customitem_zhijiao.cpp \
    CustomGraphicsItem/ChiGui/customitem_dengyao.cpp \
    CustomGraphicsItem/ChiGui/customitem_liangjiaoqi.cpp \
    CustomGraphicsItem/ChiGui/customitem_yuangui.cpp \
    Spotlight/light.cpp \
    Lockscreen/mylock.cpp \
    Veil/myveil.cpp \
    VirtualKeyBoard/keyboard.cpp \
    CustomGraphicsItem/pathitem.cpp \
    mod_draw/erasertask.cpp \
    Custom/PushButton/pushbutton_1.cpp \
    Custom/PushButton/pushbutton_2.cpp \
    Custom/PushButton/pushbutton_basic.cpp \
    Panel/graphicspanel.cpp \
    Panel/toolpanel.cpp \
    Panel/rulerpanel.cpp \
    Panel/penpanel.cpp \
    Custom/PushButton/pushbutton_3.cpp \
    Custom/PushButton/pushbutton_4.cpp \
    Panel/erasepanel.cpp \
    Panel/selectpanel.cpp \
    Panel/menupanel.cpp \
    Custom/PushButton/pushbutton_5.cpp \
    Panel/menupanel_export.cpp \
    Custom/Frame/frame_1.cpp \
    Panel/pagepanel.cpp \
    Custom/PushButton/pushbutton_6.cpp \
    initapplication.cpp \
    Custom/Widget/widget_1.cpp \
    Custom/MessageBox/messagebox_1.cpp \
    ToolPanel/db_colorpanel.cpp \
    CustomGraphicsItem/lineitem.cpp \
    CustomGraphicsItem/graphicsitem.cpp \
    CustomGraphicsItem/selectedrectitem.cpp \
    CustomGraphicsItem/pixmapitem.cpp


HEADERS += \
    Common/toolkit.h \
    Custom/Frame/frame_2.h \
    Custom/Label/label_1.h \
    Custom/PushButton/pushbutton_10.h \
    Custom/PushButton/pushbutton_11.h \
    Custom/PushButton/pushbutton_12.h \
    Custom/PushButton/pushbutton_13.h \
    Custom/PushButton/pushbutton_7.h \
    Custom/PushButton/pushbutton_8.h \
    Custom/PushButton/pushbutton_9.h \
    Custom/Widget/widget_2.h \
    CustomGraphicsItem/cubeitem.h \
    GlobalSignal/globalsignal.h \
    MiniBoard/checkminiboardnumber.h \
    MiniBoard/getpenworker.h \
    MiniBoard/getpointworker.h \
    MinimizedWhiteboard/minwhiteboar_pathitem.h \
    MinimizedWhiteboard/minwhiteboard.h \
    MinimizedWhiteboard/minwhiteboard_erasetask.h \
    MinimizedWhiteboard/minwhiteboard_scene.h \
    MinimizedWhiteboard/minwhiteboard_view.h \
    Panel/backgroundstyle.h \
    Panel/setboard.h \
    Public/CommonShapeData.h \
    Shape/Base/baseshapeobject.h \
    Shape/OperRecord/baserecord.h \
    Shape/OperRecord/borderchangedrecord.h \
    Shape/OperRecord/fillchangedrecord.h \
    Shape/OperRecord/pathchangedrecord.h \
    Shape/OperRecord/poschangedrecord.h \
    Shape/OperRecord/recordmanager.h \
    Shape/OperRecord/rotatechangedrecord.h \
    Shape/OperRecord/shapeaddandremoverecord.h \
    Shape/OperRecord/zindexchanegedrecord.h \
    ShareStyle/db_font.h \
    VersionUpdate/versionupdate.h \
    changebackgroundpixmapthread.h \
    mod_http/db_httpworker.h \
    CustomWidget/db_custompushbutton.h \
    CustomWidget/db_customwidget.h \
    mod_http/db_httpthread.h \
    mod_http/db_httpinterface.h \
    mod_draw/boardscene.h \
    mod_draw/boardview.h \
    ShareStyle/db_scale.h \
    drawingboard.h \
    applicationconfig.h \
    CustomWidget/db_customslider.h \
    mod_draw/graphic.h \
    aboutus.h \
    mainwidget.h \
    FileOperations/m_pdf.h \
    CustomGraphicsItem/customitem_fan.h \
    mod_draw/ItemTool/itemtool.h \
    Public/public_function.h \
    mod_draw/ItemTool/itemtool_borderpanel.h \
    mod_draw/ItemTool/itemtool_fillcolorpanel.h \
    mod_draw/ItemTool/itemtool_flippanel.h \
    mod_draw/ItemTool/itemtool_mirrorpanel.h \
    ExportFile/exportfile.h \
    CustomGraphicsItem/customitem_cube.h \
    Extern/extern.h \
    CustomGraphicsItem/ChiGui/customitem_zhichi.h \
    CustomGraphicsItem/ChiGui/customitem_zhijiao.h \
    CustomGraphicsItem/ChiGui/customitem_dengyao.h \
    CustomGraphicsItem/ChiGui/customitem_liangjiaoqi.h \
    CustomGraphicsItem/ChiGui/customitem_yuangui.h \
    Spotlight/light.h \
    Lockscreen/mylock.h \
    Veil/myveil.h \
    VirtualKeyBoard/keyboard.h \
    CustomGraphicsItem/pathitem.h \
    mod_draw/erasertask.h \
    Custom/PushButton/pushbutton_1.h \
    Custom/PushButton/pushbutton_2.h \
    Custom/PushButton/pushbutton_basic.h \
    Panel/graphicspanel.h \
    Panel/toolpanel.h \
    Panel/rulerpanel.h \
    Panel/penpanel.h \
    Custom/PushButton/pushbutton_3.h \
    Custom/PushButton/pushbutton_4.h \
    Panel/erasepanel.h \
    Panel/selectpanel.h \
    Panel/menupanel.h \
    Custom/PushButton/pushbutton_5.h \
    Panel/menupanel_export.h \
    Custom/Frame/frame_1.h \
    Panel/pagepanel.h \
    Custom/PushButton/pushbutton_6.h \
    initapplication.h \
    Custom/Widget/widget_1.h \
    Custom/MessageBox/messagebox_1.h \
    ToolPanel/db_colorpanel.h \
    CustomGraphicsItem/lineitem.h \
    CustomGraphicsItem/graphicsitem.h \
    CustomGraphicsItem/selectedrectitem.h \
    CustomGraphicsItem/pixmapitem.h

FORMS += \
    MinimizedWhiteboard/minwhiteboard.ui \
    Panel/backgroundstyle.ui \
    Panel/setboard.ui \
    VersionUpdate/versionupdate.ui \
    mainwidget.ui \
    mod_draw/ItemTool/itemtool.ui \
    mod_draw/ItemTool/itemtool_borderpanel.ui \
    mod_draw/ItemTool/itemtool_fillcolorpanel.ui \
    mod_draw/ItemTool/itemtool_flippanel.ui \
    mod_draw/ItemTool/itemtool_mirrorpanel.ui \
    ExportFile/exportfile.ui \
    VirtualKeyBoard/keyboard.ui \
    Panel/graphicspanel.ui \
    Panel/toolpanel.ui \
    Panel/rulerpanel.ui \
    Panel/penpanel.ui \
    Panel/erasepanel.ui \
    Panel/selectpanel.ui \
    Panel/menupanel.ui \
    Panel/menupanel_export.ui \
    Panel/pagepanel.ui \
    initapplication.ui \
    drawingboard.ui \
    Custom/MessageBox/messagebox_1.ui \
    ToolPanel/db_colorpanel.ui


RESOURCES += \
    pixmap.qrc

TRANSLATIONS += zh.ts \
                en.ts

CONFIG += resources_big
