#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "database.h"

#include <QObject>
#include <QQueue>

#include <QMediaPlayer>

class ArtworkExtractor
{
public:
    ArtworkExtractor(const ArtworkExtractor&) = delete;
    ArtworkExtractor& operator=(const ArtworkExtractor&) = delete;

    static void fromMP3(const std::string& filePath, const std::string& outPath);
    static void fromM4a(const std::string& filePath, const std::string& outPath);

private:
    ArtworkExtractor() = delete;
    ~ArtworkExtractor() = delete;
};

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
    std::string getElapsedTime();
    std::string getRemainingTime();
    int getPercentage();
    bool isPlaying();

signals:
    void onTrackInfoUpdate(Track track);

public slots:
    void playTrack(int id);

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    std::string formatTime(qint64 ms);

private:
    QMediaPlayer *m_player;
    std::shared_ptr<Database> m_db;
    int m_currentTrackId;
    QString m_artworkPath;
};

Q_DECLARE_METATYPE(MediaPlayer::Track);

#endif // MEDIAPLAYER_H
