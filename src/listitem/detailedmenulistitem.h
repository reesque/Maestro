#ifndef DETAILEDMENULISTITEM_H
#define DETAILEDMENULISTITEM_H

#include "basemenulistitem.h"

namespace Ui {
class DetailedMenuListItem;
}

class DetailedMenuListItem : public BaseMenuListItem
{
    Q_OBJECT

public:
    explicit DetailedMenuListItem(QWidget *parent = nullptr);
    ~DetailedMenuListItem() override;

    void setProperties(const std::string& header,
                       const std::string& subtext,
                       const std::string& artworkPath);
    void onFocus() override;
    void onLoseFocus() override;

private:
    Ui::DetailedMenuListItem *ui;
};

#endif // DETAILEDMENULISTITEM_H
