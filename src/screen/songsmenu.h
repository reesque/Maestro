#ifndef SONGSMENU_H
#define SONGSMENU_H

#include "database.h"
#include "datastruct.h"
#include "menu.h"
#include "detailedmenulistitem.h"

class SongsMenu : public Menu<DetailedMenuEntry, DetailedMenuListItem>
{
public:
    enum class Filter
    {
        Album = 0,
        Artist,
        AlbumArtist
    };

    explicit SongsMenu(std::shared_ptr<Database> db, QWidget *parent = nullptr);
    explicit SongsMenu(std::shared_ptr<Database> db, Filter filter, QVector<QVariant> values, QWidget *parent = nullptr);
    ~SongsMenu() override;

protected:
    DetailedMenuListItem* createListItem(std::shared_ptr<DetailedMenuEntry> entry) override;

private:
    void fillSongRecords(std::vector<Track> records);

private:
    std::shared_ptr<Database> m_db;
};

#endif // SONGSMENU_H
