#include "mediaplayer.h"

#include <sstream>

#include <QDir>
#include <QDirIterator>
#include <QUrl>
#include <taglib/fileref.h>
#include <taglib/tag.h>

MediaPlayer::Track::Track(const std::string& tTitle, const std::string& tArtist, const std::string& tAlbum)
{
    title = tTitle;
    artist = tArtist;
    album = tAlbum;
}

MediaPlayer::Track::Track()
{
    title = "Unknown";
    artist = "Unknown";
    album = "Unknown";
}

MediaPlayer::MediaPlayer(std::shared_ptr<Database> db, QObject *parent)
    : QObject{parent}
{
    m_db = db;
    m_player = new QMediaPlayer;

    m_currentTrackId = -1;

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::onMediaStatusChanged);
}

MediaPlayer::~MediaPlayer()
{}

void MediaPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::BufferedMedia) {
        emit onTrackInfoUpdate(getCurrentTrackMetaData());
    }
}

void MediaPlayer::playTrack(int id)
{
    Database::Track track = m_db->getTrack(id);
    m_currentTrackId = id;

    m_player->setMedia(QUrl::fromLocalFile(track.filePath.c_str()));
    m_player->play();
}

void MediaPlayer::reindex()
{
    // Clear db
    m_db->clearTable(Database::Table::Track);

    QString rootPath = QDir::homePath() + "/Music/";
    QStringList audioExtensions = {"*.mp3", "*.wav", "*.flac", "*.aac", "*.ogg", "*.m4a"};

    QDirIterator it(rootPath, audioExtensions, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString currentPath = it.next();
        TagLib::FileRef f(currentPath.toStdString().c_str());

        if (!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();
            m_db->insertTrack(currentPath,
                               QString::fromStdWString(tag->title().toWString()),
                               QString::fromStdWString(tag->artist().toWString()),
                               QString::fromStdWString(tag->album().toWString()));
        }
    }
}

MediaPlayer::Track MediaPlayer::getTrackMetaData(int id)
{
    if (id < 1)
    {
        return Track();
    }

    Database::Track track = m_db->getTrack(id);
    MediaPlayer::Track trackMetaData;

    trackMetaData.title = track.title;
    trackMetaData.artist = track.artist;
    trackMetaData.album = track.album;

    return trackMetaData;
}

MediaPlayer::Track MediaPlayer::getCurrentTrackMetaData()
{
    return getTrackMetaData(m_currentTrackId);
}
