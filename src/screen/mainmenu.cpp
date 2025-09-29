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
}

MainMenu::~MainMenu()
{}

MenuListItem* MainMenu::createDefaultItem()
{
    return new MenuListItem(ui->ListObject);
}

void MainMenu::updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget)
{
    widget->setProperties(entry->label);
    widget->setActivator(entry->activator);
}
