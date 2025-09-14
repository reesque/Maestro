#include "songsmenu.h"

#include <QDir>

#include <filesystem>

SongsMenu::SongsMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Music;
    m_db = db;

    QString artworkPath = QDir::homePath() + "/.config/maestro/artwork/";
    for (auto track : db->getAllTracks())
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

SongsMenu::~SongsMenu()
{}

DetailedMenuListItem* SongsMenu::createListItem(std::shared_ptr<DetailedMenuEntry> entry)
{
    return new DetailedMenuListItem(entry->header, entry->subtext, entry->artPath, entry->activator, ui->ListObject);
}

