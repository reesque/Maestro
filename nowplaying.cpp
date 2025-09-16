#include "nowplaying.h"
#include "ui_nowplaying.h"

#include <QDir>

#include <filesystem>

NowPlaying::NowPlaying(std::shared_ptr<Database> db, std::shared_ptr<MediaPlayer> mediaPlayer, QWidget *parent) :
    Screen(parent),
    ui(new Ui::NowPlaying)
{
    prevScreen = ScreenType::Main;

    m_db = db;
    m_mediaPlayer = mediaPlayer;

    ui->setupUi(this);

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
    // Update track stats
    ui->Title->setText(QString::fromStdString(track.title));
    ui->Artist->setText(QString::fromStdString(track.artist));
    ui->Album->setText(QString::fromStdString(track.album));

    // Update player stats
    ui->TimeLeft->setText(QString::fromStdString(m_mediaPlayer->getElapsedTime()));
    ui->TimeRight->setText(QString::fromStdString(m_mediaPlayer->getRemainingTime()));
    ui->Seekbar->setValue(m_mediaPlayer->getPercentage());

    // Update artwork
    QString artworkPath = QDir::homePath() + "/.config/maestro/artwork/";
    QString trackArtworkPath = artworkPath + track.album.c_str();
    QString trackArtPathPng = trackArtworkPath + ".png";
    QString trackArtPathJpg = trackArtworkPath + ".jpg";
    std::string artPath = "";
    if (std::filesystem::exists(trackArtPathPng.toStdString()))
    {
        artPath = trackArtPathPng.toStdString();
    }
    else if (std::filesystem::exists(trackArtPathJpg.toStdString()))
    {
        artPath = trackArtPathJpg.toStdString();
    }

    if (artPath != "")
    {
        QPixmap pixmap(QString::fromStdString(artPath));
        ui->CoverArt->setPixmap(pixmap);
    }
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
