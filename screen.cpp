#include "screen.h"

Screen::Screen(QWidget *parent) :
    QWidget(parent)
{
    prevScreen = ScreenType::None;
    setFocusPolicy(Qt::StrongFocus);

    // Keyboard config
    leftKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Left), this);
    connect(leftKey.get(), &QShortcut::activated, this, &Screen::leftAction);
}

Screen::~Screen()
{
    disconnect(leftKey.get(), &QShortcut::activated, this, &Screen::leftAction);
}

ScreenType Screen::getPrevScreen()
{
    return prevScreen;
}

void Screen::upAction()
{}

void Screen::dnAction()
{}

void Screen::rightAction()
{}

void Screen::leftAction()
{
    emit switchToPreviousScreen(prevScreenArgs);
}
