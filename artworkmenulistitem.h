#ifndef ARTWORKMENULISTITEM_H
#define ARTWORKMENULISTITEM_H

#include "basemenulistitem.h"

namespace Ui {
class ArtworkMenuListItem;
}

class ArtworkMenuListItem : public BaseMenuListItem
{
    Q_OBJECT

public:
    explicit ArtworkMenuListItem(const std::string& header,
                                 std::function<void()> activator, QWidget *parent = nullptr);
    ~ArtworkMenuListItem();

private:
    Ui::ArtworkMenuListItem *ui;
};

#endif // ARTWORKMENULISTITEM_H
