#ifndef SETTINGSSLIDERLISTITEM_H
#define SETTINGSSLIDERLISTITEM_H

#include "basemenulistitem.h"
#include "menuentry.h"

namespace Ui {
class SettingsSliderListItem;
}

class SettingsSliderListItem : public QWidget,
    public BaseMenuListItem<SliderSettingMenuEntry>
{
    Q_OBJECT

public:
    explicit SettingsSliderListItem(QWidget *parent = nullptr);
    ~SettingsSliderListItem();

    void updateItem() override;
    void slide(bool isForward);

private:
    Ui::SettingsSliderListItem *ui;
};

#endif // SETTINGSSLIDERLISTITEM_H
