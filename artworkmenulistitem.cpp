#include "artworkmenulistitem.h"
#include "ui_artworkmenulistitem.h"

ArtworkMenuListItem::ArtworkMenuListItem(const std::string& header,
                                         std::function<void()> activator, QWidget *parent) :
  BaseMenuListItem(activator, parent),
  ui(new Ui::ArtworkMenuListItem)
{
  ui->setupUi(this);

  ui->HeaderLabel->setText(QString::fromStdString(header));
}

ArtworkMenuListItem::~ArtworkMenuListItem()
{
    delete ui;
}
