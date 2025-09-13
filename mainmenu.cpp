#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    Menu(parent)
{
    menuList->push_back(MenuEntry {"Music", [=](){switchScreenTo(ScreenType::Music);}});
    menuList->push_back(MenuEntry {"Videos", [](){}});
    menuList->push_back(MenuEntry {"Photos", [](){}});
    menuList->push_back(MenuEntry {"Settings", [](){}});
    menuList->push_back(MenuEntry {"Shuffle Songs", [](){}});
    menuList->push_back(MenuEntry {"Now Playing", [](){}});
    menuList->push_back(MenuEntry {"Quit", [](){}});

    populateMenu();
}

MainMenu::~MainMenu()
{}
