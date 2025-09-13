#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.h"

class MainMenu : public Menu
{
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu() override;
};

#endif // MAINMENU_H
