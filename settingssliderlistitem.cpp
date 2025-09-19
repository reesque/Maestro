#include "settingssliderlistitem.h"
#include "ui_settingssliderlistitem.h"

#include "roundedprogressbarstyle.h"

SettingsSliderListItem::SettingsSliderListItem(const std::string& label, int min, int max, int stepSize, int value,
                                        std::function<void(int)> slideAction, std::function<void()> activator,
                                        QWidget *parent) :
    BaseMenuListItem(activator, parent),
    ui(new Ui::SettingsSliderListItem)
{
    ui->setupUi(this);

    m_min = min;
    m_max = max;
    m_stepSize = stepSize;
    m_slideAction = slideAction;

    ui->ValueBar->setStyle(new RoundedProgressBarStyle);

    ui->Label->setText(QString::fromStdString(label));
    ui->ValueBar->setMinimum(min);
    ui->ValueBar->setMaximum(max);
    ui->ValueBar->setValue(value);
    ui->Value->setText(QString::number(value));
}

SettingsSliderListItem::~SettingsSliderListItem()
{
    delete ui;
}

void SettingsSliderListItem::slide(bool isForward)
{
    if (isForward)
    {
        ui->ValueBar->setValue(std::min(ui->ValueBar->value() + m_stepSize, m_max));
    }
    else
    {
        ui->ValueBar->setValue(std::max(ui->ValueBar->value() - m_stepSize, m_min));
    }

    ui->Value->setText(QString::number(ui->ValueBar->value()));
    m_slideAction(ui->ValueBar->value());
}
