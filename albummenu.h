#ifndef ALBUMMENU_H
#define ALBUMMENU_H

#include "database.h"
#include "menu.h"
#include "artworkmenulistitem.h"

class AlbumMenu : public Menu<ArtworkMenuEntry, ArtworkMenuListItem>
{
public:
    explicit AlbumMenu(std::shared_ptr<Database> db, QWidget *parent = nullptr);
    ~AlbumMenu() override;

protected:
    ArtworkMenuListItem* createListItem(std::shared_ptr<ArtworkMenuEntry> entry) override;

private:
    std::shared_ptr<Database> m_db;
};

#endif // ALBUMMENU_H
