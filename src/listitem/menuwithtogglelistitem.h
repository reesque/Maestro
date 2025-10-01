#ifndef MENUWITHTOGGLELISTITEM_H
#define MENUWITHTOGGLELISTITEM_H

#include "basemenulistitem.h"
#include "menuentry.h"

namespace Ui {
class MenuWithToggleListItem;
}

class MenuWithToggleListItem : public BaseMenuListItem
{
    Q_OBJECT

public:
    explicit MenuWithToggleListItem(QWidget *parent = nullptr);
    ~MenuWithToggleListItem() override;

    void setProperties(std::shared_ptr<LabelWithToggleMenuEntry> entry);
    void onFocus() override;
    void onLoseFocus() override;

    void activate() override;

private:
    Ui::MenuWithToggleListItem *ui;
    std::shared_ptr<LabelWithToggleMenuEntry> m_entry;
};

#endif // MENUWITHTOGGLELISTITEM_H
