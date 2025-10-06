#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "datastruct.h"

#include <memory>

#include <QWidget>
#include <QtBluetooth/QBluetoothLocalDevice>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar() override;

public slots:
    void changeTitle(QString title);
    void onPlaybackStateChanged(PlaybackStatus playbackStatus);

private slots:
    void bluetoothModeStateChanged(QBluetoothLocalDevice::HostMode state);
    void bluetoothDeviceConnected(const QBluetoothAddress &address);
    void bluetoothDeviceDisconnected(const QBluetoothAddress &address);

private:
    void checkBluetoothState();

private:
    Ui::StatusBar *ui;
    std::unique_ptr<QBluetoothLocalDevice> m_localDevice;
};

#endif // STATUSBAR_H
