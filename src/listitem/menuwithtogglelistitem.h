#ifndef MENUWITHTOGGLELISTITEM_H
#define MENUWITHTOGGLELISTITEM_H

#include "basemenulistitem.h"

namespace Ui {
class MenuWithToggleListItem;
}

class MenuWithToggleListItem : public BaseMenuListItem
{
    Q_OBJECT

public:
    explicit MenuWithToggleListItem(QWidget *parent = nullptr);
    ~MenuWithToggleListItem() override;

    void setProperties(const std::string& label, bool toggleable, bool initValue);
    void onFocus() override;
    void onLoseFocus() override;

    void activate() override;

private:
    Ui::MenuWithToggleListItem *ui;
    bool m_toggleable;
};

#endif // MENUWITHTOGGLELISTITEM_H
