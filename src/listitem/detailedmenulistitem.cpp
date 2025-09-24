#include "detailedmenulistitem.h"
#include "ui_detailedmenulistitem.h"

#include <QPixmap>

DetailedMenuListItem::DetailedMenuListItem(const std::string& header, const std::string& subtext,
                                           const std::string& artworkPath, QWidget *parent) :
    BaseMenuListItem(parent),
    ui(new Ui::DetailedMenuListItem)
{
    ui->setupUi(this);

    ui->HeaderLabel->setText(QString::fromStdString(header));
    ui->SubtextLabel->setText(QString::fromStdString(subtext));

    if (artworkPath != "")
    {
        QPixmap pixmap(QString::fromStdString(artworkPath));
        ui->CoverArt->setPixmap(pixmap);
    }
}

DetailedMenuListItem::~DetailedMenuListItem()
{
    delete ui;
}
