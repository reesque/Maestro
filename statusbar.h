#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

#include <QTimer>
#include <QDateTime>

namespace Ui {
class StatusBar;
}

class TimeWatcher : public QObject {
    Q_OBJECT

public:
    TimeWatcher(QWidget *parent = nullptr);

public slots:
    void checkTime();

signals:
    void timeChanged(QDateTime);

private:
    QTimer *timer;
    QDateTime lastTime;
};

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();

private slots:
    void timeChanged(QDateTime dateTime);

private:
    std::string currentTime();

private:
    Ui::StatusBar *ui;
    std::unique_ptr<TimeWatcher> pTimeWatcher;
};

#endif // STATUSBAR_H
