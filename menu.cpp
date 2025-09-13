#include "menu.h"
#include "ui_menu.h"

#include "menulistitem.h"

Menu::Menu(QWidget *parent) :
    Screen(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    ui->ListObject->setStyleSheet(
        "QListWidget::item { background-color: white; border: none; }"
        "QListWidget::item:selected { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0096FF, stop:1 #0066CC); border: none; }"
    );

    ui->ListObject->setFocusPolicy(Qt::NoFocus);

    menuList = std::make_unique<std::vector<MenuEntry>>();
    connect(ui->ListObject, &QListWidget::itemClicked, this, &Menu::onItemClicked);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::clear()
{
    ui->ListObject->clear();
}

void Menu::onItemClicked(QListWidgetItem *item)
{
    QWidget *qw = ui->ListObject->itemWidget(item);
    static_cast<MenuListItem&>(*qw).activate();
}

void Menu::populateMenu()
{
    for (auto entry : *menuList)
    {
        QListWidgetItem *qitem = new QListWidgetItem(ui->ListObject);
        MenuListItem *item = new MenuListItem(entry.label, entry.activator, ui->ListObject);
        qitem->setSizeHint(item->sizeHint());
        ui->ListObject->addItem(qitem);
        ui->ListObject->setItemWidget(qitem, item);
    }

    ui->ListObject->setCurrentRow(0);
}
