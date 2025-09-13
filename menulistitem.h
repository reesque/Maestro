#ifndef MENULISTITEM_H
#define MENULISTITEM_H

#include <QWidget>

#include <functional>

namespace Ui {
class MenuListItem;
}

class MenuListItem : public QWidget
{
    Q_OBJECT

public:
    explicit MenuListItem(std::string label, std::function<void()> activator, QWidget *parent = nullptr);
    ~MenuListItem();

    void activate();

private:
    Ui::MenuListItem *ui;
    std::function<void()> m_activator;
};

#endif // MENULISTITEM_H
