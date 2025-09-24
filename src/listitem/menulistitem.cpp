#include "menulistitem.h"
#include "ui_menulistitem.h"

MenuListItem::MenuListItem(const std::string& label, QWidget *parent) :
    BaseMenuListItem(parent),
    ui(new Ui::MenuListItem)
{
    ui->setupUi(this);
    ui->MenuLabel->setText(QString::fromStdString(label));
}

MenuListItem::~MenuListItem()
{
    delete ui;
}
