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


LIBS += -framework AppKit -framework QuartzCore -framework QTKit

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    confirmationdialog.cpp \
    contentviewer.cpp \
    directorytableview.cpp \
    main.cpp \
    mainwindow.cpp \
    syftactionmanager.cpp \
    syftactions.cpp \
    syftdir.cpp \
    syftfile.cpp \
    syftoptions.cpp \
    syftorganizer.cpp \
    syftsettings.cpp \
    videoplayer.cpp \
    webmvideoplayer.cpp

HEADERS += \
    confirmationdialog.h \
    contentviewer.h \
    directorytableview.h \
    mainwindow.h \
    syftaction.h \
    syftactionmanager.h \
    syftactions.h \
    syftdir.h \
    syftfile.h \
    syftoptions.h \
    syftorganizer.h \
    syftsettings.h \
    videoplayer.h \
    webmvideoplayer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


