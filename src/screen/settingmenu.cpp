#include "settingmenu.h"

#include <QtBluetooth/QBluetoothLocalDevice>

SettingMenu::SettingMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Main;

    menuList->push_back(std::make_shared<LabelMenuEntry>("About",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::About);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Controller",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::Controller);}));

    QBluetoothLocalDevice localDevice;
    if (localDevice.isValid())
    {
        menuList->push_back(std::make_shared<LabelMenuEntry>("Bluetooth",
            [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::Bluetooth);}));
    }

    menuList->push_back(std::make_shared<LabelMenuEntry>("Sync Library",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::Reindex);}));
}

SettingMenu::~SettingMenu()
{}

MenuListItem* SettingMenu::createDefaultItem()
{
    return new MenuListItem(ui->ListObject);
}

void SettingMenu::updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget)
{
    widget->setProperties(entry);
}
