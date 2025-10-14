#include "controller.h"

#include <iostream>

Controller::Controller(std::shared_ptr<Settings> setting, QWidget *parent)
    : QObject{parent}, m_currentGamepad(nullptr)
{
    m_setting = setting;

    // Debounce timer
    m_faceBtnDebounceTimer = new QTimer(this);
    m_faceBtnDebounceTimer->setSingleShot(true);
    m_faceBtnDebounceTimer->setInterval(levelToMillisec(m_setting->getFaceBtnResponsiveLevel()));

    m_dpadDebounceTimer = new QTimer(this);
    m_dpadDebounceTimer->setSingleShot(true);
    m_dpadDebounceTimer->setInterval(levelToMillisec(m_setting->getDpadResponsiveLevel()));

    // Keyboard config
    m_leftKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Left), parent);
    m_rightKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Right), parent);
    m_upKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Up), parent);
    m_downKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Down), parent);
    m_backKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Escape), parent);
    m_confirmKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Return), parent);

    connect(m_leftKey.get(), &QShortcut::activated, this, &Controller::triggerLeftAction);
    connect(m_rightKey.get(), &QShortcut::activated, this, &Controller::triggerRightAction);
    connect(m_upKey.get(), &QShortcut::activated, this, &Controller::triggerUpAction);
    connect(m_downKey.get(), &QShortcut::activated, this, &Controller::triggerDownAction);
    connect(m_backKey.get(), &QShortcut::activated, this, &Controller::triggerBackAction);
    connect(m_confirmKey.get(), &QShortcut::activated, this, &Controller::triggerConfirmAction);

    // Gamepad config
    connect(QGamepadManager::instance(), &QGamepadManager::connectedGamepadsChanged, this, &Controller::connectedGamepadsChanged);
    QList<int> gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.size() > 0)
    {
        connectGamepad(gamepads[gamepads.size() - 1]);
    }
}

Controller::~Controller()
{
    disconnect(m_leftKey.get(), &QShortcut::activated, this, &Controller::triggerLeftAction);
    disconnect(m_rightKey.get(), &QShortcut::activated, this, &Controller::triggerRightAction);
    disconnect(m_upKey.get(), &QShortcut::activated, this, &Controller::triggerUpAction);
    disconnect(m_downKey.get(), &QShortcut::activated, this, &Controller::triggerDownAction);
    disconnect(m_backKey.get(), &QShortcut::activated, this, &Controller::triggerBackAction);
    disconnect(m_confirmKey.get(), &QShortcut::activated, this, &Controller::triggerConfirmAction);
}

void Controller::onDpadResponsiveLevelChanged(int level)
{
    m_dpadDebounceTimer->setInterval(levelToMillisec(level));
}

void Controller::onFaceBtnResponsiveLevelChanged(int level)
{
    m_faceBtnDebounceTimer->setInterval(levelToMillisec(level));
}

void Controller::disconnectGamepad()
{
    if (m_currentGamepad)
    {
        disconnect(m_currentGamepad, &QGamepad::buttonLeftChanged, this, &Controller::controllerButtonLeftChanged);
        disconnect(m_currentGamepad, &QGamepad::buttonRightChanged, this, &Controller::controllerButtonRightChanged);
        disconnect(m_currentGamepad, &QGamepad::buttonUpChanged, this, &Controller::controllerButtonUpChanged);
        disconnect(m_currentGamepad, &QGamepad::buttonDownChanged, this, &Controller::controllerButtonDownChanged);
        disconnect(m_currentGamepad, &QGamepad::buttonBChanged, this, &Controller::controllerButtonBChanged);
        disconnect(m_currentGamepad, &QGamepad::buttonAChanged, this, &Controller::controllerButtonAChanged);
        delete m_currentGamepad;
        m_currentGamepad = nullptr;
    }
}

void Controller::connectGamepad(int id)
{
    disconnectGamepad();
    m_currentGamepad = new QGamepad(id, this);

    connect(m_currentGamepad, &QGamepad::buttonLeftChanged, this, &Controller::controllerButtonLeftChanged);
    connect(m_currentGamepad, &QGamepad::buttonRightChanged, this, &Controller::controllerButtonRightChanged);
    connect(m_currentGamepad, &QGamepad::buttonUpChanged, this, &Controller::controllerButtonUpChanged);
    connect(m_currentGamepad, &QGamepad::buttonDownChanged, this, &Controller::controllerButtonDownChanged);
    connect(m_currentGamepad, &QGamepad::buttonBChanged, this, &Controller::controllerButtonBChanged);
    connect(m_currentGamepad, &QGamepad::buttonAChanged, this, &Controller::controllerButtonAChanged);
}

void Controller::controllerButtonUpChanged(bool value)
{
    if (value && !m_dpadDebounceTimer->isActive())
    {
        m_dpadDebounceTimer->start();
        emit triggerUpAction();
    }
}

void Controller::controllerButtonDownChanged(bool value)
{
    if (value && !m_dpadDebounceTimer->isActive())
    {
        m_dpadDebounceTimer->start();
        emit triggerDownAction();
    }
}

void Controller::controllerButtonLeftChanged(bool value)
{
    if (value && !m_dpadDebounceTimer->isActive())
    {
        m_dpadDebounceTimer->start();
        emit triggerLeftAction();
    }
}

void Controller::controllerButtonRightChanged(bool value)
{
    if (value && !m_dpadDebounceTimer->isActive())
    {
        m_dpadDebounceTimer->start();
        emit triggerRightAction();
    }
}

void Controller::controllerButtonAChanged(bool value)
{
    if (value && !m_faceBtnDebounceTimer->isActive())
    {
        m_faceBtnDebounceTimer->start();
        emit triggerConfirmAction();
    }
}

void Controller::controllerButtonBChanged(bool value)
{
    if (value && !m_faceBtnDebounceTimer->isActive())
    {
        m_faceBtnDebounceTimer->start();
        emit triggerBackAction();
    }
}

void Controller::connectedGamepadsChanged()
{
    QList<int> gamepads = QGamepadManager::instance()->connectedGamepads();

    if (m_currentGamepad)
    {
        if (gamepads.size() == 0 ||  m_currentGamepad->deviceId() != gamepads[gamepads.size() - 1])
        {
            disconnectGamepad();
        }
    }

    if (gamepads.size() > 0 && !m_currentGamepad)
    {
        connectGamepad(gamepads[gamepads.size() - 1]);
    }
}

int Controller::levelToMillisec(int level)
{
    // 250 base level
    return 250 + level * 250;
}
