#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T13:32:51
#
#-------------------------------------------------

QT       += core gui widgets multimedia opengl


LIBS += "/usr/local/lib/libopencv_core.so"
LIBS += "/usr/local/lib/libopencv_video.so"
LIBS += "/usr/local/lib/libopencv_highgui.so"
LIBS += "/usr/local/lib/libopencv_imgproc.so"
LIBS += "/usr/local/lib/libopencv_objdetect.so"
LIBS += "/usr/local/lib/libopencv_videoio.so"


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = catalogo-nui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    boton.cpp \
    navigator.cpp \
    image.cpp \
    haar/haar.cpp \
    config/config.cpp \
    camera/camera.cpp \
    features/features.cpp \
    camerathread.cpp

HEADERS += \
        widget.h \
    boton.h \
    navigator.h \
    keys.h \
    image.h \
    logger/logger.h \
    haar/haar.h \
    config/config.h \
    camera/camera.h \
    features/features.h \
    common.h \
    camerathread.h

FORMS += \
        widget.ui \
    boton.ui

DISTFILES += \
    project.config
