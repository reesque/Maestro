#include "settingmenu.h"

SettingMenu::SettingMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Main;

    menuList->push_back(std::make_shared<LabelMenuEntry>("Sync Library", [=](){switchScreenTo(ScreenType::Reindex);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("Controller", [=](){switchScreenTo(ScreenType::Controller);}));
}

SettingMenu::~SettingMenu()
{}

MenuListItem* SettingMenu::createListItem(std::shared_ptr<LabelMenuEntry> entry)
{
    MenuListItem *item = new MenuListItem(entry->label, ui->ListObject);
    item->setActivator(entry->activator);
    return item;
}
