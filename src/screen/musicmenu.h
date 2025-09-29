#ifndef MUSICMENU_H
#define MUSICMENU_H

#include "menu.h"
#include "menulistitem.h"

class MusicMenu : public Menu<LabelMenuEntry, MenuListItem>
{
public:
    explicit MusicMenu(QWidget *parent = nullptr);
    ~MusicMenu() override;

protected:
    MenuListItem* createDefaultItem() override;
    void updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget) override;
};

#endif // MUSICMENU_H
