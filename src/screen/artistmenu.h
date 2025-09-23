#ifndef ARTISTMENU_H
#define ARTISTMENU_H

#include "database.h"
#include "menu.h"
#include "menulistitem.h"

class ArtistMenu : public Menu<LabelMenuEntry, MenuListItem>
{
public:
    explicit ArtistMenu(std::shared_ptr<Database> db, QWidget *parent = nullptr);
    ~ArtistMenu() override;

protected:
    MenuListItem* createListItem(std::shared_ptr<LabelMenuEntry> entry) override;
};

#endif // ARTISTMENU_H
