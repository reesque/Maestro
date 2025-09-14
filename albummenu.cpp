#include "albummenu.h"

AlbumMenu::AlbumMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Music;

    m_db = db;

    for (auto album : m_db->getAllAlbums())
    {
        menuList->push_back(std::make_shared<LabelMenuEntry>(album, [](){}));
    }

    populateMenu();
}

AlbumMenu::~AlbumMenu()
{}

ArtworkMenuListItem* AlbumMenu::createListItem(std::shared_ptr<LabelMenuEntry> entry)
{
    return new ArtworkMenuListItem(entry->label, entry->activator, ui->ListObject);
}
