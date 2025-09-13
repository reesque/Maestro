#ifndef SONGSMENU_H
#define SONGSMENU_H

#include "database.h"
#include "menu.h"
#include "detailedmenulistitem.h"

class SongsMenu : public Menu<DetailedMenuEntry, DetailedMenuListItem>
{
public:
    explicit SongsMenu(std::shared_ptr<Database> db, QWidget *parent = nullptr);
    ~SongsMenu() override;

protected:
    DetailedMenuListItem* createListItem(std::shared_ptr<DetailedMenuEntry> entry) override;

private:
    std::shared_ptr<Database> m_db;
};

#endif // SONGSMENU_H
