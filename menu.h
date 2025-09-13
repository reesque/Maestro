#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QListWidgetItem>

#include <functional>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

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
    std::shared_ptr<std::vector<MenuEntry>> menuList;

private slots:
    void onItemClicked(QListWidgetItem *item);

private:
    Ui::Menu *ui;
};

#endif // MENU_H
