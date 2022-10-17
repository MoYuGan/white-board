#-------------------------------------------------
#
# Project created by QtCreator 2021-03-11T09:45:22
# 板中板
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Plateplate
#TEMPLATE = lib
TEMPLATE = app
CONFIG += plugin
DESTDIR += ../lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        plateplate.cpp \
    mainwidget.cpp \
    Custom/TabTools/tabtools_1.cpp \
    Custom/PushButton/custompushbutton_2.cpp \
    Custom/PushButton/custompushbutton_1.cpp \
    Custom/PushButton/custompushbutton.cpp \
    Custom/ToolBar/customtoolbar_1.cpp \
    main.cpp \
    Custom/GraphicsItem/customitem_pixmap.cpp \
    Draw/boardview.cpp \
    Draw/boardscene.cpp \
    Extern/extern.cpp \
    Panel/penpanel.cpp \
    Custom/PushButton/custompushbutton_3.cpp \
    Custom/PushButton/custompushbutton_4.cpp \
    Panel/eraserpanel.cpp \
    Custom/Slider/customslider_1.cpp \
    ToolBar/graphicsitem_toolbar.cpp \
    Custom/GraphicsItem/customitem_selectedrect.cpp \
    Custom/GraphicsItem/customitem_path.cpp \
    ExportFile/exportfile.cpp \
    Custom/Frame/customframe_1.cpp

HEADERS += \
        plateplate.h \
    plateplate_interface.h \
    mainwidget.h \
    Custom/TabTools/tabtools_1.h \
    Custom/PushButton/custompushbutton_2.h \
    Custom/PushButton/custompushbutton_1.h \
    Custom/PushButton/custompushbutton.h \
    Custom/ToolBar/customtoolbar_1.h \
    Public/publicfunction.h \
    Custom/GraphicsItem/customitem_selectedrect.h \
    Custom/GraphicsItem/customitem_path.h \
    Custom/GraphicsItem/customitem_pixmap.h \
    Draw/boardview.h \
    Draw/boardscene.h \
    Extern/extern.h \
    Panel/penpanel.h \
    Custom/PushButton/custompushbutton_3.h \
    Custom/PushButton/custompushbutton_4.h \
    Panel/eraserpanel.h \
    Custom/Slider/customslider_1.h \
    ToolBar/graphicsitem_toolbar.h \
    ExportFile/exportfile.h \
    Custom/Frame/customframe_1.h

DISTFILES += Plateplate.json 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    mainwidget.ui \
    Panel/penpanel.ui \
    Panel/eraserpanel.ui \
    ToolBar/graphicsitem_toolbar.ui \
    ExportFile/exportfile.ui

RESOURCES += \
    resource.qrc

TRANSLATIONS += Pzh.ts \
                Pen.ts
