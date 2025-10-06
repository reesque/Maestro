#ifndef TWOSIDEDLISTITEM_H
#define TWOSIDEDLISTITEM_H

#include "basemenulistitem.h"
#include "menuentry.h"

namespace Ui {
class TwoSidedListItem;
}

class TwoSidedListItem : public QWidget,
    public BaseMenuListItem<TwoSidedLabelMenuEntry>
{
    Q_OBJECT

public:
    explicit TwoSidedListItem(QWidget *parent = nullptr);
    ~TwoSidedListItem() override;

    void updateItem() override;
    void onFocus() override;
    void onLoseFocus() override;

private:
    Ui::TwoSidedListItem *ui;
};

#endif // TWOSIDEDLISTITEM_H
