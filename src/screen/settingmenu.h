#ifndef SETTINGMENU_H
#define SETTINGMENU_H

#include "menu.h"
#include "menulistitem.h"

class SettingMenu : public Menu<LabelMenuEntry, MenuListItem>
{
public:
    explicit SettingMenu(QWidget *parent = nullptr);
    ~SettingMenu() override;

protected:
    MenuListItem* createDefaultItem() override;
    void updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget) override;
};

#endif // SETTINGMENU_H
