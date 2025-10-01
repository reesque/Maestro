#include "menuwithtogglelistitem.h"
#include "ui_menuwithtogglelistitem.h"

MenuWithToggleListItem::MenuWithToggleListItem(QWidget *parent) :
    BaseMenuListItem(parent),
    ui(new Ui::MenuWithToggleListItem)
{
    ui->setupUi(this);
    m_toggleable = true;
}

MenuWithToggleListItem::~MenuWithToggleListItem()
{
    delete ui;
}

void MenuWithToggleListItem::setProperties(const std::string& label,
                                           bool toggleable, bool initValue)
{
    ui->MenuLabel->setText(QString::fromStdString(label));
    m_toggleable = toggleable;
    if (!toggleable)
    {
        ui->Toggle->setVisible(false);
    }
    else
    {
        if (initValue)
        {
            ui->Toggle->setChecked(true);
        }
        else
        {
            ui->Toggle->setChecked(false);
        }
    }
}

void MenuWithToggleListItem::onFocus()
{
    ui->MenuLabel->startScrolling();
}

void MenuWithToggleListItem::onLoseFocus()
{
    ui->MenuLabel->stopScrolling();
}

void MenuWithToggleListItem::activate()
{
    if (m_toggleable)
    {
        if (ui->Toggle->isChecked())
        {
            ui->Toggle->setChecked(false);
        }
        else
        {
            ui->Toggle->setChecked(true);
        }
    }

    m_activator();
}
