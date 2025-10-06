#include "twosidedlistitem.h"
#include "ui_twosidedlistitem.h"

#include <QScrollBar>

TwoSidedListItem::TwoSidedListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoSidedListItem)
{
    ui->setupUi(this);
}

TwoSidedListItem::~TwoSidedListItem()
{
    delete ui;
}

void TwoSidedListItem::updateItem()
{
    ui->MenuLabel->setText(QString::fromStdString(m_entry->label));
    ui->ValueLabel->setText(QString::fromStdString(m_entry->value));

    QScrollBar *hBar = ui->ValueLabel->horizontalScrollBar();
    if (hBar->maximum() == 0)
    {
        ui->ValueLabel->selectAll();
        ui->ValueLabel->setAlignment(Qt::AlignRight);
        QTextCursor cursor = ui->ValueLabel->textCursor();
        cursor.clearSelection();
        ui->ValueLabel->setTextCursor(cursor);
    }
}

void TwoSidedListItem::onFocus()
{
    ui->ValueLabel->startScrolling();
}

void TwoSidedListItem::onLoseFocus()
{
    ui->ValueLabel->stopScrolling();
}
