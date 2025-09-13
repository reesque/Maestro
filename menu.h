#ifndef MENU_H
#define MENU_H

#include "screen.h"
#include "menuentry.h"

#include "ui_menu.h"

#include <QListWidgetItem>
#include <QScrollBar>

namespace Ui {
class Menu;
}

template <typename MenuEntry, typename MenuWidget>
class Menu : public Screen
{
public:
    explicit Menu(QWidget *parent) :
        Screen(parent),
        ui(new Ui::Menu)
    {
        ui->setupUi(this);

        // Background on focus
        ui->ListObject->setStyleSheet(
            "QListWidget::item { background-color: white; border: none; }"
            "QListWidget::item:selected { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0096FF, stop:1 #0066CC); border: none; }"
        );

        ui->ListObject->setFocusPolicy(Qt::NoFocus);
        ui->ListObject->setContentsMargins(0, 0, 0, 0);
        ui->ListObject->viewport()->setContentsMargins(0, 0, 0, 0);
        ui->ListObject->setSpacing(0);
        ui->ListObject->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        // Scroll bar
        ui->ListObject->verticalScrollBar()->setStyleSheet(R"(
            QScrollBar:vertical {
                background: transparent;
                width: 6px;
                margin: 0px;
            }

            QScrollBar::handle:vertical {
                background: rgba(100, 100, 100, 180);
                min-height: 20px;
                border-radius: 3px;
            }

            QScrollBar::add-line:vertical,
            QScrollBar::sub-line:vertical {
                height: 0px;
            }

            QScrollBar::add-page:vertical,
            QScrollBar::sub-page:vertical {
                background: none;
            }
        )");

        menuList = std::make_unique<std::vector<std::shared_ptr<BaseMenuEntry>>>();
        connect(ui->ListObject, &QListWidget::itemClicked, this, &Menu::onItemClicked);
    }

    virtual ~Menu()
    {
        disconnect(ui->ListObject, &QListWidget::itemClicked, this, &Menu::onItemClicked);

        delete ui;
    }

protected:
    void populateMenu()
    {
        for (auto entry : *menuList)
        {
            QListWidgetItem *qitem = new QListWidgetItem(ui->ListObject);
            QWidget *item = createListItem(std::static_pointer_cast<MenuEntry>(entry));
            qitem->setSizeHint(item->sizeHint());
            ui->ListObject->addItem(qitem);
            ui->ListObject->setItemWidget(qitem, item);
        }

        ui->ListObject->setCurrentRow(0);
    }

    virtual MenuWidget* createListItem(std::shared_ptr<MenuEntry> entry) = 0;

protected:
    Ui::Menu *ui;
    std::unique_ptr<std::vector<std::shared_ptr<BaseMenuEntry>>> menuList;

protected slots:
    void onItemClicked(QListWidgetItem *item)
    {
        QWidget *qw = ui->ListObject->itemWidget(item);
        static_cast<MenuWidget&>(*qw).activate();
    }
};

#endif // MENU_H
