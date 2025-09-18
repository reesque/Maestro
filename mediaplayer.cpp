#include "mediaplayer.h"

#include <sstream>

#include <QDir>
#include <QDirIterator>
#include <QUrl>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/mp4file.h>
#include <taglib/mp4tag.h>
#include <taglib/mp4coverart.h>

#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

void ArtworkExtractor::fromMP3(const std::string& filePath, const std::string& outPath)
{
    TagLib::MPEG::File file(filePath.c_str());

    TagLib::ID3v2::Tag *id3v2tag = file.ID3v2Tag();
    if (!id3v2tag) {
        return;
    }

    TagLib::ID3v2::FrameList frames = id3v2tag->frameListMap()["APIC"];
    if (frames.isEmpty()) {
        return;
    }

    TagLib::ID3v2::AttachedPictureFrame *picFrame =
        static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frames.front());

    std::string mimeType = picFrame->mimeType().toCString();
    QString outImgPath = QString::fromStdString(outPath);
    if (mimeType == "image/jpeg")
    {
        outImgPath += ".jpg";
    }
    else if (mimeType == "image/png")
    {
        outImgPath += ".png";
    }
    else
    {
        outImgPath += ".img";
    }

    std::ofstream imgFile(outImgPath.toStdString(), std::ios::binary);
    imgFile.write((const char *)picFrame->picture().data(), picFrame->picture().size());
    imgFile.close();
}

void ArtworkExtractor::fromM4a(const std::string& filePath, const std::string& outPath)
{
    TagLib::MP4::File file(filePath.c_str());

    const TagLib::MP4::Item covrItem = file.tag()->item("covr");
    if (!covrItem.isValid())
    {
        return;
    }

    const TagLib::MP4::CoverArtList &coverList = covrItem.toCoverArtList();
    if (coverList.isEmpty())
    {
        return;
    }

    const TagLib::MP4::CoverArt &cover = coverList.front();

    QString outImgPath = QString::fromStdString(outPath);
    if (cover.format() == TagLib::MP4::CoverArt::JPEG) {
        outImgPath += ".jpg";
    } else if (cover.format() == TagLib::MP4::CoverArt::PNG) {
        outImgPath += ".png";
    } else {
        outImgPath += ".img";
    }

    std::ofstream imgFile(outImgPath.toStdString(), std::ios::binary);
    imgFile.write((const char *)cover.data().data(), cover.data().size());
    imgFile.close();
}

MediaPlayer::MediaPlayer(std::shared_ptr<Database> db, QObject *parent)
    : QObject{parent}
{
    m_db = db;
    m_player = new QMediaPlayer;
    m_playlist = new QMediaPlaylist;

    m_player->setPlaylist(m_playlist);

    // Check path exists
    QString appPath = QDir::homePath() + "/.config/maestro";
    if (!std::filesystem::exists(appPath.toStdString()))
    {
        std::filesystem::create_directory(appPath.toStdString());
    }

    m_artworkPath = appPath + "/artwork/";
    if (!std::filesystem::exists(m_artworkPath.toStdString()))
    {
        std::filesystem::create_directory(m_artworkPath.toStdString());
    }

    connect(m_playlist, &QMediaPlaylist::currentMediaChanged, this, &MediaPlayer::currentMediaChanged);
    connect(m_player, &QMediaPlayer::stateChanged, this, &MediaPlayer::onStateChanged);
}

MediaPlayer::~MediaPlayer()
{
    disconnect(m_player, &QMediaPlayer::currentMediaChanged, this, &MediaPlayer::currentMediaChanged);
    disconnect(m_player, &QMediaPlayer::stateChanged, this, &MediaPlayer::onStateChanged);
}

void MediaPlayer::currentMediaChanged(const QMediaContent &media)
{
    emit onTrackInfoUpdate(getCurrentTrackMetaData());
}

void MediaPlayer::playTrack(QVector<Track> queue, int position)
{
    m_playlist->clear();
    m_mediaQueue.clear();
    for (auto track : queue)
    {
        queueTrack(track.id);
        m_mediaQueue.push_back(track);
    }

    m_playlist->setCurrentIndex(position);
    m_player->play();
}

void MediaPlayer::queueTrack(int id)
{
    Track track = m_db->getTrack(id);
    m_playlist->addMedia(QUrl::fromLocalFile(track.filePath.c_str()));
}

