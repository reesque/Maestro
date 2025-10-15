#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "settings.h"

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
    Controller(std::shared_ptr<Settings> settings, QWidget *parent);
    ~Controller() override;

public slots:
    void onDpadResponsiveLevelChanged(int level);
    void onFaceBtnResponsiveLevelChanged(int level);

signals:
    void triggerUpAction();
    void triggerDownAction();
    void triggerRightAction();
    void triggerLeftAction();
    void triggerBackAction();
    void triggerConfirmAction();
    void triggerExtra1Action();
    void triggerExtra2Action();

private slots:
    void connectedGamepadsChanged();
    void controllerButtonUpChanged(bool value);
    void controllerButtonDownChanged(bool value);
    void controllerButtonLeftChanged(bool value);
    void controllerButtonRightChanged(bool value);
    void controllerButtonAChanged(bool value);
    void controllerButtonBChanged(bool value);
    void controllerButtonXChanged(bool value);
    void controllerButtonYChanged(bool value);

private:
    void disconnectGamepad();
    void connectGamepad(int id);
    int levelToMillisec(int level);

private:
    std::unique_ptr<QShortcut> m_upKey;
    std::unique_ptr<QShortcut> m_downKey;
    std::unique_ptr<QShortcut> m_leftKey;
    std::unique_ptr<QShortcut> m_rightKey;
    std::unique_ptr<QShortcut> m_backKey;
    std::unique_ptr<QShortcut> m_confirmKey;
    std::unique_ptr<QShortcut> m_extra1Key;
    std::unique_ptr<QShortcut> m_extra2Key;

    std::shared_ptr<Settings> m_setting;

    QTimer *m_faceBtnDebounceTimer;
    QTimer *m_dpadDebounceTimer;
    QGamepad *m_currentGamepad;
};

#endif // CONTROLLER_H
