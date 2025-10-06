#ifndef ABOUTMENU_H
#define ABOUTMENU_H

#include "menu.h"
#include "twosidedlistitem.h"

class AboutMenu : public Menu<TwoSidedLabelMenuEntry, TwoSidedListItem>
{
public:
    explicit AboutMenu(QWidget *parent = nullptr);
    ~AboutMenu() override;

protected:
    virtual TwoSidedListItem* createDefaultItem() override;
    virtual void updateListItem(std::shared_ptr<TwoSidedLabelMenuEntry> entry, TwoSidedListItem *widget) override;

private:
    std::string getLinuxDistro();
};

#endif // ABOUTMENU_H
