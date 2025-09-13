#include "menu.h"
#include "ui_menu.h"

#include "menulistitem.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    ui->ListObject->setStyleSheet(
        "QListWidget::item { background-color: white; }"
        "QListWidget::item:selected { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0096FF, stop:1 #0066CC); }"
    );

    ui->ListObject->setFocusPolicy(Qt::NoFocus);

    std::vector<std::string> tempMenu;
    tempMenu.push_back("Music");
    tempMenu.push_back("Videos");
    tempMenu.push_back("Photos");
    tempMenu.push_back("Settings");
    tempMenu.push_back("Shuffle Songs");
    tempMenu.push_back("Now Playing");

    populateMenu(tempMenu);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::populateMenu(const std::vector<std::string>& entries)
{
    for (auto entry : entries)
    {
        QListWidgetItem *qitem = new QListWidgetItem(ui->ListObject);
        MenuListItem *item = new MenuListItem(ui->ListObject, entry);
        qitem->setSizeHint(item->sizeHint());
        ui->ListObject->addItem(qitem);
        ui->ListObject->setItemWidget(qitem, item);
    }
}
