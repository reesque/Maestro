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

        // Check metadata
        if (!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();
            m_db->insertTrack(currentPath,
                               QString::fromStdWString(tag->title().toWString()),
                               QString::fromStdWString(tag->artist().toWString()),
                               QString::fromStdWString(tag->album().toWString()));

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

    return static_cast<int>(static_cast<float>(m_player->position()) / static_cast<float>(m_player->duration()) * 1000);
}

MediaPlayer::Track MediaPlayer::getCurrentTrackMetaData()
{
    return getTrackMetaData(m_currentTrackId);
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
