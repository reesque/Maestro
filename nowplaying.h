#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include "database.h"
#include "mediaplayer.h"
#include "screen.h"

namespace Ui {
class NowPlaying;
}

class NowPlaying : public Screen
{
    Q_OBJECT

public:
    explicit NowPlaying(std::shared_ptr<Database> db, std::shared_ptr<MediaPlayer> mediaPlayer, QWidget *parent = nullptr);
    ~NowPlaying();

private slots:
    void onTrackInfoUpdate(MediaPlayer::Track track);

private:
    Ui::NowPlaying *ui;
    std::shared_ptr<Database> m_db;
    std::shared_ptr<MediaPlayer> m_mediaPlayer;
};

#endif // NOWPLAYING_H
