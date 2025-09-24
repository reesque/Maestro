#ifndef BASEMENULISTITEM_H
#define BASEMENULISTITEM_H

#include <functional>

#include <QWidget>

class BaseMenuListItem : public QWidget
{
    Q_OBJECT

public:
    virtual void activate();
    virtual void onSideActivate(QVariant arg);

    void setActivator(std::function<void()> activator);
    void setSideActivator(std::function<void(QVariant)> sideActivator);

    virtual void onFocus();
    virtual void onLoseFocus();

    virtual ~BaseMenuListItem() = default;

protected:
    BaseMenuListItem(QWidget *parent = nullptr);

protected:
    std::function<void()> m_activator;
    std::function<void(QVariant)> m_sideActivator;
};

#endif // BASEMENULISTITEM_H
