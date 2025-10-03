#include "artistfiltermenu.h"

ArtistFilterMenu::ArtistFilterMenu(const std::string& artistName, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Artist;

    QVector<QVariant> args;
    args.push_back(QVariant(QString::fromStdString(artistName)));

    menuList->push_back(std::make_shared<LabelMenuEntry>("by Songs",
        [=](std::shared_ptr<LabelMenuEntry>){
            switchScreenTo(ScreenType::SongsByArtist, args);
        }
    ));
    menuList->push_back(std::make_shared<LabelMenuEntry>("by Album",
        [=](std::shared_ptr<LabelMenuEntry>){
            switchScreenTo(ScreenType::AlbumByArtist, args);
        }
    ));
}

ArtistFilterMenu::~ArtistFilterMenu()
{}

MenuListItem* ArtistFilterMenu::createDefaultItem()
{
    return new MenuListItem(ui->ListObject);
}

void ArtistFilterMenu::updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget)
{
    widget->setProperties(entry);
}
