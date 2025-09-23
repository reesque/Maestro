#ifndef SETTINGSSLIDERLISTITEM_H
#define SETTINGSSLIDERLISTITEM_H

#include "basemenulistitem.h"

namespace Ui {
class SettingsSliderListItem;
}

class SettingsSliderListItem : public BaseMenuListItem
{
    Q_OBJECT

public:
    explicit SettingsSliderListItem(const std::string& label, int min, int max, int stepSize, int value,
                                std::function<void(int)> slideAction, std::function<void()> activator,
                                QWidget *parent = nullptr);
    ~SettingsSliderListItem();
    void slide(bool isForward);

private:
    Ui::SettingsSliderListItem *ui;

    int m_min;
    int m_max;
    int m_stepSize;
    std::function<void(int)> m_slideAction;
};

#endif // SETTINGSSLIDERLISTITEM_H
