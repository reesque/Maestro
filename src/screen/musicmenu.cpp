#include "musicmenu.h"

MusicMenu::MusicMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Main;

    menuList->push_back(std::make_shared<LabelMenuEntry>("Songs", [=](){switchScreenTo(ScreenType::Songs);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Albums", [=](){switchScreenTo(ScreenType::Album);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Artists", [=](){switchScreenTo(ScreenType::Artist);}));

    populateMenu();
}

MusicMenu::~MusicMenu()
{}

MenuListItem* MusicMenu::createListItem(std::shared_ptr<LabelMenuEntry> entry)
{
    MenuListItem *item = new MenuListItem(entry->label, ui->ListObject);
    item->setActivator(entry->activator);
    return item;
}
