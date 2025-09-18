#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
}

StatusBar::~StatusBar()
{
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
            ui->PlaybackStatus->setPixmap(QPixmap(":/icons/assets/play.png"));
            break;
        }
        case (PlaybackStatus::Paused):
        {
            ui->PlaybackStatus->setPixmap(QPixmap(":/icons/assets/pause.png"));
            break;
        }
        case (PlaybackStatus::Stopped):
        {
            ui->PlaybackStatus->setPixmap(QPixmap());
            break;
        }
    }
}
