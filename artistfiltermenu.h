#ifndef ARTISTFILTERMENU_H
#define ARTISTFILTERMENU_H

#include "menu.h"
#include "menulistitem.h"

class ArtistFilterMenu : public Menu<LabelMenuEntry, MenuListItem>
{
public:
    explicit ArtistFilterMenu(const std::string& artistName, QWidget *parent = nullptr);
    ~ArtistFilterMenu() override;

protected:
    MenuListItem* createListItem(std::shared_ptr<LabelMenuEntry> entry) override;
};

#endif // ARTISTFILTERMENU_H
