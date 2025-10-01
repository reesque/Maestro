#include "detailedmenulistitem.h"
#include "ui_detailedmenulistitem.h"

#include <QPixmap>

DetailedMenuListItem::DetailedMenuListItem(QWidget *parent) :
    BaseMenuListItem(parent),
    ui(new Ui::DetailedMenuListItem)
{
    ui->setupUi(this);
}

DetailedMenuListItem::~DetailedMenuListItem()
{
    delete ui;
}


void DetailedMenuListItem::setProperties(const std::string& header,
                                         const std::string& subtext,
                                         const std::string& artworkPath)
{
    ui->HeaderLabel->setText(QString::fromStdString(header));
    ui->SubtextLabel->setText(QString::fromStdString(subtext));

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

void DetailedMenuListItem::onFocus()
{
    ui->HeaderLabel->startScrolling();
    ui->SubtextLabel->startScrolling();
}

void DetailedMenuListItem::onLoseFocus()
{
    ui->HeaderLabel->stopScrolling();
    ui->SubtextLabel->stopScrolling();
}
