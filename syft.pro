QT      += core

QT += widgets
QT += multimedia
QT += multimediawidgets

QT += webview
QT += webenginewidgets

#WEBENGINE_CONFIG+=use_proprietary_codecs

CONFIG += c++11
CONFIG += console
CONFIG += static


CONFIG += link_pkgconfig
#PKGCONFIG += QtGStreamer

TARGET = Syft

INCLUDEPATH += inc/

LIBS += -framework AppKit -framework QuartzCore -framework QTKit

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/contentviewer.cpp \
    src/directorytableview.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/syftactionmanager.cpp \
    src/syftactions.cpp \
    src/syftdir.cpp \
    src/syftfile.cpp \
    src/syftoptions.cpp \
    src/syftorganizer.cpp \
    src/syftsettings.cpp \
    src/videoplayer.cpp \
    src/webmvideoplayer.cpp

HEADERS += \
    inc/contentviewer.h \
    inc/directorytableview.h \
    inc/mainwindow.h \
    inc/syftaction.h \
    inc/syftactionmanager.h \
    inc/syftactions.h \
    inc/syftdir.h \
    inc/syftfile.h \
    inc/syftoptions.h \
    inc/syftorganizer.h \
    inc/syftsettings.h \
    inc/videoplayer.h \
    inc/webmvideoplayer.h \

FORMS += \
    inc/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


