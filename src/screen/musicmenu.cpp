#include "musicmenu.h"

MusicMenu::MusicMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Main;

    menuList->push_back(std::make_shared<LabelMenuEntry>("Songs",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::Songs);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Albums",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::Album);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Artists",
        [=](std::shared_ptr<LabelMenuEntry>){switchScreenTo(ScreenType::Artist);}));
}

MusicMenu::~MusicMenu()
{}

MenuListItem* MusicMenu::createDefaultItem()
{
    return new MenuListItem(ui->ListObject);
}

void MusicMenu::updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget)
{
    widget->setProperties(entry);
}
