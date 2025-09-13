#ifndef MUSICMENU_H
#define MUSICMENU_H

#include "menu.h"

class MusicMenu : public Menu
{
public:
    explicit MusicMenu(QWidget *parent = nullptr);
    ~MusicMenu() override;
};

#endif // MUSICMENU_H
