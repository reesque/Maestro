#include "nowplaying.h"
#include "ui_nowplaying.h"

NowPlaying::NowPlaying(std::shared_ptr<Database> db, std::shared_ptr<MediaPlayer> mediaPlayer, QWidget *parent) :
    Screen(parent),
    ui(new Ui::NowPlaying)
{
    prevScreen = ScreenType::Main;

    m_db = db;
    m_mediaPlayer = mediaPlayer;

    ui->setupUi(this);

    ui->Seekbar->setStyleSheet(
            "QProgressBar {"
            "    border: 2px solid grey;"
            "    border-radius: 5px;"
            "}"
            "QProgressBar::chunk {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0096FF, stop:1 #0066CC);"
            "    width: 1px;"
            "}"
        );

    seekTimer = std::make_unique<QTimer>();
    connect(seekTimer.get(), &QTimer::timeout, this, &NowPlaying::tickSeekBar);
    seekTimer->start(10);

    connect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);
    onTrackInfoUpdate(m_mediaPlayer->getCurrentTrackMetaData());
}

NowPlaying::~NowPlaying()
{
    disconnect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);
    disconnect(seekTimer.get(), &QTimer::timeout, this, &NowPlaying::tickSeekBar);

    delete ui;
}

void NowPlaying::onTrackInfoUpdate(MediaPlayer::Track track)
{
    ui->Title->setText(QString::fromStdString(track.title));
    ui->Artist->setText(QString::fromStdString(track.artist));
    ui->Album->setText(QString::fromStdString(track.album));

    ui->TimeLeft->setText(QString::fromStdString(m_mediaPlayer->getElapsedTime()));
    ui->TimeRight->setText(QString::fromStdString(m_mediaPlayer->getRemainingTime()));
    ui->Seekbar->setValue(m_mediaPlayer->getPercentage());
}

void NowPlaying::tickSeekBar()
{
    if (m_mediaPlayer->isPlaying() && ui->Seekbar->value() + 1 != ui->Seekbar->maximum())
    {
        ui->Seekbar->setValue(m_mediaPlayer->getPercentage());
        ui->TimeLeft->setText(QString::fromStdString(m_mediaPlayer->getElapsedTime()));
        ui->TimeRight->setText(QString::fromStdString(m_mediaPlayer->getRemainingTime()));
    }
}

void NowPlaying::upAction()
{}

void NowPlaying::dnAction()
{}

void NowPlaying::rightAction()
{}
