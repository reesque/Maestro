#include "menulistitem.h"
#include "ui_menulistitem.h"

MenuListItem::MenuListItem(QWidget *parent) :
    BaseMenuListItem(parent),
    ui(new Ui::MenuListItem)
{
    ui->setupUi(this);
}

MenuListItem::~MenuListItem()
{
    delete ui;
}

void MenuListItem::setProperties(const std::string& label)
{
    ui->MenuLabel->setText(QString::fromStdString(label));
}

void MenuListItem::onFocus()
{
    ui->MenuLabel->startScrolling();
}

void MenuListItem::onLoseFocus()
{
    ui->MenuLabel->stopScrolling();
}
