#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <string>
#include <functional>

struct BaseMenuEntry
{
    std::function<void()> activator;

protected:
    BaseMenuEntry(std::function<void()> v_activator)
    {
        activator = v_activator;
    }
};

struct LabelMenuEntry : public BaseMenuEntry
{
    std::string label;

    LabelMenuEntry(std::string v_label, std::function<void()> v_activator) :
        BaseMenuEntry(v_activator)
    {
        label = v_label;
    }
};

struct DetailedMenuEntry : public BaseMenuEntry
{
    std::string header;
    std::string subtext;

    DetailedMenuEntry(std::string v_header, std::string v_subtext, std::function<void()> v_activator) :
        BaseMenuEntry(v_activator)
    {
        header = v_header;
        subtext = v_subtext;
    }
};

#endif // MENUENTRY_H
