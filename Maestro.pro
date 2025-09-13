QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    menulistitem.cpp \
    statusbar.cpp

HEADERS += \
    mainwindow.h \
    menu.h \
    menulistitem.h \
    statusbar.h

FORMS += \
    mainwindow.ui \
    menu.ui \
    menulistitem.ui \
    statusbar.ui
