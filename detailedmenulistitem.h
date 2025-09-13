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
    explicit DetailedMenuListItem(const std::string& header, const std::string& subtext,
                                  std::function<void()> activator, QWidget *parent = nullptr);
    ~DetailedMenuListItem();

private:
    Ui::DetailedMenuListItem *ui;
};

#endif // DETAILEDMENULISTITEM_H