void MediaPlayer::onStateChanged(QMediaPlayer::State state)
{
    switch (state)
    {
        case (QMediaPlayer::PlayingState):
        {
            emit onPlaybackStateChanged(PlaybackStatus::Playing);
            break;
        }
        case (QMediaPlayer::PausedState):
        {
            emit onPlaybackStateChanged(PlaybackStatus::Paused);
            break;
        }
        default:
        {
            emit onPlaybackStateChanged(PlaybackStatus::Stopped);
            break;
        }
    }
}

void MediaPlayer::reindex()
{
    // Clear db
    m_db->clearTable(Database::Table::Track);

    QString rootPath = QDir::homePath() + "/Music/";
    QStringList audioExtensions = {"*.mp3", "*.wav", "*.flac", "*.aac", "*.ogg", "*.m4a"};

    QDirIterator it(rootPath, audioExtensions, QDir::Files, QDirIterator::Subdirectories);

    std::vector<QString> files;
    while (it.hasNext()) {
        files.push_back(it.next());
    }

    for (size_t i = 0; i < files.size(); ++i) {
        QString currentPath = files[i];
        TagLib::FileRef f(currentPath.toStdString().c_str());

        // Check metadata
        if (!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();
            m_db->insertTrack(currentPath,
                               QString::fromStdWString(tag->title().toWString()),
                               QString::fromStdWString(tag->artist().toWString()),
                               QString::fromStdWString(tag->album().toWString()),
                               tag->track());

            // Check if album art is extracted
            QString basePath = m_artworkPath + tag->album().toCString();
            QString albumArtPathPng = basePath + ".png";
            QString albumArtPathJpg = basePath + ".jpg";

            std::filesystem::path pngPath {albumArtPathPng.toStdString()};
            std::filesystem::path jpgPath {albumArtPathJpg.toStdString()};

            if (!std::filesystem::exists(pngPath) and !std::filesystem::exists(jpgPath)) {
                std::filesystem::path mediaFilePath {currentPath.toStdString()};
                if (mediaFilePath.extension() == ".mp3")
                {
                    ArtworkExtractor::fromMP3(currentPath.toStdString(), basePath.toStdString());
                }
                else if (mediaFilePath.extension() == ".m4a")
                {
                    ArtworkExtractor::fromM4a(currentPath.toStdString(), basePath.toStdString());
                }
            }
        }

        emit onIndexProgress(i + 1, files.size());
    }
}

Track MediaPlayer::getTrackMetaData(int id)
{
    if (id < 1)
    {
        return Track();
    }

    return m_db->getTrack(id);
}

std::string MediaPlayer::getElapsedTime()
{
    if (m_player->mediaStatus() != QMediaPlayer::BufferedMedia)
    {
        return "00:00";
    }

    return formatTime(m_player->position());
}

std::string MediaPlayer::getRemainingTime()
{
    if (m_player->mediaStatus() != QMediaPlayer::BufferedMedia)
    {
        return "-00:00";
    }

    return "-" + formatTime(m_player->duration() - m_player->position());
}

int MediaPlayer::getPercentage()
{
    if (m_player->mediaStatus() != QMediaPlayer::BufferedMedia)
    {
        return 0;
    }

    return static_cast<int>(static_cast<float>(m_player->position()) / static_cast<float>(m_player->duration()) * 100);
}

Track MediaPlayer::getCurrentTrackMetaData()
{
    return getTrackMetaData(m_mediaQueue[m_playlist->currentIndex()].id);
}

std::string MediaPlayer::formatTime(qint64 ms) {
    int seconds = ms / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;

    return QString("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0')).toStdString();
}

bool MediaPlayer::isPlaying()
{
    return m_player->state() == QMediaPlayer::PlayingState;
}

void MediaPlayer::togglePause()
{
    if (isPlaying())
    {
        m_player->pause();
    }
    else
    {
        m_player->play();
    }
}

void MediaPlayer::next()
{
    m_playlist->next();
}

void MediaPlayer::previous()
{
    m_playlist->previous();
}

bool MediaPlayer::isMediaReady()
{
    return m_player->mediaStatus() == QMediaPlayer::BufferedMedia;
}
