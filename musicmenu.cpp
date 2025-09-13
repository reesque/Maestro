#include "musicmenu.h"

MusicMenu::MusicMenu(QWidget *parent) :
    Menu(parent)
{
    menuList->push_back(MenuEntry {"Songs", [](){}});
    menuList->push_back(MenuEntry {"Albums", [](){}});
    menuList->push_back(MenuEntry {"Artists", [](){}});
    menuList->push_back(MenuEntry {"Playlists", [](){}});

    populateMenu();
}

MusicMenu::~MusicMenu()
{}
