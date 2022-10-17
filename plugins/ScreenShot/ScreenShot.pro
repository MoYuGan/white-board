QT       += core gui


TARGET = ScreenShot  #生成文件的名称
TEMPLATE = lib #将此工程生产库文件，以便主工程使用时调用库文件
CONFIG += plugin #添加插件配置信息
DESTDIR += ../lib #将生产的文件放入指定的位置，每次有新的生成会覆盖旧的
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    custom.cpp \
    main.cpp \
    screenshot.cpp

HEADERS += \
    Public/public_function.h \
    ScreenShotInterFace.h \
    custom.h \
    screenshot.h

FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Pixmap.qrc
