#ifndef MENULISTITEM_H
#define MENULISTITEM_H

#include <QWidget>

namespace Ui {
class MenuListItem;
}

class MenuListItem : public QWidget
{
    Q_OBJECT

public:
    explicit MenuListItem(QWidget *parent = nullptr, std::string label = "MISSING");
    ~MenuListItem();

private:
    Ui::MenuListItem *ui;
};

#endif // MENULISTITEM_H
