#include "menulistitem.h"
#include "ui_menulistitem.h"

MenuListItem::MenuListItem(std::string label, std::function<void()> activator, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuListItem),
    m_activator(activator)
{
    ui->setupUi(this);
    ui->MenuLabel->setText(QString::fromStdString(label));
}

MenuListItem::~MenuListItem()
{
    delete ui;
}

void MenuListItem::activate()
{
    m_activator();
}
