#include "nowplaying.h"
#include "ui_nowplaying.h"

#include "roundedprogressbarstyle.h"

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

    ui->Seekbar->setStyle(new RoundedProgressBarStyle);

    seekTimer = std::make_unique<QTimer>();
    connect(seekTimer.get(), &QTimer::timeout, this, &NowPlaying::tickSeekBar);
    seekTimer->start(10);

    connect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);
    if (m_mediaPlayer->isMediaReady())
    {
        onTrackInfoUpdate(m_mediaPlayer->getCurrentTrackMetaData());
    }
}

NowPlaying::~NowPlaying()
{
    disconnect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);
    disconnect(seekTimer.get(), &QTimer::timeout, this, &NowPlaying::tickSeekBar);

    delete ui;
}

void NowPlaying::onTrackInfoUpdate(Track track)
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

void NowPlaying::leftAction()
{
    m_mediaPlayer->previous();
}

void NowPlaying::rightAction()
{
    m_mediaPlayer->next();
}

void NowPlaying::confirmAction()
{
    m_mediaPlayer->togglePause();
}
