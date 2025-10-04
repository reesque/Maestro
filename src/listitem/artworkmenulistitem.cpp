#include "artworkmenulistitem.h"
#include "ui_artworkmenulistitem.h"

ArtworkMenuListItem::ArtworkMenuListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArtworkMenuListItem)
{
    ui->setupUi(this);
}

ArtworkMenuListItem::~ArtworkMenuListItem()
{
    delete ui;
}

void ArtworkMenuListItem::updateItem()
{
    ui->HeaderLabel->setText(QString::fromStdString(m_entry->header));
    if (m_entry->artPath != "")
    {
        QPixmap pixmap(QString::fromStdString(m_entry->artPath));
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
