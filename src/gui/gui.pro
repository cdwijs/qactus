QT += core gui widgets network
TARGET = qactus
TEMPLATE = app
DEPENDPATH += ../qobs
INCLUDEPATH += ../qobs
LIBS += -L../qobs/ -lqobs
DESTDIR += .
include(../defines.pri)

unix:isEmpty(PREFIX):PREFIX = /usr/local
unix {
    INCLUDEPATH += /usr/include/qt5keychain
    contains(QMAKE_HOST.arch, x86_64) {
        LIBS += -L/usr/lib64/ -lqt5keychain
    } else {
        LIBS += -L/usr/lib/ -lqt5keychain
    }
}

SOURCES += main.cpp \
    mainwindow.cpp \
    trayicon.cpp \
    configure.cpp \
    login.cpp \
    roweditor.cpp \
    requeststateeditor.cpp \
    autotooltipdelegate.cpp \
    packagetreewidget.cpp \
    requesttreewidgetitem.cpp \
    utils.cpp \
    credentials.cpp
HEADERS += mainwindow.h \
    trayicon.h \
    configure.h \
    login.h \
    roweditor.h \
    requeststateeditor.h \
    autotooltipdelegate.h \
    packagetreewidget.h \
    requesttreewidgetitem.h \
    utils.h \
    credentials.h
FORMS += mainwindow.ui \
    configure.ui \
    login.ui \
    roweditor.ui \
    requeststateeditor.ui
OTHER_FILES += ../README.md \
    ../LICENSE
INSTALLS += target \
    icon128 \
    desktop
target.path = $$PREFIX/bin
desktop.path = $$PREFIX/share/applications/
desktop.files += ../../qactus.desktop
icon128.path = $$PREFIX/share/icons/hicolor/128x128/apps
icon128.files += ../../qactus.png
RESOURCES = ../../application.qrc
