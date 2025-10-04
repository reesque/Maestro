#include "settingssliderlistitem.h"
#include "ui_settingssliderlistitem.h"

#include "roundedprogressbarstyle.h"

SettingsSliderListItem::SettingsSliderListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsSliderListItem)
{
    ui->setupUi(this);
}

SettingsSliderListItem::~SettingsSliderListItem()
{
    delete ui;
}


void SettingsSliderListItem::updateItem()
{
    ui->ValueBar->setStyle(new RoundedProgressBarStyle);

    ui->Label->setText(QString::fromStdString(m_entry->label));
    ui->ValueBar->setMinimum(m_entry->min);
    ui->ValueBar->setMaximum(m_entry->max);
    ui->ValueBar->setValue(m_entry->value);
    ui->Value->setText(QString::number(m_entry->value));
}

void SettingsSliderListItem::slide(bool isForward)
{
    if (isForward)
    {
        m_entry->value = std::min(ui->ValueBar->value() + m_entry->stepSize, m_entry->max);
        ui->ValueBar->setValue(m_entry->value);
    }
    else
    {
        m_entry->value = std::max(ui->ValueBar->value() - m_entry->stepSize, m_entry->min);
        ui->ValueBar->setValue(m_entry->value);
    }

    ui->Value->setText(QString::number(m_entry->value));

    activate();
}
