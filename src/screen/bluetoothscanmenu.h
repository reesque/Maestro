#ifndef BLUETOOTHSCANMENU_H
#define BLUETOOTHSCANMENU_H

#include "menu.h"
#include "menuwithtogglelistitem.h"

#include <QTimer>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>

class BluetoothScanMenu : public Menu<LabelWithToggleMenuEntry, MenuWithToggleListItem>
{
public:
    explicit BluetoothScanMenu(QWidget *parent = nullptr);
    ~BluetoothScanMenu() override;

protected:
    MenuWithToggleListItem* createDefaultItem() override;
    void updateListItem(std::shared_ptr<LabelWithToggleMenuEntry> entry, MenuWithToggleListItem *widget) override;

private:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void scanFinished();

private:
    std::unique_ptr<QBluetoothDeviceDiscoveryAgent> m_bluetoothAgent;
    std::unique_ptr<QBluetoothLocalDevice> m_localDevice;
    std::deque<std::shared_ptr<LabelWithToggleMenuEntry>> m_scannedEntries;
    QTimer *m_scanTimer;
};

#endif // BLUETOOTHSCANMENU_H
