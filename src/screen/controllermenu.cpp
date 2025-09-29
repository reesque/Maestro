#include "controllermenu.h"

ControllerMenu::ControllerMenu(std::shared_ptr<Settings> setting, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Setting;

    menuList->push_back(std::make_shared<SliderSettingMenuEntry>(
        "DPAD Responsiveness", 0, 10, 1, setting->getDpadResponsiveLevel(), [setting](QVariant arg){
            setting->setDpadResponsiveLevel(arg.toInt());
        },[](){}));
    menuList->push_back(std::make_shared<SliderSettingMenuEntry>(
        "Face Button Responsiveness", 0, 10, 1, setting->getFaceBtnResponsiveLevel(), [setting](QVariant arg){
            setting->setFaceBtnResponsiveLevel(arg.toInt());
        }, [](){}));
}

ControllerMenu::~ControllerMenu()
{}

SettingsSliderListItem* ControllerMenu::createDefaultItem()
{
    return new SettingsSliderListItem(ui->ListObject);
}

void ControllerMenu::updateListItem(std::shared_ptr<SliderSettingMenuEntry> entry, SettingsSliderListItem *widget)
{
    widget->setProperties(entry->label, entry->min, entry->max, entry->stepSize, entry->value);
    widget->setSideActivator(entry->slideAction);
}

void ControllerMenu::leftAction()
{
    static_cast<SettingsSliderListItem *>(ui->ListObject->itemWidget(ui->ListObject->currentItem()))->slide(false);
}

void ControllerMenu::rightAction()
{
    static_cast<SettingsSliderListItem *>(ui->ListObject->itemWidget(ui->ListObject->currentItem()))->slide(true);
}
