#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "database.h"
#include "datastruct.h"

#include <QObject>
#include <QQueue>

#include <QMediaPlayer>
#include <QMediaPlaylist>

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
    explicit MediaPlayer(std::shared_ptr<Database> db, QObject *parent = nullptr);
    ~MediaPlayer();

    void reindex();
    Track getTrackMetaData(int id);
    Track getCurrentTrackMetaData();
    std::string getElapsedTime();
    std::string getRemainingTime();
    int getPercentage();
    bool isPlaying();
    bool isMediaReady();
    void togglePause();
    void next();
    void previous();

signals:
    void onTrackInfoUpdate(Track track);
    void onIndexProgress(int progress, int total);
    void onPlaybackStateChanged(PlaybackStatus playbackStatus);

public slots:
    void playTrack(QVector<Track> queue, int position);
    void queueTrack(int id);

private slots:
    void currentMediaChanged(const QMediaContent &media);
    void onStateChanged(QMediaPlayer::State state);

private:
    std::string formatTime(qint64 ms);

private:
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    std::shared_ptr<Database> m_db;
    QString m_artworkPath;
    std::vector<Track> m_mediaQueue;
};

#endif // MEDIAPLAYER_H
