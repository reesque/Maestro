#ifndef MENULISTITEM_H
#define MENULISTITEM_H

#include "basemenulistitem.h"

namespace Ui {
class MenuListItem;
}

class MenuListItem : public BaseMenuListItem
{
    Q_OBJECT

public:
    explicit MenuListItem(const std::string& label, QWidget *parent = nullptr);
    ~MenuListItem() override;

    void onFocus() override;
    void onLoseFocus() override;

private:
    Ui::MenuListItem *ui;
};

#endif // MENULISTITEM_H
