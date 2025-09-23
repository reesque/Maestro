#include "artistfiltermenu.h"

ArtistFilterMenu::ArtistFilterMenu(const std::string& artistName, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Artist;

    QVector<QVariant> args;
    args.push_back(QVariant(QString::fromStdString(artistName)));

    menuList->push_back(std::make_shared<LabelMenuEntry>("by Songs", [=](){
        switchScreenTo(ScreenType::SongsByArtist, args);}));
    menuList->push_back(std::make_shared<LabelMenuEntry>("by Album", [=](){
        switchScreenTo(ScreenType::AlbumByArtist, args);}));

    populateMenu();
}

ArtistFilterMenu::~ArtistFilterMenu()
{}

MenuListItem* ArtistFilterMenu::createListItem(std::shared_ptr<LabelMenuEntry> entry)
{
    return new MenuListItem(entry->label, entry->activator, ui->ListObject);
}
