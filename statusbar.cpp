#include "statusbar.h"
#include "ui_statusbar.h"

#include <ctime>
#include <iomanip>

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);

    timeChanged(QDateTime::currentDateTime());

    // Monitor time changed
    pTimeWatcher = std::make_unique<TimeWatcher>(this);
    connect(pTimeWatcher.get(), &TimeWatcher::timeChanged, this, &StatusBar::timeChanged);
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::timeChanged(QDateTime dateTime)
{
    auto localTime = dateTime.toLocalTime();
    std::stringstream timeStream;
    timeStream << localTime.time().hour() << ":" << localTime.time().minute();
    ui->Time->setText(QString::fromStdString(timeStream.str()));
}

std::string StatusBar::currentTime()
{
    std::stringstream timeStream;
    std::time_t t = std::time(nullptr);
    std::tm local_tm = *std::localtime(&t);

    timeStream << std::put_time(&local_tm, "%H:%M");
    return timeStream.str();
}

TimeWatcher::TimeWatcher(QWidget *parent) : QObject(parent) {
    lastTime = QDateTime::currentDateTime();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TimeWatcher::checkTime);
    timer->start(1000);
}

void TimeWatcher::checkTime() {
    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 diff = lastTime.msecsTo(currentTime);

    if (qAbs(diff - 1000) > 1000) {
        emit TimeWatcher::timeChanged(currentTime);
    }

    lastTime = currentTime;
    timer->start(1000);
}
