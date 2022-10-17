#-------------------------------------------------
#
# Project created by QtCreator 2020-10-09T11:50:14
#
#-------------------------------------------------

QT       += core gui network
QT  += multimedia concurrent multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmdoxBooth
TRANSLATIONS += widgets_zh_cn.ts

TEMPLATE = app
#TEMPLATE = lib
#CONFIG += plugin
#DESTDIR += ../../../lib
#DESTDIR += ../lib
DESTDIR += ../bin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# OpenCV (apt-get install libopencv-dev)
LIBS += -lopencv_video  -lopencv_core   -lopencv_videoio  -lopencv_imgproc
#OCR (apt-get install libcurl4-openssl-dev)
LIBS += -lcurl

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Custom/MessageBox/messagebox_tip.cpp \
    Custom/Slider/c_slider.cpp \
    applicationstart.cpp \
    getupdatezip.cpp \
        main.cpp \
    Custom/PushButton/custompushbutton.cpp  \
    Custom/PushButton/custompushbutton_1.cpp \
    Custom/PushButton/custompushbutton_2.cpp \
    Custom/PushButton/custompushbutton_3.cpp \
    ToolBar/maintoolbar_left.cpp \
    Menu/mainmenu.cpp \
    Menu/resolutionmenu.cpp \
    Menu/devicesmenu.cpp \
    ToolBar/maintoolbar_midleft.cpp \
    ToolBar/maintoolbar_midright.cpp \
    mainwidget.cpp \
    ToolBar/maintoolbar_refore.cpp \
    ToolBar/maintoolbar_right.cpp \
    Menu/imagemenu.cpp \
    Custom/CustomLabel/customlabel.cpp \
    Custom/CustomWidget/customwidget.cpp \
    Worker/listeningdevicesworker.cpp \
    Worker/getresolutionlistworker.cpp \
    Worker/getcameraframeworker.cpp \
    Custom/PushButton/custompushbutton_4.cpp \
    Draw/boardscene.cpp \
    Draw/boardview.cpp \
    Extern/extern.cpp \
    Custom/GraphicsItem/customitem_path.cpp \
    Custom/GraphicsItem/customitem_pixmap.cpp \
    OCR/ocrwidget.cpp \
    Menu/controlmenu.cpp \
    Custom/PushButton/custompushbutton_5.cpp \
    ExportFile/exportfile.cpp \
    exhibitionbooth.cpp

HEADERS += \
    Custom/MessageBox/messagebox_tip.h \
    Custom/Slider/c_slider.h \
    applicationstart.h \
    getupdatezip.h \
    json.hpp \
    cppcodec/data/access.hpp \
    cppcodec/data/raw_result_buffer.hpp \
    cppcodec/detail/base32.hpp \
    cppcodec/detail/base64.hpp \
    cppcodec/detail/codec.hpp \
    cppcodec/detail/config.hpp \
    cppcodec/detail/hex.hpp \
    cppcodec/detail/stream_codec.hpp \
    cppcodec/base32_crockford.hpp \
    cppcodec/base32_default_crockford.hpp \
    cppcodec/base32_default_hex.hpp \
    cppcodec/base32_default_rfc4648.hpp \
    cppcodec/base32_hex.hpp \
    cppcodec/base32_rfc4648.hpp \
    cppcodec/base64_default_rfc4648.hpp \
    cppcodec/base64_default_url.hpp \
    cppcodec/base64_default_url_unpadded.hpp \
    cppcodec/base64_rfc4648.hpp \
    cppcodec/base64_url.hpp \
    cppcodec/base64_url_unpadded.hpp \
    cppcodec/hex_default_lower.hpp \
    cppcodec/hex_default_upper.hpp \
    cppcodec/hex_lower.hpp \
    cppcodec/hex_upper.hpp \
    cppcodec/parse_error.hpp \
    Public/publicfunction.h \
    Custom/PushButton/custompushbutton_1.h \
    Custom/PushButton/custompushbutton_2.h \
    Custom/PushButton/custompushbutton.h \
    Custom/PushButton/custompushbutton_3.h \
    ToolBar/maintoolbar_left.h \
    Menu/mainmenu.h \
    Menu/resolutionmenu.h \
    Menu/devicesmenu.h \
    ToolBar/maintoolbar_midleft.h \
    ToolBar/maintoolbar_midright.h \
    mainwidget.h \
    ToolBar/maintoolbar_refore.h \
    ToolBar/maintoolbar_right.h \
    Menu/imagemenu.h \
    Custom/CustomLabel/customlabel.h \
    Custom/CustomWidget/customwidget.h \
    Worker/listeningdevicesworker.h \
    Worker/getresolutionlistworker.h \
    Worker/getcameraframeworker.h \
    Custom/PushButton/custompushbutton_4.h \
    aboutus.h \
    Draw/boardview.h \
    Draw/boardscene.h \
    Extern/extern.h \
    Custom/GraphicsItem/customitem_path.h \
    Custom/GraphicsItem/customitem_pixmap.h \
    OCR/ocrworker.h \
    OCR/ocrwidget.h \
    OCR/ocrthread.h \
    Menu/controlmenu.h \
    Custom/PushButton/custompushbutton_5.h \
    ExportFile/exportfile.h \
    exhibitionbooth_interface.h \
    exhibitionbooth.h

FORMS += \
    applicationstart.ui \
    db_messageboxdialog.ui \
    ToolBar/maintoolbar_left.ui \
    Menu/mainmenu.ui \
    Menu/resolutionmenu.ui \
    Menu/devicesmenu.ui \
    ToolBar/maintoolbar_midleft.ui \
    ToolBar/maintoolbar_midright.ui \
    getupdatezip.ui \
    mainwidget.ui \
    ToolBar/maintoolbar_refore.ui \
    ToolBar/maintoolbar_right.ui \
    Menu/imagemenu.ui \
    OCR/ocrwidget.ui \
    Menu/controlmenu.ui \
    ExportFile/exportfile.ui

RESOURCES += \
    myresourcefile.qrc

DISTFILES += ExhibitionBooth.json
