#include "nowplaying.h"
#include "ui_nowplaying.h"

#include <iostream>

NowPlaying::NowPlaying(std::shared_ptr<Database> db, std::shared_ptr<MediaPlayer> mediaPlayer, QWidget *parent) :
    Screen(parent),
    ui(new Ui::NowPlaying)
{
    m_db = db;
    m_mediaPlayer = mediaPlayer;

    ui->setupUi(this);

    ui->Seekbar->setStyleSheet(
            "QProgressBar {"
            "    border: 2px solid grey;"
            "    border-radius: 5px;"
            "    text-align: center;"
            "}"
            "QProgressBar::chunk {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0096FF, stop:1 #0066CC);"
            "    width: 20px;"
            "}"
        );

    connect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);
    onTrackInfoUpdate(m_mediaPlayer->getCurrentTrackMetaData());
}

NowPlaying::~NowPlaying()
{
    disconnect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);

    delete ui;
}

void NowPlaying::onTrackInfoUpdate(MediaPlayer::Track track)
{
    ui->Title->setText(QString::fromStdString(track.title));
    ui->Artist->setText(QString::fromStdString(track.artist));
    ui->Album->setText(QString::fromStdString(track.album));
}
