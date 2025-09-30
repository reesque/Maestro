#ifndef BLUETOOTHSCANMENU_H
#define BLUETOOTHSCANMENU_H

#include "menu.h"
#include "menulistitem.h"

#include <QTimer>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>

class BluetoothScanMenu : public Menu<LabelMenuEntry, MenuListItem>
{
public:
    explicit BluetoothScanMenu(QWidget *parent = nullptr);
    ~BluetoothScanMenu() override;

protected:
    MenuListItem* createDefaultItem() override;
    void updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget) override;

private:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void scanFinished();

private:
    std::unique_ptr<QBluetoothDeviceDiscoveryAgent> m_bluetoothAgent;
    std::unique_ptr<QBluetoothLocalDevice> m_localDevice;
    std::deque<std::shared_ptr<LabelMenuEntry>> m_scannedEntries;
    QTimer *m_scanTimer;
};

#endif // BLUETOOTHSCANMENU_H
