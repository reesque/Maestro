#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <string>
#include <functional>
#include <memory>

#include <QVariant>

template<typename SelfType>
struct BaseMenuEntry
{
    std::function<void(std::shared_ptr<SelfType>)> activator;

protected:
    BaseMenuEntry(std::function<void(std::shared_ptr<SelfType>)> v_activator)
    {
        activator = v_activator;
    }
};

struct LabelMenuEntry : public BaseMenuEntry<LabelMenuEntry>
{
    std::string label;

    LabelMenuEntry(std::string v_label, std::function<void(std::shared_ptr<LabelMenuEntry>)> v_activator) :
        BaseMenuEntry(v_activator)
    {
        label = v_label;
    }
};

struct DetailedMenuEntry : public BaseMenuEntry<DetailedMenuEntry>
{
    std::string header;
    std::string subtext;
    std::string artPath;

    DetailedMenuEntry(std::string v_header, std::string v_subtext,
                      std::string v_artPath, std::function<void(std::shared_ptr<DetailedMenuEntry>)> v_activator) :
        BaseMenuEntry(v_activator)
    {
        header = v_header;
        subtext = v_subtext;
        artPath = v_artPath;
    }
};

struct ArtworkMenuEntry : public BaseMenuEntry<ArtworkMenuEntry>
{
    std::string header;
    std::string artPath;

    ArtworkMenuEntry(std::string v_header, std::string v_artPath,
                     std::function<void(std::shared_ptr<ArtworkMenuEntry>)> v_activator) :
        BaseMenuEntry(v_activator)
    {
        header = v_header;
        artPath = v_artPath;
    }
};

struct SliderSettingMenuEntry : public BaseMenuEntry<SliderSettingMenuEntry>
{
    std::string label;
    int min;
    int max;
    int stepSize;
    int value;

    SliderSettingMenuEntry(std::string v_label, int v_min, int v_max, int v_stepSize, int v_value,
                           std::function<void(std::shared_ptr<SliderSettingMenuEntry>)> v_activator) :
        BaseMenuEntry(v_activator)
    {
        label = v_label;
        min = v_min;
        max = v_max;
        stepSize = v_stepSize;
        value = v_value;
    }
};

struct LabelWithToggleMenuEntry : public BaseMenuEntry<LabelWithToggleMenuEntry>
{
    std::string label;
    bool toggleable;
    bool value;

    LabelWithToggleMenuEntry(std::string v_label, bool v_toggleable,
                             std::function<void(std::shared_ptr<LabelWithToggleMenuEntry>)> v_activator,
                             bool v_value = false) :
        BaseMenuEntry(v_activator)
    {
        label = v_label;
        toggleable = v_toggleable;
        value = v_value;
    }
};

#endif // MENUENTRY_H
