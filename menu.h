#ifndef MENU_H
#define MENU_H

#include "screen.h"
#include <QListWidgetItem>

#include <functional>

namespace Ui {
class Menu;
}

class Menu : public Screen
{
protected:
    struct MenuEntry
    {
        std::string label;
        std::function<void()> activator;
    };

public:
    explicit Menu(QWidget *parent = nullptr);
    virtual ~Menu();

    void clear();

protected:
    void populateMenu();

protected:
    Ui::Menu *ui;
    std::unique_ptr<std::vector<MenuEntry>> menuList;

protected slots:
    void onItemClicked(QListWidgetItem *item);
};

#endif // MENU_H
