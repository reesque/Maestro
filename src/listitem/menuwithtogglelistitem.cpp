#include "menuwithtogglelistitem.h"
#include "ui_menuwithtogglelistitem.h"

MenuWithToggleListItem::MenuWithToggleListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWithToggleListItem)
{
    ui->setupUi(this);
}

MenuWithToggleListItem::~MenuWithToggleListItem()
{
    delete ui;
}

void MenuWithToggleListItem::updateItem()
{
    ui->MenuLabel->setText(QString::fromStdString(m_entry->label));
    if (!m_entry->toggleable)
    {
        ui->Toggle->setVisible(false);
    }
    else
    {
        ui->Toggle->setVisible(true);
        if (m_entry->value)
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
    if (m_entry->toggleable)
    {
        if (ui->Toggle->isChecked())
        {
            m_entry->value = false;
        }
        else
        {
            m_entry->value = true;
        }

        ui->Toggle->setChecked(m_entry->value);
    }

    BaseMenuListItem::activate();
}
