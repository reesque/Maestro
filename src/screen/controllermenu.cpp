#include "controllermenu.h"

ControllerMenu::ControllerMenu(std::shared_ptr<Settings> setting, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Setting;

    menuList->push_back(std::make_shared<SliderSettingMenuEntry>(
        "DPAD Responsiveness", 0, 10, 1, setting->getDpadResponsiveLevel(), [setting](int value){
            setting->setDpadResponsiveLevel(value);
        },[=](){}));
    menuList->push_back(std::make_shared<SliderSettingMenuEntry>(
        "Face Button Responsiveness", 0, 10, 1, setting->getFaceBtnResponsiveLevel(), [setting](int value){
            setting->setFaceBtnResponsiveLevel(value);
        }, [=](){}));

    populateMenu();
}

ControllerMenu::~ControllerMenu()
{}

SettingsSliderListItem* ControllerMenu::createListItem(std::shared_ptr<SliderSettingMenuEntry> entry)
{
    return new SettingsSliderListItem(entry->label, entry->min, entry->max, entry->stepSize, entry->value,
                                      entry->slideAction, entry->activator, ui->ListObject);
}

void ControllerMenu::leftAction()
{
    static_cast<SettingsSliderListItem *>(ui->ListObject->itemWidget(ui->ListObject->currentItem()))->slide(false);
}

void ControllerMenu::rightAction()
{
    static_cast<SettingsSliderListItem *>(ui->ListObject->itemWidget(ui->ListObject->currentItem()))->slide(true);
}
