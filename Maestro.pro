QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets gamepad

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/include/taglib
LIBS += -L/usr/lib -ltag -lstdc++fs

SOURCES += \
    albummenu.cpp \
    artistfiltermenu.cpp \
    artistmenu.cpp \
    artworkmenulistitem.cpp \
    basemenulistitem.cpp \
    controller.cpp \
    database.cpp \
    detailedmenulistitem.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    mediaplayer.cpp \
    menulistitem.cpp \
    musicmenu.cpp \
    nowplaying.cpp \
    reindexscreen.cpp \
    roundedprogressbarstyle.cpp \
    screen.cpp \
    settingmenu.cpp \
    songsmenu.cpp \
    statusbar.cpp

HEADERS += \
    albummenu.h \
    artistfiltermenu.h \
    artistmenu.h \
    artworkmenulistitem.h \
    basemenulistitem.h \
    controller.h \
    database.h \
    datastruct.h \
    detailedmenulistitem.h \
    mainmenu.h \
    mainwindow.h \
    mediaplayer.h \
    menu.h \
    menuentry.h \
    menulistitem.h \
    musicmenu.h \
    nowplaying.h \
    reindexscreen.h \
    roundedprogressbarstyle.h \
    screen.h \
    settingmenu.h \
    songsmenu.h \
    statusbar.h

FORMS += \
    artworkmenulistitem.ui \
    detailedmenulistitem.ui \
    mainwindow.ui \
    menu.ui \
    menulistitem.ui \
    nowplaying.ui \
    reindexscreen.ui \
    statusbar.ui

RESOURCES += \
    assets.qrc
