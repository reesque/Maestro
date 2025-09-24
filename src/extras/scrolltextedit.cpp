#include "scrolltextedit.h"

#include <QScrollBar>

ScrollTextEdit::ScrollTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    scrollTimer = new QTimer(this);
    startTimer = new QTimer(this);
    endTimer = new QTimer(this);

    setReadOnly(true);
    viewport()->setCursor(Qt::ArrowCursor);

    // Connect all the timers
    connect(scrollTimer, &QTimer::timeout, this, &ScrollTextEdit::scrollStep);
    connect(startTimer, &QTimer::timeout, this, &ScrollTextEdit::waitAtTheStart);
    connect(endTimer, &QTimer::timeout, this, &ScrollTextEdit::waitAtTheEnd);

    // Start chain of timer
    startScrolling();
}

ScrollTextEdit::~ScrollTextEdit()
{
    disconnect(scrollTimer, &QTimer::timeout, this, &ScrollTextEdit::scrollStep);
    disconnect(startTimer, &QTimer::timeout, this, &ScrollTextEdit::waitAtTheStart);
    disconnect(endTimer, &QTimer::timeout, this, &ScrollTextEdit::waitAtTheEnd);
}

void ScrollTextEdit::startScrolling()
{
    startTimer->start(WAIT_TIME);
}

void ScrollTextEdit::stopScrolling()
{
    scrollTimer->stop();
    startTimer->stop();
    endTimer->stop();
    horizontalScrollBar()->setValue(0);
}

void ScrollTextEdit::waitAtTheStart()
{
    startTimer->stop();
    scrollTimer->start(50);
}

void ScrollTextEdit::waitAtTheEnd()
{
    horizontalScrollBar()->setValue(0);
    endTimer->stop();
    startScrolling();
}

void ScrollTextEdit::scrollStep()
{
    QScrollBar* hScroll = horizontalScrollBar();
    int newVal = hScroll->value() + 1;
    if (newVal >= hScroll->maximum()) {
        scrollTimer->stop();
        endTimer->start(WAIT_TIME);
    } else {
        hScroll->setValue(newVal);
    }
}
