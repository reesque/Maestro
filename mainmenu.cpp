#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    Menu(parent)
{
    menuList->push_back(std::make_shared<LabelMenuEntry>("Music", [=](){switchScreenTo(ScreenType::Music);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Videos", [](){}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Photos", [](){}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Settings", [](){}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Shuffle Songs", [](){}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Now Playing", [](){}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Quit", [](){}));

    populateMenu();
}

MainMenu::~MainMenu()
{}

MenuListItem* MainMenu::createListItem(std::shared_ptr<LabelMenuEntry> entry)
{
    return new MenuListItem(entry->label, entry->activator, ui->ListObject);
}
