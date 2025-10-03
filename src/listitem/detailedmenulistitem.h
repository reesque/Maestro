#ifndef DETAILEDMENULISTITEM_H
#define DETAILEDMENULISTITEM_H

#include "basemenulistitem.h"
#include "menuentry.h"

namespace Ui {
class DetailedMenuListItem;
}

class DetailedMenuListItem : public QWidget,
    public BaseMenuListItem<DetailedMenuEntry>
{
    Q_OBJECT

public:
    explicit DetailedMenuListItem(QWidget *parent = nullptr);
    ~DetailedMenuListItem() override;

    void updateItem() override;
    void onFocus() override;
    void onLoseFocus() override;

private:
    Ui::DetailedMenuListItem *ui;
};

#endif // DETAILEDMENULISTITEM_H
