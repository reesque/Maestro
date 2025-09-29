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

MenuListItem* SettingMenu::createDefaultItem()
{
    return new MenuListItem(ui->ListObject);
}

void SettingMenu::updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget)
{
    widget->setProperties(entry->label);
    widget->setActivator(entry->activator);
}
