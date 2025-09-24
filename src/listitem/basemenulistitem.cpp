#include "basemenulistitem.h"

#include <QVariant>

void BaseMenuListItem::activate()
{
    m_activator();
}

void BaseMenuListItem::onFocus()
{
    m_focusActivator();
}

void BaseMenuListItem::setActivator(std::function<void()> activator)
{
    m_activator = activator;
}

void BaseMenuListItem::setOnFocus(std::function<void()> focusActivator)
{
    m_focusActivator = focusActivator;
}

void BaseMenuListItem::onSideActivate(QVariant arg)
{
    m_sideActivator(arg);
}

void BaseMenuListItem::setSideActivator(std::function<void(QVariant)> sideActivator)
{
    m_sideActivator = sideActivator;
}

BaseMenuListItem::BaseMenuListItem(QWidget *parent) :
    QWidget(parent)
{
    m_activator = [](){};
    m_focusActivator = [](){};
    m_sideActivator = [](QVariant){};
}
