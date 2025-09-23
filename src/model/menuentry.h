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
    std::string artPath;

    DetailedMenuEntry(std::string v_header, std::string v_subtext,
                      std::string v_artPath, std::function<void()> v_activator) :
        BaseMenuEntry(v_activator)
    {
        header = v_header;
        subtext = v_subtext;
        artPath = v_artPath;
    }
};

struct ArtworkMenuEntry : public BaseMenuEntry
{
    std::string header;
    std::string artPath;

    ArtworkMenuEntry(std::string v_header, std::string v_artPath, std::function<void()> v_activator) :
        BaseMenuEntry(v_activator)
    {
        header = v_header;
        artPath = v_artPath;
    }
};

struct SliderSettingMenuEntry : public BaseMenuEntry
{
    std::string label;
    int min;
    int max;
    int stepSize;
    int value;
    std::function<void(int)> slideAction;

    SliderSettingMenuEntry(std::string v_label, int v_min, int v_max, int v_stepSize, int v_value,
                           std::function<void(int)> v_slideAction, std::function<void()> v_activator) :
        BaseMenuEntry(v_activator)
    {
        label = v_label;
        min = v_min;
        max = v_max;
        stepSize = v_stepSize;
        value = v_value;
        slideAction = v_slideAction;
    }
};

#endif // MENUENTRY_H
