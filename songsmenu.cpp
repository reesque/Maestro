#include "songsmenu.h"

#include <QDir>

#include <filesystem>

SongsMenu::SongsMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Music;
    m_db = db;

    fillSongRecords(db->getAllTracks());
}

SongsMenu::SongsMenu(std::shared_ptr<Database> db, Filter filter, std::string byValue, QWidget *parent) :
    Menu(parent)
{
    m_db = db;

    switch (filter)
    {
        case Filter::Album:
        {
            prevScreen = ScreenType::Album;
            fillSongRecords(db->getTracksByAlbum(byValue));
            break;
        }
        case Filter::Artist:
        {
            break;
        }
    }
}

SongsMenu::~SongsMenu()
{}

DetailedMenuListItem* SongsMenu::createListItem(std::shared_ptr<DetailedMenuEntry> entry)
{
    return new DetailedMenuListItem(entry->header, entry->subtext, entry->artPath, entry->activator, ui->ListObject);
}

void SongsMenu::fillSongRecords(std::vector<Database::Track> records)
{
    QString artworkPath = QDir::homePath() + "/.config/maestro/artwork/";
    //for (auto track : db->getAllTracks())
    for (auto track : records)
    {
        // Check if artwork is available
        QString trackArtworkPath = artworkPath + track.album.c_str();
        QString trackArtPathPng = trackArtworkPath + ".png";
        QString trackArtPathJpg = trackArtworkPath + ".jpg";
        std::string artPath = "";
        if (std::filesystem::exists(trackArtPathPng.toStdString()))
        {
            artPath = trackArtPathPng.toStdString();
        }
        else if (std::filesystem::exists(trackArtPathJpg.toStdString()))
        {
            artPath = trackArtPathJpg.toStdString();
        }

        // Create menu list
        menuList->push_back(std::make_shared<DetailedMenuEntry>(
            track.title, track.artist, artPath, [=](){
                emit switchScreenTo(ScreenType::NowPlaying);
                emit playTrack(track.id);
            }
        ));
    }

    populateMenu();
}

