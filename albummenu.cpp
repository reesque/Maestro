#include "albummenu.h"

#include <QDir>

#include <filesystem>

AlbumMenu::AlbumMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Music;
    m_db = db;

    QString artworkPath = QDir::homePath() + "/.config/maestro/artwork/";
    for (auto album : m_db->getAllAlbums())
    {
        // Check if artwork is available
        QString trackArtworkPath = artworkPath + album.c_str();
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

        menuList->push_back(std::make_shared<ArtworkMenuEntry>(album, artPath, [](){}));
    }

    populateMenu();
}

AlbumMenu::~AlbumMenu()
{}

ArtworkMenuListItem* AlbumMenu::createListItem(std::shared_ptr<ArtworkMenuEntry> entry)
{
    return new ArtworkMenuListItem(entry->header, entry->artPath, entry->activator, ui->ListObject);
}
