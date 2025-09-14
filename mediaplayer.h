#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "database.h"

#include <QObject>
#include <QQueue>

#include <QMediaPlayer>

class MediaPlayer : public QObject
{
    Q_OBJECT
public:
    struct Track {
        std::string title;
        std::string artist;
        std::string album;

        Track();
        Track(const std::string& tTitle, const std::string& tArtist, const std::string& tAlbum);
    };

    explicit MediaPlayer(std::shared_ptr<Database> db, QObject *parent = nullptr);
    ~MediaPlayer();

    void reindex();
    Track getTrackMetaData(int id);
    Track getCurrentTrackMetaData();

signals:
    void onTrackInfoUpdate(Track track);

public slots:
    void playTrack(int id);

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QMediaPlayer *m_player;
    std::shared_ptr<Database> m_db;
    int m_currentTrackId;
};

Q_DECLARE_METATYPE(MediaPlayer::Track);

#endif // MEDIAPLAYER_H
