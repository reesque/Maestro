#ifndef BLUETOOTHMENU_H
#define BLUETOOTHMENU_H

#include "menu.h"
#include "menuwithtogglelistitem.h"

#include <QtBluetooth/QBluetoothLocalDevice>

class BluetoothMenu : public Menu<LabelWithToggleMenuEntry, MenuWithToggleListItem>
{
public:
    explicit BluetoothMenu(QWidget *parent = nullptr);
    ~BluetoothMenu() override;

protected:
    MenuWithToggleListItem* createDefaultItem() override;
    void updateListItem(std::shared_ptr<LabelWithToggleMenuEntry> entry, MenuWithToggleListItem *widget) override;

private:
    std::unique_ptr<QBluetoothLocalDevice> m_localDevice;
};

#endif // BLUETOOTHMENU_H
