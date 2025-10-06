#include "aboutmenu.h"

#include "version.h"

#ifdef UNIX
#include <sys/utsname.h>

#include <QFile>
#include <QTextStream>
#include <QDebug>
#endif

#include <QHostInfo>

AboutMenu::AboutMenu(QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Setting;

    menuList->push_back(std::make_shared<TwoSidedLabelMenuEntry>("Name", QHostInfo::localHostName().toStdString(), TwoSidedListItem::DefaultActivator()));
    menuList->push_back(std::make_shared<TwoSidedLabelMenuEntry>("Software", PROJECT_VERSION, TwoSidedListItem::DefaultActivator()));

#ifdef UNIX
    struct utsname unameData;
    if (uname(&unameData) != 0)
    {
        return;
    }
    menuList->push_back(std::make_shared<TwoSidedLabelMenuEntry>("Distribution", getLinuxDistro(), TwoSidedListItem::DefaultActivator()));
    menuList->push_back(std::make_shared<TwoSidedLabelMenuEntry>("Kernel", unameData.release, TwoSidedListItem::DefaultActivator()));
    menuList->push_back(std::make_shared<TwoSidedLabelMenuEntry>("Architecture", unameData.machine, TwoSidedListItem::DefaultActivator()));
#endif
}

AboutMenu::~AboutMenu()
{}

TwoSidedListItem* AboutMenu::createDefaultItem()
{
    return new TwoSidedListItem(ui->ListObject);
}

void AboutMenu::updateListItem(std::shared_ptr<TwoSidedLabelMenuEntry> entry, TwoSidedListItem *widget)
{
    widget->setProperties(entry);
}

#ifdef UNIX
std::string AboutMenu::getLinuxDistro()
{
    QFile file("/etc/os-release");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return "Unknown";
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.startsWith("PRETTY_NAME="))
        {
            return line.section('=', 1).trimmed().remove('"').toStdString();
        }
    }
    return "Unknown";
}
#endif
