#include "detailedmenulistitem.h"
#include "ui_detailedmenulistitem.h"

#include <QPixmap>

DetailedMenuListItem::DetailedMenuListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailedMenuListItem)
{
    ui->setupUi(this);
}

DetailedMenuListItem::~DetailedMenuListItem()
{
    delete ui;
}


void DetailedMenuListItem::updateItem()
{
    ui->HeaderLabel->setText(QString::fromStdString(m_entry->header));
    ui->SubtextLabel->setText(QString::fromStdString(m_entry->subtext));

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
