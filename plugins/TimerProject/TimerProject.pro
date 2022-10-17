QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = TimerProject
#TEMPLATE = app
TEMPLATE = lib
CONFIG += plugin
DESTDIR += ../lib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    downwidget.cpp \
    downwork.cpp \
    main.cpp \
    mainwindow.cpp \
    timerinterface.cpp \
    timerwidget.cpp \
    timerwork.cpp

HEADERS += \
    NumberWidget.h \
    Public/public_function.h \
    TimerPlugin.h \
    downwidget.h \
    downwork.h \
    mainwindow.h \
    timerinterface.h \
    timerwidget.h \
    timerwork.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Pixmap.qrc
