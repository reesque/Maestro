#include "controllerlistwidget.h"

ControllerListWidget::ControllerListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setAction([](bool){});
}

void ControllerListWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();

    if (delta > 0)
    {
        m_action(false);
    } else if (delta < 0)
    {
        m_action(true);
    }

    // Accept the event to prevent default scrolling
    event->accept();
}

void ControllerListWidget::setAction(std::function<void(bool)> action)
{
    m_action = action;
}
