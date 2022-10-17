QT       += core gui multimediawidgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = VideoPlayer
#TEMPLATE = app
TEMPLATE = lib
CONFIG += plugin
DESTDIR += ../lib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customcontrol.cpp \
    main.cpp \
    mainwindow.cpp \
    toolwidget.cpp \
    videoplayerwork.cpp

HEADERS += \
    Public/public_function.h \
    VideoPlayerInterFace.h \
    customcontrol.h \
    mainwindow.h \
    toolwidget.h \
    videoplayerwork.h

FORMS += \
    mainwindow.ui \
    toolwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Pixmap.qrc

#sudo apt install libvlc-dev
INCLUDEPATH =.vlc
LIBS+= -lvlc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lvlc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lvlc
else:unix: LIBS += -L$$PWD/./ -lvlc

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
