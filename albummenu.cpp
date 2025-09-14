#include "albummenu.h"

#include <QDir>
#include <QVector>
#include <QVariant>

#include <filesystem>

AlbumMenu::AlbumMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Music;
    m_db = db;

    ui->ListObject->setStyleSheet(
        "QListWidget::item { background-color: white; border-top: none; border-bottom: 1px solid #cccccc; }"
        "QListWidget::item:selected { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0096FF, stop:1 #0066CC); border: none; }"
    );

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

        menuList->push_back(std::make_shared<ArtworkMenuEntry>(album, artPath, [=](){
            QVector<QVariant> args;
            args.push_back(QVariant(QString::fromStdString(album)));
            emit switchScreenTo(ScreenType::SongsByAlbum, args);
        }));
    }

    populateMenu();
}

AlbumMenu::~AlbumMenu()
{}

ArtworkMenuListItem* AlbumMenu::createListItem(std::shared_ptr<ArtworkMenuEntry> entry)
{
    return new ArtworkMenuListItem(entry->header, entry->artPath, entry->activator, ui->ListObject);
}
