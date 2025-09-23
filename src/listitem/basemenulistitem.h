#ifndef BASEMENULISTITEM_H
#define BASEMENULISTITEM_H

#include <functional>

#include <QWidget>

class BaseMenuListItem : public QWidget
{
    Q_OBJECT

public:
    virtual void activate();
    virtual ~BaseMenuListItem() = default;

protected:
    BaseMenuListItem(std::function<void()> activator, QWidget *parent = nullptr);

protected:
    std::function<void()> m_activator;
};

#endif // BASEMENULISTITEM_H
