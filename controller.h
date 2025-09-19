#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include <QObject>
#include <QShortcut>
#include <QGamepadManager>
#include <QGamepad>
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QWidget *parent = nullptr);
    ~Controller() override;

signals:
    void triggerUpAction();
    void triggerDownAction();
    void triggerRightAction();
    void triggerLeftAction();
    void triggerBackAction();
    void triggerConfirmAction();

private slots:
    void allowNextInput();
    void connectedGamepadsChanged();
    void controllerButtonUpChanged(bool value);
    void controllerButtonDownChanged(bool value);
    void controllerButtonLeftChanged(bool value);
    void controllerButtonRightChanged(bool value);
    void controllerButtonAChanged(bool value);
    void controllerButtonBChanged(bool value);

private:
    void disconnectGamepad();
    void connectGamepad(int id);

private:
    std::unique_ptr<QShortcut> upKey;
    std::unique_ptr<QShortcut> downKey;
    std::unique_ptr<QShortcut> leftKey;
    std::unique_ptr<QShortcut> rightKey;
    std::unique_ptr<QShortcut> backKey;
    std::unique_ptr<QShortcut> confirmKey;

    QTimer *debounceTimer;

    QGamepad *currentGamepad;
    bool acceptInput;
};

#endif // CONTROLLER_H
