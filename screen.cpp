#include "screen.h"

Screen::Screen(QWidget *parent) :
    QWidget(parent)
{
    prevScreen = ScreenType::None;
    setFocusPolicy(Qt::StrongFocus);
}

Screen::~Screen()
{}

ScreenType Screen::getPrevScreen()
{
    return prevScreen;
}

void Screen::upAction()
{}

void Screen::downAction()
{}

void Screen::rightAction()
{}

void Screen::leftAction()
{}

void Screen::backAction()
{
    emit switchToPreviousScreen(prevScreenArgs);
}

void Screen::confirmAction()
{}
