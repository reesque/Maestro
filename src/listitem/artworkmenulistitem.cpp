#include "artworkmenulistitem.h"
#include "ui_artworkmenulistitem.h"

ArtworkMenuListItem::ArtworkMenuListItem(QWidget *parent) :
    BaseMenuListItem(parent),
    ui(new Ui::ArtworkMenuListItem)
{
    ui->setupUi(this);
}

ArtworkMenuListItem::~ArtworkMenuListItem()
{
    delete ui;
}

void ArtworkMenuListItem::setProperties(const std::string& header, const std::string& artworkPath)
{
    ui->HeaderLabel->setText(QString::fromStdString(header));
    if (artworkPath != "")
    {
        QPixmap pixmap(QString::fromStdString(artworkPath));
        ui->CoverArt->setPixmap(pixmap);
    }
    else
    {
        ui->CoverArt->setPixmap(QPixmap(":/app/assets/cover.png"));
    }
}

void ArtworkMenuListItem::onFocus()
{
    ui->HeaderLabel->startScrolling();
}

void ArtworkMenuListItem::onLoseFocus()
{
    ui->HeaderLabel->stopScrolling();
}
