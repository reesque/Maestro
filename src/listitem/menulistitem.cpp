#include "menulistitem.h"
#include "ui_menulistitem.h"

MenuListItem::MenuListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuListItem)
{
    ui->setupUi(this);
}

MenuListItem::~MenuListItem()
{
    delete ui;
}

void MenuListItem::updateItem()
{
    ui->MenuLabel->setText(QString::fromStdString(m_entry->label));
}

void MenuListItem::onFocus()
{
    ui->MenuLabel->startScrolling();
}

void MenuListItem::onLoseFocus()
{
    ui->MenuLabel->stopScrolling();
}
