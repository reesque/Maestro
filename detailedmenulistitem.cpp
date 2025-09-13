#include "detailedmenulistitem.h"
#include "ui_detailedmenulistitem.h"

DetailedMenuListItem::DetailedMenuListItem(const std::string& header, const std::string& subtext,
                                           std::function<void()> activator, QWidget *parent) :
    BaseMenuListItem(activator, parent),
    ui(new Ui::DetailedMenuListItem)
{
    ui->setupUi(this);

    ui->HeaderLabel->setText(QString::fromStdString(header));
    ui->SubtextLabel->setText(QString::fromStdString(subtext));
}

DetailedMenuListItem::~DetailedMenuListItem()
{
    delete ui;
}
