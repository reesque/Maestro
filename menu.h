#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private:
    void populateMenu(const std::vector<std::string>& entries);

private:
    Ui::Menu *ui;
};

#endif // MENU_H
