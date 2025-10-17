#include "nowplaying.h"
#include "ui_nowplaying.h"

#include "roundedprogressbarstyle.h"

#include <QDir>
#include <QPainter>
#include <QPainterPath>

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
    ui->Title->startScrolling();
    ui->Artist->startScrolling();
    ui->Album->startScrolling();

    seekTimer = std::make_unique<QTimer>();
    connect(seekTimer.get(), &QTimer::timeout, this, &NowPlaying::tickSeekBar);
    seekTimer->start(10);

    connect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);
    if (m_mediaPlayer->isMediaReady())
    {
        onTrackInfoUpdate(m_mediaPlayer->getCurrentTrackMetaData());
    }
    else
    {
        reset();
    }

    connect(m_mediaPlayer.get(), &MediaPlayer::onPlaybackModeChanged, this, &NowPlaying::onPlaybackModeChanged);
    setPlaybackMode(m_mediaPlayer->getPlaybackMode());
}

NowPlaying::~NowPlaying()
{
    disconnect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);
    disconnect(seekTimer.get(), &QTimer::timeout, this, &NowPlaying::tickSeekBar);
    disconnect(m_mediaPlayer.get(), &MediaPlayer::onPlaybackModeChanged, this, &NowPlaying::onPlaybackModeChanged);

    delete ui;
}

void NowPlaying::onTrackInfoUpdate(Track track)
{
    if (track == Track::NonExist())
    {
        reset();
        return;
    }

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
        ui->CoverArt->setPixmap(roundPixmapCorner(QPixmap(QString::fromStdString(artPath)), 20));
    }
}

QPixmap NowPlaying::roundPixmapCorner(const QPixmap& src, float radius)
{
    if (src.isNull())
            return QPixmap();

    QPixmap dest(src.size());
    dest.fill(Qt::transparent);

    QPainter painter(&dest);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(src.rect(), radius, radius);

    painter.setClipPath(path);
    painter.drawPixmap(0, 0, src);

    return dest;
}

void NowPlaying::reset()
{
    ui->Title->setText("");
    ui->Artist->setText("");
    ui->Album->setText("");

    ui->TimeLeft->setText("00:00");
    ui->TimeRight->setText("-00:00");
    ui->Seekbar->setValue(0);

    ui->CoverArt->setPixmap(roundPixmapCorner(QPixmap(":/app/assets/cover.png"), 20));
}

void NowPlaying::onPlaybackModeChanged(QMediaPlaylist::PlaybackMode mode)
{
    setPlaybackMode(mode);
}

void NowPlaying::setPlaybackMode(QMediaPlaylist::PlaybackMode mode)
{
    if (mode == QMediaPlaylist::Sequential)
    {
        ui->RepeatIcon->setPixmap(QPixmap(":/app/assets/repeat.png"));
        ui->ShuffleIcon->hide();
    }
    else if (mode == QMediaPlaylist::CurrentItemInLoop)
    {
        ui->RepeatIcon->setPixmap(QPixmap(":/app/assets/repeat_once.png"));
        ui->ShuffleIcon->hide();
    }
    else if (mode == QMediaPlaylist::Random)
    {
        ui->RepeatIcon->setPixmap(QPixmap(":/app/assets/repeat.png"));
        ui->ShuffleIcon->show();
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

void NowPlaying::extra1Action()
{
    m_mediaPlayer->stop();
}

void NowPlaying::extra2Action()
{
    m_mediaPlayer->togglePlaybackMode();
}
