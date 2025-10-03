#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::None;

    menuList->push_back(std::make_shared<LabelMenuEntry>("Music",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::Music);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Settings",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::Setting);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Shuffle Songs",
        [](std::shared_ptr<LabelMenuEntry>){}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Now Playing",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::NowPlaying);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Quit",
        [](std::shared_ptr<LabelMenuEntry>){QApplication::quit();}));
}

MainMenu::~MainMenu()
{}

MenuListItem* MainMenu::createDefaultItem()
{
    return new MenuListItem(ui->ListObject);
}

void MainMenu::updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget)
{
    widget->setProperties(entry);
}
