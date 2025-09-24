#include "basemenulistitem.h"

#include <QVariant>

void BaseMenuListItem::activate()
{
    m_activator();
}

void BaseMenuListItem::setActivator(std::function<void()> activator)
{
    m_activator = activator;
}

void BaseMenuListItem::onSideActivate(QVariant arg)
{
    m_sideActivator(arg);
}

void BaseMenuListItem::setSideActivator(std::function<void(QVariant)> sideActivator)
{
    m_sideActivator = sideActivator;
}

void BaseMenuListItem::onFocus()
{}

void BaseMenuListItem::onLoseFocus()
{}

BaseMenuListItem::BaseMenuListItem(QWidget *parent) :
    QWidget(parent)
{
    m_activator = [](){};
    m_sideActivator = [](QVariant){};
}
