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

        Track(const std::string& tTitle, const std::string& tArtist, const std::string& tAlbum);
    };

    explicit MediaPlayer(QObject *parent = nullptr);
    ~MediaPlayer();

    void reindex();

signals:
    void clearDBTable(const Database::Table& table);
    void insertDBTrack(const QString& filePath, const QString& title,
                const QString& artist, const QString& album);

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QMediaPlayer *m_player;
    std::unique_ptr<Track> m_currentTrack;
};

#endif // MEDIAPLAYER_H
