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
    explicit ArtworkMenuListItem(QWidget *parent = nullptr);
    ~ArtworkMenuListItem();

    void setProperties(const std::string& header, const std::string& artworkPath);
    void onFocus() override;
    void onLoseFocus() override;

private:
    Ui::ArtworkMenuListItem *ui;
};

#endif // ARTWORKMENULISTITEM_H
