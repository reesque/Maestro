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
                                  const std::string& artworkPath, std::function<void()> activator,
                                  QWidget *parent = nullptr);
    ~DetailedMenuListItem() override;

private:
    Ui::DetailedMenuListItem *ui;
};

#endif // DETAILEDMENULISTITEM_H
