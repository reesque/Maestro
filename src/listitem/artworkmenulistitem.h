#ifndef ARTWORKMENULISTITEM_H
#define ARTWORKMENULISTITEM_H

#include "basemenulistitem.h"
#include "menuentry.h"

namespace Ui {
class ArtworkMenuListItem;
}

class ArtworkMenuListItem : public QWidget,
    public BaseMenuListItem<ArtworkMenuEntry>
{
    Q_OBJECT

public:
    explicit ArtworkMenuListItem(QWidget *parent = nullptr);
    ~ArtworkMenuListItem();

    void updateItem() override;
    void onFocus() override;
    void onLoseFocus() override;

private:
    Ui::ArtworkMenuListItem *ui;
};

#endif // ARTWORKMENULISTITEM_H
