#include "artistmenu.h"

#include <QVector>
#include <QVariant>

ArtistMenu::ArtistMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Music;

    ui->ListObject->setStyleSheet(
        "QListWidget::item { background-color: white; border-top: none; border-bottom: 1px solid #cccccc; }"
        "QListWidget::item:selected { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0096FF, stop:1 #0066CC); border: none; }"
    );

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
