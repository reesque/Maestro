#ifndef MENUWITHTOGGLELISTITEM_H
#define MENUWITHTOGGLELISTITEM_H

#include "basemenulistitem.h"
#include "menuentry.h"

namespace Ui {
class MenuWithToggleListItem;
}

class MenuWithToggleListItem : public QWidget,
    public BaseMenuListItem<LabelWithToggleMenuEntry>
{
    Q_OBJECT

public:
    explicit MenuWithToggleListItem(QWidget *parent = nullptr);
    ~MenuWithToggleListItem() override;

    void updateItem() override;
    void onFocus() override;
    void onLoseFocus() override;

    void activate() override;

private:
    Ui::MenuWithToggleListItem *ui;
};

#endif // MENUWITHTOGGLELISTITEM_H
