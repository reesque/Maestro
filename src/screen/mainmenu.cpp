#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::None;

    menuList->push_back(std::make_shared<LabelMenuEntry>("Music", [=](){switchScreenTo(ScreenType::Music);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Settings", [=](){switchScreenTo(ScreenType::Setting);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Shuffle Songs", [](){}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Now Playing", [=](){switchScreenTo(ScreenType::NowPlaying);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Quit", [](){QApplication::quit();}));

    populateMenu();
}

MainMenu::~MainMenu()
{}

MenuListItem* MainMenu::createListItem(std::shared_ptr<LabelMenuEntry> entry)
{
    MenuListItem *item = new MenuListItem(entry->label, ui->ListObject);
    item->setActivator(entry->activator);
    return item;
}
