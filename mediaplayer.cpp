#include "mediaplayer.h"

#include <sstream>

#include <QDir>
#include <QDirIterator>
#include <taglib/fileref.h>
#include <taglib/tag.h>

MediaPlayer::Track::Track(const std::string& tTitle, const std::string& tArtist, const std::string& tAlbum)
{
    title = tTitle;
    artist = tArtist;
    album = tAlbum;
}

MediaPlayer::MediaPlayer(std::shared_ptr<Database> db, QObject *parent)
    : QObject{parent}
{
    m_db = db;
    m_player = new QMediaPlayer;

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::onMediaStatusChanged);
}

MediaPlayer::~MediaPlayer()
{}

void MediaPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        return;
    }

    m_currentTrack = nullptr;
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
