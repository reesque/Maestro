#include "nowplaying.h"
#include "ui_nowplaying.h"

#include <QDir>

#include <filesystem>

void RoundedProgressBarStyle::drawControl(ControlElement element, const QStyleOption* option,
                     QPainter* painter, const QWidget* widget) const {
    if (element == CE_ProgressBarContents)
    {
        const QStyleOptionProgressBar* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option);
        if (!progressBarOption)
        {
            return;
        }

        QRect rect = progressBarOption->rect;
        qreal radius = rect.height() / 2.0;

        double percent = (double)(progressBarOption->progress - progressBarOption->minimum) /
                         (progressBarOption->maximum - progressBarOption->minimum);

        QRectF chunkRect = rect.adjusted(0, 0, -(1.0 - percent) * rect.width(), 0);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(QColor("#000000"));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(chunkRect, radius, radius);
        painter->restore();
    }
    else if (element == CE_ProgressBarGroove)
    {
        const QStyleOptionProgressBar* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option);
        if (!progressBarOption) {
            return;
        }

        QRect rect = progressBarOption->rect;
        qreal radius = rect.height() / 2.0;

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(QColor("#aaaaaa"));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(rect, radius, radius);
        painter->restore();
    }
    else {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}

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

    // Keyboard config
    connect(leftKey.get(), &QShortcut::activated, this, &NowPlaying::leftAction);
    connect(rightKey.get(), &QShortcut::activated, this, &NowPlaying::rightAction);
    connect(confirmKey.get(), &QShortcut::activated, this, &NowPlaying::confirmAction);
}

NowPlaying::~NowPlaying()
{
    disconnect(m_mediaPlayer.get(), &MediaPlayer::onTrackInfoUpdate, this, &NowPlaying::onTrackInfoUpdate);
    disconnect(seekTimer.get(), &QTimer::timeout, this, &NowPlaying::tickSeekBar);
    disconnect(leftKey.get(), &QShortcut::activated, this, &NowPlaying::leftAction);
    disconnect(rightKey.get(), &QShortcut::activated, this, &NowPlaying::rightAction);
    disconnect(confirmKey.get(), &QShortcut::activated, this, &NowPlaying::confirmAction);

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
