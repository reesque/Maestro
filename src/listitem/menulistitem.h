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
    explicit MenuListItem(QWidget *parent = nullptr);
    ~MenuListItem() override;

    void setProperties(const std::string& label);
    void onFocus() override;
    void onLoseFocus() override;

private:
    Ui::MenuListItem *ui;
};

#endif // MENULISTITEM_H
