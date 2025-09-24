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

    populateMenu();
}

ControllerMenu::~ControllerMenu()
{}

SettingsSliderListItem* ControllerMenu::createListItem(std::shared_ptr<SliderSettingMenuEntry> entry)
{
    SettingsSliderListItem *item = new SettingsSliderListItem(entry->label, entry->min, entry->max,
                                                              entry->stepSize, entry->value, ui->ListObject);
    item->setSideActivator(entry->slideAction);
    return item;
}

void ControllerMenu::leftAction()
{
    static_cast<SettingsSliderListItem *>(ui->ListObject->itemWidget(ui->ListObject->currentItem()))->slide(false);
}

void ControllerMenu::rightAction()
{
    static_cast<SettingsSliderListItem *>(ui->ListObject->itemWidget(ui->ListObject->currentItem()))->slide(true);
}
