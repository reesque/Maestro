#include "controllermenu.h"

ControllerMenu::ControllerMenu(std::shared_ptr<Settings> setting, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Setting;

    menuList->push_back(std::make_shared<SliderSettingMenuEntry>(
        "DPAD Responsiveness", 0, 50, 1, setting->getDpadResponsiveLevel(),
        [=](std::shared_ptr<SliderSettingMenuEntry> entry){
            setting->setDpadResponsiveLevel(entry->value);
        }
    ));
    menuList->push_back(std::make_shared<SliderSettingMenuEntry>(
        "Face Button Responsiveness", 0, 50, 1, setting->getFaceBtnResponsiveLevel(),
        [=](std::shared_ptr<SliderSettingMenuEntry> entry){
            setting->setFaceBtnResponsiveLevel(entry->value);
        }
    ));
}

ControllerMenu::~ControllerMenu()
{}

SettingsSliderListItem* ControllerMenu::createDefaultItem()
{
    return new SettingsSliderListItem(ui->ListObject);
}

void ControllerMenu::updateListItem(std::shared_ptr<SliderSettingMenuEntry> entry, SettingsSliderListItem *widget)
{
    widget->setProperties(entry);
}

void ControllerMenu::leftAction()
{
    static_cast<SettingsSliderListItem *>(ui->ListObject->itemWidget(ui->ListObject->currentItem()))->slide(false);
}

void ControllerMenu::rightAction()
{
    static_cast<SettingsSliderListItem *>(ui->ListObject->itemWidget(ui->ListObject->currentItem()))->slide(true);
}
