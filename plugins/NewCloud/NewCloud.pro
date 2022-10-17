#-------------------------------------------------
#
# Project created by QtCreator 2021-04-19T09:13:52
#
#-------------------------------------------------

QT       += core gui sql network webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewCloud
#TEMPLATE = app
TEMPLATE = lib #将此工程生产库文件，以便主工程使用时调用库文件
CONFIG += plugin #添加插件配置信息
DESTDIR +=../lib #将生产的文件放入指定的位置，每次有新的生成会覆盖旧的
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lqrencode #QrCode (apt-get install libqrencode-dev)

SOURCES += \
    VirtualKeyBoard/keyboard.cpp \
        main.cpp \
    mycloud.cpp \
    customwidget.cpp \
    maininterface.cpp \
    mod_http/db_httpinterface.cpp \
    mod_http/db_httpthread.cpp \
    mod_http/db_httpworker.cpp

HEADERS += \
    VirtualKeyBoard/keyboard.h \
    cloudcoursewareinterface.h \
    mycloud.h \
    Public/public_function.h \
    custombtn.h \
    customwidget.h \
    maininterface.h \
    mod_http/db_httpinterface.h \
    mod_http/db_httpthread.h \
    mod_http/db_httpworker.h

FORMS += \
    VirtualKeyBoard/keyboard.ui \
    mycloud.ui \
    maininterface.ui

RESOURCES += \
    cloudpixmap.qrc
