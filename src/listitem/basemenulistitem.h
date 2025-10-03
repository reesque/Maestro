#ifndef BASEMENULISTITEM_H
#define BASEMENULISTITEM_H

#include <functional>

#include <QWidget>

template<typename EntryType>
class BaseMenuListItem
{
public:
    virtual void activate()
    {
        m_entry->activator(m_entry);
    }

    virtual void onFocus()
    {}

    virtual void onLoseFocus()
    {}

    virtual void setProperties(std::shared_ptr<EntryType> entry)
    {
        m_entry = entry;
        updateItem();
    }

    virtual ~BaseMenuListItem() = default;

protected:
    BaseMenuListItem(){}

    virtual void updateItem() = 0;

protected:
    std::shared_ptr<EntryType> m_entry;
};

#endif // BASEMENULISTITEM_H
