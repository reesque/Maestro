#include "basemenulistitem.h"

void BaseMenuListItem::activate()
{
    m_activator();
}

BaseMenuListItem::BaseMenuListItem(std::function<void()> activator, QWidget *parent) :
    QWidget(parent)
{
    m_activator = activator;
}
