#include "controller.h"

#include <iostream>

Controller::Controller(QWidget *parent)
    : QObject{parent}
{
    // Keyboard config
    leftKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Left), parent);
    rightKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Right), parent);
    upKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Up), parent);
    downKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Down), parent);
    backKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Escape), parent);
    confirmKey = std::make_unique<QShortcut>(QKeySequence(Qt::Key_Space), parent);

    connect(leftKey.get(), &QShortcut::activated, this, &Controller::triggerLeftAction);
    connect(rightKey.get(), &QShortcut::activated, this, &Controller::triggerRightAction);
    connect(upKey.get(), &QShortcut::activated, this, &Controller::triggerUpAction);
    connect(downKey.get(), &QShortcut::activated, this, &Controller::triggerDownAction);
    connect(backKey.get(), &QShortcut::activated, this, &Controller::triggerBackAction);
    connect(confirmKey.get(), &QShortcut::activated, this, &Controller::triggerConfirmAction);

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
    disconnect(leftKey.get(), &QShortcut::activated, this, &Controller::triggerLeftAction);
    disconnect(rightKey.get(), &QShortcut::activated, this, &Controller::triggerRightAction);
    disconnect(upKey.get(), &QShortcut::activated, this, &Controller::triggerUpAction);
    disconnect(downKey.get(), &QShortcut::activated, this, &Controller::triggerDownAction);
    disconnect(backKey.get(), &QShortcut::activated, this, &Controller::triggerBackAction);
    disconnect(confirmKey.get(), &QShortcut::activated, this, &Controller::triggerConfirmAction);

    disconnectGamepad();
}

void Controller::disconnectGamepad()
{
    if (currentGamepad)
    {
        disconnect(currentGamepad, &QGamepad::buttonLeftChanged, this, &Controller::controllerButtonLeftChanged);
        disconnect(currentGamepad, &QGamepad::buttonRightChanged, this, &Controller::controllerButtonRightChanged);
        disconnect(currentGamepad, &QGamepad::buttonUpChanged, this, &Controller::controllerButtonUpChanged);
        disconnect(currentGamepad, &QGamepad::buttonDownChanged, this, &Controller::controllerButtonDownChanged);
        disconnect(currentGamepad, &QGamepad::buttonBChanged, this, &Controller::controllerButtonBChanged);
        disconnect(currentGamepad, &QGamepad::buttonAChanged, this, &Controller::controllerButtonAChanged);
        delete currentGamepad;
        currentGamepad = nullptr;
    }
}

void Controller::connectGamepad(int id)
{
    disconnectGamepad();
    currentGamepad = new QGamepad(id, this);

    connect(currentGamepad, &QGamepad::buttonLeftChanged, this, &Controller::controllerButtonLeftChanged);
    connect(currentGamepad, &QGamepad::buttonRightChanged, this, &Controller::controllerButtonRightChanged);
    connect(currentGamepad, &QGamepad::buttonUpChanged, this, &Controller::controllerButtonUpChanged);
    connect(currentGamepad, &QGamepad::buttonDownChanged, this, &Controller::controllerButtonDownChanged);
    connect(currentGamepad, &QGamepad::buttonBChanged, this, &Controller::controllerButtonBChanged);
    connect(currentGamepad, &QGamepad::buttonAChanged, this, &Controller::controllerButtonAChanged);
}

void Controller::controllerButtonUpChanged(bool value)
{
    if (value)
    {
        emit triggerUpAction();
    }
}

void Controller::controllerButtonDownChanged(bool value)
{
    if (value)
    {
        emit triggerDownAction();
    }
}

void Controller::controllerButtonLeftChanged(bool value)
{
    if (value)
    {
        emit triggerLeftAction();
    }
}

void Controller::controllerButtonRightChanged(bool value)
{
    if (value)
    {
        emit triggerRightAction();
    }
}

void Controller::controllerButtonAChanged(bool value)
{
    if (value)
    {
        emit triggerConfirmAction();
    }
}

void Controller::controllerButtonBChanged(bool value)
{
    if (value)
    {
        emit triggerBackAction();
    }
}

void Controller::connectedGamepadsChanged()
{
    QList<int> gamepads = QGamepadManager::instance()->connectedGamepads();

    if (currentGamepad)
    {
        if (gamepads.size() == 0 ||  currentGamepad->deviceId() != gamepads[gamepads.size() - 1])
        {
            disconnectGamepad();
        }
    }

    if (gamepads.size() > 0 && !currentGamepad)
    {
        connectGamepad(gamepads[gamepads.size() - 1]);
    }
}
