#ifndef CONTROLLERMENU_H
#define CONTROLLERMENU_H

#include "menu.h"
#include "settings.h"
#include "settingssliderlistitem.h"

class ControllerMenu : public Menu<SliderSettingMenuEntry, SettingsSliderListItem>
{
public:
    explicit ControllerMenu(std::shared_ptr<Settings> setting, QWidget *parent = nullptr);
    ~ControllerMenu() override;

protected:
    SettingsSliderListItem* createDefaultItem() override;
    void updateListItem(std::shared_ptr<SliderSettingMenuEntry> entry, SettingsSliderListItem *widget) override;

protected slots:
    void leftAction() override;
    void rightAction() override;
};

#endif // CONTROLLERMENU_H
