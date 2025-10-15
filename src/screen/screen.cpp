#include "screen.h"

Screen::Screen(QWidget *parent) :
    QWidget(parent)
{
    prevScreen = ScreenType::None;
    setFocusPolicy(Qt::StrongFocus);

    m_inputLock = false;
}

Screen::~Screen()
{}

void Screen::setInputLock(bool isLocked)
{
    m_inputLock = isLocked;
}

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

void Screen::resizeEvent(QResizeEvent *)
{}

void Screen::backAction()
{
    if (!m_inputLock)
    {
        emit switchToPreviousScreen(prevScreenArgs);
    }
}

void Screen::confirmAction()
{}

void Screen::extra1Action()
{}

void Screen::extra2Action()
{}
