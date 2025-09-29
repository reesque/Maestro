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
    explicit SettingsSliderListItem(QWidget *parent = nullptr);
    ~SettingsSliderListItem();

    void setProperties(const std::string& label, int min, int max, int stepSize, int value);
    void slide(bool isForward);

private:
    Ui::SettingsSliderListItem *ui;

    int m_min;
    int m_max;
    int m_stepSize;
};

#endif // SETTINGSSLIDERLISTITEM_H
