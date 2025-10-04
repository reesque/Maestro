#include "bluetoothscanmenu.h"

#include <QVector>

BluetoothScanMenu::BluetoothScanMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Bluetooth;
    m_scannedEntries = std::deque<std::shared_ptr<LabelWithToggleMenuEntry>>();
    m_localDevice = std::make_unique<QBluetoothLocalDevice>();

    // Temp list data to display while scanning
    menuList->push_back(std::make_shared<LabelWithToggleMenuEntry>("Scanning...", false,
        [=](std::shared_ptr<LabelWithToggleMenuEntry>){}));

    // Start BT agent
    m_bluetoothAgent = std::make_unique<QBluetoothDeviceDiscoveryAgent>();
    connect(m_bluetoothAgent.get(), &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoothScanMenu::deviceDiscovered);
    m_bluetoothAgent->start();

    // Start timer
    m_scanTimer = new QTimer(this);
    connect(m_scanTimer, &QTimer::timeout, this, &BluetoothScanMenu::scanFinished);
    m_scanTimer->setSingleShot(true);
    m_scanTimer->start(5000);
}

BluetoothScanMenu::~BluetoothScanMenu()
{
    disconnect(m_bluetoothAgent.get(), &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoothScanMenu::deviceDiscovered);
    disconnect(m_bluetoothAgent.get(), &QBluetoothDeviceDiscoveryAgent::finished,
            this, &BluetoothScanMenu::scanFinished);
}

void BluetoothScanMenu::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    quint8 major = device.majorDeviceClass();
    if (major == QBluetoothDeviceInfo::AudioVideoDevice ||
        major == QBluetoothDeviceInfo::PeripheralDevice)
    {
        bool paired = m_localDevice->pairingStatus(device.address())
                != QBluetoothLocalDevice::Pairing::Unpaired;
        m_scannedEntries.push_back(std::make_shared<LabelWithToggleMenuEntry>(
            device.name().isEmpty() ? device.address().toString().toStdString()
                                    : device.name().toStdString(), true,
            [=](std::shared_ptr<LabelWithToggleMenuEntry>){
                QVector<QVariant> arg;
                arg.append(QVariant::fromValue(device.address()));
                arg.append(QVariant::fromValue(!paired));
                switchScreenTo(ScreenType::BluetoothPair, arg);
            }, paired
        ));
    }
}

void BluetoothScanMenu::scanFinished()
{
    menuList->clear();

    for (auto dev : m_scannedEntries)
    {
        menuList->push_back(dev);
    }

    toTop();
}

MenuWithToggleListItem* BluetoothScanMenu::createDefaultItem()
{
    return new MenuWithToggleListItem(ui->ListObject);
}

void BluetoothScanMenu::updateListItem(std::shared_ptr<LabelWithToggleMenuEntry> entry, MenuWithToggleListItem *widget)
{
    widget->setProperties(entry);
}
