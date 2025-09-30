#include "bluetoothpairscreen.h"

#include "ui_bluetoothpair.h"

BluetoothPairScreen::BluetoothPairScreen(QBluetoothAddress pairAddress, QWidget *parent) :
    Screen(parent),
    ui(new Ui::BluetoothPairScreen)
{
    prevScreen = ScreenType::Bluetooth;

    ui->setupUi(this);

    setInputLock(true);

    m_localDevice = std::make_unique<QBluetoothLocalDevice>();
    targetAddress = pairAddress;

    connect(m_localDevice.get(), &QBluetoothLocalDevice::pairingFinished,
            this, &BluetoothPairScreen::pairSuccess);
    connect(m_localDevice.get(), &QBluetoothLocalDevice::error,
            this, &BluetoothPairScreen::pairError);

    m_localDevice->requestPairing(pairAddress, QBluetoothLocalDevice::Paired);
}

BluetoothPairScreen::~BluetoothPairScreen()
{
    disconnect(m_localDevice.get(), &QBluetoothLocalDevice::pairingFinished,
            this, &BluetoothPairScreen::pairSuccess);
    disconnect(m_localDevice.get(), &QBluetoothLocalDevice::error,
            this, &BluetoothPairScreen::pairError);

    delete ui;
}

void BluetoothPairScreen::pairSuccess(const QBluetoothAddress &address,
                                      QBluetoothLocalDevice::Pairing pairing)
{
    if (address == targetAddress && pairing == QBluetoothLocalDevice::Pairing::Paired)
    {
        switchToPreviousScreen();
    }
}

void BluetoothPairScreen::pairError(QBluetoothLocalDevice::Error error)
{
    if (error == QBluetoothLocalDevice::Error::PairingError ||
        error == QBluetoothLocalDevice::Error::UnknownError)
    {
        switchToPreviousScreen();
    }
}
