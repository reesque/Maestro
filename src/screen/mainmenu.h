#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.h"
#include "menulistitem.h"

class MainMenu : public Menu<LabelMenuEntry, MenuListItem>
{
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu() override;

protected:
    MenuListItem* createListItem(std::shared_ptr<LabelMenuEntry> entry) override;
};

#endif // MAINMENU_H
