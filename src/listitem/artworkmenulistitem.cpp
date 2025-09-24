#include "artworkmenulistitem.h"
#include "ui_artworkmenulistitem.h"

ArtworkMenuListItem::ArtworkMenuListItem(const std::string& header,
                                         const std::string& artworkPath,
                                         QWidget *parent) :
    BaseMenuListItem(parent),
    ui(new Ui::ArtworkMenuListItem)
{
    ui->setupUi(this);

    ui->HeaderLabel->setText(QString::fromStdString(header));
    if (artworkPath != "")
    {
        QPixmap pixmap(QString::fromStdString(artworkPath));
        ui->CoverArt->setPixmap(pixmap);
    }
}

ArtworkMenuListItem::~ArtworkMenuListItem()
{
    delete ui;
}
