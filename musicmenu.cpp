#include "musicmenu.h"

MusicMenu::MusicMenu(QWidget *parent) :
    Menu(parent)
{
    menuList->push_back(std::make_shared<LabelMenuEntry>("Songs", [=](){switchScreenTo(ScreenType::Songs);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Albums", [=](){switchScreenTo(ScreenType::Main);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Artists", [](){}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Playlists", [](){}));

    populateMenu();
}

MusicMenu::~MusicMenu()
{}

MenuListItem* MusicMenu::createListItem(std::shared_ptr<LabelMenuEntry> entry)
{
    return new MenuListItem(entry->label, entry->activator, ui->ListObject);
}
