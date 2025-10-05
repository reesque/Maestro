#ifndef CONTROLLERLISTWIDGET_H
#define CONTROLLERLISTWIDGET_H

#include <functional>

#include <QListWidget>
#include <QWheelEvent>

class ControllerListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit ControllerListWidget(QWidget *parent = nullptr);
    void setAction(std::function<void(bool)>);

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    std::function<void(bool)> m_action;
};

#endif // CONTROLLERLISTWIDGET_H
