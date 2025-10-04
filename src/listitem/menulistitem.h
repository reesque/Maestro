#ifndef MENULISTITEM_H
#define MENULISTITEM_H

#include "basemenulistitem.h"
#include "menuentry.h"

namespace Ui {
class MenuListItem;
}

class MenuListItem : public QWidget,
    public BaseMenuListItem<LabelMenuEntry>
{
    Q_OBJECT

public:
    explicit MenuListItem(QWidget *parent = nullptr);
    ~MenuListItem() override;

    void updateItem() override;
    void onFocus() override;
    void onLoseFocus() override;

private:
    Ui::MenuListItem *ui;
};

#endif // MENULISTITEM_H
