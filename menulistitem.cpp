#include "menulistitem.h"
#include "ui_menulistitem.h"

MenuListItem::MenuListItem(const std::string& label, std::function<void()> activator, QWidget *parent) :
    BaseMenuListItem(activator, parent),
    ui(new Ui::MenuListItem)
{
    ui->setupUi(this);
    ui->MenuLabel->setText(QString::fromStdString(label));
}

MenuListItem::~MenuListItem()
{
    delete ui;
}
