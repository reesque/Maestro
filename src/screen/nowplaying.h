#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include "database.h"
#include "datastruct.h"
#include "mediaplayer.h"
#include "screen.h"

#include <QTimer>

namespace Ui {
class NowPlaying;
}

class NowPlaying : public Screen
{
    Q_OBJECT

public:
    explicit NowPlaying(std::shared_ptr<Database> db, std::shared_ptr<MediaPlayer> mediaPlayer, QWidget *parent = nullptr);
    ~NowPlaying() override;

protected slots:
    void leftAction() override;
    void rightAction() override;
    void confirmAction() override;
    void extra1Action() override;
    void extra2Action() override;

private slots:
    void onTrackInfoUpdate(Track track);
    void onPlaybackModeChanged(QMediaPlaylist::PlaybackMode mode);

private:
    void tickSeekBar();
    void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);
    void reset();
    QPixmap roundPixmapCorner(const QPixmap& src, float radius);

private:
    Ui::NowPlaying *ui;
    std::unique_ptr<QTimer> seekTimer;
    std::shared_ptr<Database> m_db;
    std::shared_ptr<MediaPlayer> m_mediaPlayer;
};

#endif // NOWPLAYING_H
