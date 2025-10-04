#ifndef MENU_H
#define MENU_H

#include "ui_menu.h"

#include "screen.h"

#include <memory>
#include <cmath>
#include <deque>

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

        numItems = 0;
        currentPage = 0;

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

        menuList = std::make_unique<std::deque<std::shared_ptr<MenuEntry>>>();
        connect(ui->ListObject, &QListWidget::itemClicked, this, &Menu::onItemClicked);
        connect(ui->ListObject, &QListWidget::currentItemChanged, this, &Menu::currentItemChanged);
    }

    virtual ~Menu()
    {
        disconnect(ui->ListObject, &QListWidget::itemClicked, this, &Menu::onItemClicked);

        delete ui;
    }

public slots:
    void resizeEvent(QResizeEvent *) override
    {
        // Re-index pages
        numItems = measure();
        render();
        toTop();
        ui->ListObject->setCurrentRow(0);

        // Resize and move widgets
        ui->ListObject->setGeometry(0, 0, width(), height());
        ui->Scroll->setGeometry(width() - ui->Scroll->width(), 0,
                                ui->Scroll->width(), height());

        ui->Scroll->setPageStep(numItems);
        ui->Scroll->setMaximum(menuList->size() - 1);
        ui->Scroll->setValue(0);
        if (numItems <= menuList->size() - 1)
        {
            ui->Scroll->show();
        }
        else
        {
            ui->Scroll->hide();
        }
    }

    void upAction() override
    {
        if (ui->ListObject->currentRow() == 0 && currentPage != 0)
        {
            currentPage -= 1;
            update();
            ui->ListObject->setCurrentRow(ui->ListObject->count() - 1);
        }
        else
        {
            ui->ListObject->setCurrentRow(std::max(ui->ListObject->currentRow() - 1, 0));
        }

        ui->Scroll->setValue(numItems * currentPage + ui->ListObject->currentRow());
    }

    void downAction() override
    {
        if (numItems * currentPage + ui->ListObject->currentRow() + 1 >= menuList->size())
        {
            return;
        }

        unsigned maxPage = std::ceil(static_cast<float>(menuList->size()) / numItems);
        if (ui->ListObject->currentRow() == ui->ListObject->count() - 1 && currentPage < maxPage - 1)
        {
            currentPage += 1;
            update();
            ui->ListObject->setCurrentRow(0);
        }
        else
        {
            ui->ListObject->setCurrentRow(std::min(ui->ListObject->currentRow() + 1, ui->ListObject->count() - 1));
        }

        ui->Scroll->setValue(numItems * currentPage + ui->ListObject->currentRow());
    }

    void confirmAction() override
    {
        emit ui->ListObject->itemClicked(ui->ListObject->currentItem());
    }

protected:
    virtual MenuWidget* createDefaultItem() = 0;
    virtual void updateListItem(std::shared_ptr<MenuEntry> entry, MenuWidget *widget) = 0;

    void toTop()
    {
        currentPage = 0;
        update();
    }

protected:
    Ui::Menu *ui;
    std::unique_ptr<std::deque<std::shared_ptr<MenuEntry>>> menuList;
    unsigned numItems;
    unsigned currentPage;

protected slots:
    void onItemClicked(QListWidgetItem *item)
    {
        if (!m_inputLock)
        {
            QWidget *qw = ui->ListObject->itemWidget(item);
            static_cast<MenuWidget&>(*qw).activate();
        }
    }

    void currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
    {
        if (current)
        {
            static_cast<MenuWidget&>(*ui->ListObject->itemWidget(current)).onFocus();
        }
        if (previous)
        {
            static_cast<MenuWidget&>(*ui->ListObject->itemWidget(previous)).onLoseFocus();
        }
    }

private:
    unsigned measure()
    {
        if (menuList->size() == 0)
        {
            return 0;
        }

        QWidget *item = createDefaultItem();
        float itemHeight = item->sizeHint().height();
        delete item;
        return std::ceil(ui->ListObject->height() / itemHeight);
    }

    void render()
    {
        ui->ListObject->clear();

        for (unsigned i = 0; i < numItems; ++i)
        {
            QListWidgetItem *qitem = new QListWidgetItem(ui->ListObject);
            QWidget *item = createDefaultItem();
            qitem->setSizeHint(item->sizeHint());
            ui->ListObject->addItem(qitem);
            ui->ListObject->setItemWidget(qitem, item);
        }
    }

    void update()
    {
        unsigned start = currentPage * numItems;

        for (unsigned i = start; i < start + numItems; ++i)
        {
            if (i < menuList->size())
            {
                updateListItem(menuList->at(i), static_cast<MenuWidget *>(ui->ListObject->itemWidget(ui->ListObject->item(i - start))));
                ui->ListObject->item(i - start)->setHidden(false);
            }
            else
            {
                ui->ListObject->item(i - start)->setHidden(true);
            }
        }
    }
};

#endif // MENU_H
