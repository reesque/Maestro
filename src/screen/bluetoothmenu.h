#ifndef BLUETOOTHMENU_H
#define BLUETOOTHMENU_H

#include "menu.h"
#include "menulistitem.h"

class BluetoothMenu : public Menu<LabelMenuEntry, MenuListItem>
{
public:
    explicit BluetoothMenu(QWidget *parent = nullptr);
    ~BluetoothMenu() override;

protected:
    MenuListItem* createDefaultItem() override;
    void updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget) override;
};

#endif // BLUETOOTHMENU_H
