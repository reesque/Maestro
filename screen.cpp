#include "screen.h"

Screen::Screen(QWidget *parent) :
    QWidget(parent)
{
    prevScreen = ScreenType::None;
    setFocusPolicy(Qt::StrongFocus);

    // Keyboard config
    leftKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Left), this);
    upKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Up), this);
    downKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Down), this);
    rightKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Right), this);
    backKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Escape), this);
    confirmKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Space), this);

    connect(backKey.get(), &QShortcut::activated, this, &Screen::backAction);
}

Screen::~Screen()
{
    disconnect(backKey.get(), &QShortcut::activated, this, &Screen::backAction);
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

void Screen::backAction()
{
    emit switchToPreviousScreen(prevScreenArgs);
}

void Screen::confirmAction()
{}
