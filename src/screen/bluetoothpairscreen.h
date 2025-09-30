#ifndef BLUETOOTHPAIRSCREEN_H
#define BLUETOOTHPAIRSCREEN_H

#include "screen.h"

#include <QtBluetooth/QBluetoothLocalDevice>

namespace Ui {
class BluetoothPairScreen;
}

class BluetoothPairScreen : public Screen
{
    Q_OBJECT

public:
    explicit BluetoothPairScreen(QBluetoothAddress pairAddress, QWidget *parent = nullptr);
    ~BluetoothPairScreen() override;

private slots:
    void pairSuccess(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing);
    void pairError(QBluetoothLocalDevice::Error error);

private:
    Ui::BluetoothPairScreen *ui;
    QBluetoothAddress targetAddress;
    std::unique_ptr<QBluetoothLocalDevice> m_localDevice;
};

#endif // BLUETOOTHPAIRSCREEN_H
