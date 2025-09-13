#include "songsmenu.h"

SongsMenu::SongsMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    m_db = db;

    std::vector<Database::Track> trackList = db->getAllSongs();

    for (auto track : trackList)
    {
        menuList->push_back(std::make_shared<DetailedMenuEntry>(track.title, track.artist, [](){}));
    }

    populateMenu();
}

SongsMenu::~SongsMenu()
{}

DetailedMenuListItem* SongsMenu::createListItem(std::shared_ptr<DetailedMenuEntry> entry)
{
    return new DetailedMenuListItem(entry->header, entry->subtext, entry->activator, ui->ListObject);
}

