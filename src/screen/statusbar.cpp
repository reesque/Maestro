#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);

    m_localDevice = std::make_unique<QBluetoothLocalDevice>();

    // Initial check
    if (m_localDevice->isValid())
    {
        if (m_localDevice->hostMode() != QBluetoothLocalDevice::HostMode::HostPoweredOff)
        {
            if (m_localDevice->connectedDevices().empty())
            {
                ui->BluetoothStatus->setPixmap(QPixmap(":/app/assets/bluetooth.png"));
            }
            else
            {
                ui->BluetoothStatus->setPixmap(QPixmap(":/app/assets/bluetooth_connect.png"));
            }
        }
    }

    // Subscribe
    connect(m_localDevice.get(), &QBluetoothLocalDevice::hostModeStateChanged,
            this, &StatusBar::bluetoothModeStateChanged);
    connect(m_localDevice.get(), &QBluetoothLocalDevice::deviceConnected,
            this, &StatusBar::bluetoothDeviceConnected);
    connect(m_localDevice.get(), &QBluetoothLocalDevice::deviceDisconnected,
            this, &StatusBar::bluetoothDeviceDisconnected);
}

StatusBar::~StatusBar()
{
    disconnect(m_localDevice.get(), &QBluetoothLocalDevice::hostModeStateChanged,
            this, &StatusBar::bluetoothModeStateChanged);
    disconnect(m_localDevice.get(), &QBluetoothLocalDevice::deviceConnected,
            this, &StatusBar::bluetoothDeviceConnected);
    disconnect(m_localDevice.get(), &QBluetoothLocalDevice::deviceDisconnected,
            this, &StatusBar::bluetoothDeviceDisconnected);

    delete ui;
}

void StatusBar::changeTitle(QString title)
{
    ui->Title->setText(title);
}

void StatusBar::onPlaybackStateChanged(PlaybackStatus playbackStatus)
{
    switch (playbackStatus)
    {
        case (PlaybackStatus::Playing):
        {
            ui->PlaybackStatus->setPixmap(QPixmap(":/app/assets/play.png"));
            break;
        }
        case (PlaybackStatus::Paused):
        {
            ui->PlaybackStatus->setPixmap(QPixmap(":/app/assets/pause.png"));
            break;
        }
        case (PlaybackStatus::Stopped):
        {
            ui->PlaybackStatus->setPixmap(QPixmap());
            break;
        }
    }
}

void StatusBar::bluetoothModeStateChanged(QBluetoothLocalDevice::HostMode state)
{
    if (state == QBluetoothLocalDevice::HostMode::HostPoweredOff)
    {
        ui->BluetoothStatus->setPixmap(QPixmap());
        return;
    }

    ui->BluetoothStatus->setPixmap(QPixmap(":/app/assets/bluetooth.png"));
}

void StatusBar::bluetoothDeviceConnected(const QBluetoothAddress &)
{
    if (m_localDevice->hostMode() == QBluetoothLocalDevice::HostMode::HostPoweredOff)
    {
        return;
    }

    ui->BluetoothStatus->setPixmap(QPixmap(":/app/assets/bluetooth_connect.png"));
}

void StatusBar::bluetoothDeviceDisconnected(const QBluetoothAddress &)
{
    if (m_localDevice->hostMode() == QBluetoothLocalDevice::HostMode::HostPoweredOff)
    {
        return;
    }

    if (m_localDevice->connectedDevices().empty())
    {
        ui->BluetoothStatus->setPixmap(QPixmap(":/app/assets/bluetooth.png"));
    }
}
