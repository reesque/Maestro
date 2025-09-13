QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/include/taglib
LIBS += -L/usr/lib -ltag

SOURCES += \
    basemenulistitem.cpp \
    database.cpp \
    detailedmenulistitem.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    mediaplayer.cpp \
    menulistitem.cpp \
    musicmenu.cpp \
    screen.cpp \
    songsmenu.cpp \
    statusbar.cpp

HEADERS += \
    basemenulistitem.h \
    database.h \
    detailedmenulistitem.h \
    mainmenu.h \
    mainwindow.h \
    mediaplayer.h \
    menu.h \
    menuentry.h \
    menulistitem.h \
    musicmenu.h \
    screen.h \
    songsmenu.h \
    statusbar.h

FORMS += \
    detailedmenulistitem.ui \
    mainwindow.ui \
    menu.ui \
    menulistitem.ui \
    statusbar.ui

RESOURCES += \
    DefaultCoverArt.qrc
