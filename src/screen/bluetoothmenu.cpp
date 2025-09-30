#include "bluetoothmenu.h"

BluetoothMenu::BluetoothMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Setting;

    menuList->push_back(std::make_shared<LabelMenuEntry>("Scan", [=](){switchScreenTo(ScreenType::BluetoothScan);}));
}

BluetoothMenu::~BluetoothMenu()
{}

MenuListItem* BluetoothMenu::createDefaultItem()
{
    return new MenuListItem(ui->ListObject);
}

void BluetoothMenu::updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget)
{
    widget->setProperties(entry->label);
    widget->setActivator(entry->activator);
}
