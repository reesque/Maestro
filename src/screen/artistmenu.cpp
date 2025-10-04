#include "artistmenu.h"

#include <QVector>
#include <QVariant>

ArtistMenu::ArtistMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Music;

    for (auto artist : db->getAllArtists())
    {
        menuList->push_back(std::make_shared<LabelMenuEntry>(artist,
            [=](std::shared_ptr<LabelMenuEntry>){
                QVector<QVariant> args;
                args.push_back(QVariant(QString::fromStdString(artist)));
                emit switchScreenTo(ScreenType::ArtistFilter, args);
            }
        ));
    }
}

ArtistMenu::~ArtistMenu()
{}

MenuListItem* ArtistMenu::createDefaultItem()
{
    return new MenuListItem(ui->ListObject);
}

void ArtistMenu::updateListItem(std::shared_ptr<LabelMenuEntry> entry, MenuListItem *widget)
{
    widget->setProperties(entry);
}
