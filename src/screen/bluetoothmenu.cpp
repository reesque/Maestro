#include "bluetoothmenu.h"

BluetoothMenu::BluetoothMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Setting;
    m_localDevice = std::make_unique<QBluetoothLocalDevice>();

    // Build the toggle entry
    menuList->push_back(std::make_shared<LabelWithToggleMenuEntry>("Status", true, [=](){
        if (static_cast<LabelWithToggleMenuEntry*>(menuList->at(0).get())->value) {
            m_localDevice->powerOn();
        }
        else
        {
            m_localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
        }
    }, m_localDevice->hostMode() != QBluetoothLocalDevice::HostPoweredOff));

    // Any other entries
    menuList->push_back(std::make_shared<LabelWithToggleMenuEntry>("Scan", false,
                                    [=](){switchScreenTo(ScreenType::BluetoothScan);}));
}

BluetoothMenu::~BluetoothMenu()
{}

MenuWithToggleListItem* BluetoothMenu::createDefaultItem()
{
    return new MenuWithToggleListItem(ui->ListObject);
}

void BluetoothMenu::updateListItem(std::shared_ptr<LabelWithToggleMenuEntry> entry, MenuWithToggleListItem *widget)
{
    widget->setProperties(entry);
    widget->setActivator(entry->activator);
}
