//
// Created by Paul Walker on 5/25/22.
//

#ifndef SST_JUCEGUI_STYLESHEET_H
#define SST_JUCEGUI_STYLESHEET_H

#include <memory>
#include <juce_gui_basics/juce_gui_basics.h>

namespace sst::jucegui::style
{
struct StyleConsumer;
struct StyleSheet
{
    StyleSheet() { setupInheritanceMaps(); }
    virtual ~StyleSheet() = default;

    struct Class
    {
        static constexpr int nameLength = 256;
        char cname[nameLength]{0};
        constexpr Class(const char *s)
        {
            for (int i = 0; i < nameLength - 1; ++i)
            {
                cname[i] = s[i];
                if (cname[i] == 0)
                    break;
            }
            cname[nameLength - 1] = 0;
        }
        Class(const Class &other) { strncpy(cname, other.cname, nameLength); }
    };
    struct Property
    {
        static constexpr int nameLength = 256;
        char pname[nameLength]{0};
        constexpr Property(const char *s)
        {
            for (int i = 0; i < nameLength - 1; ++i)
            {
                pname[i] = s[i];
                if (pname[i] == 0)
                    break;
            }
            pname[nameLength - 1] = 0;
        }
    };

    virtual bool hasColour(const Class &c, const Property &p) const = 0;
    virtual juce::Colour getColour(const Class &c, const Property &p) const = 0;

    virtual bool hasFont(const Class &c, const Property &p) const = 0;
    virtual juce::Font getFont(const Class &c, const Property &p) const = 0;

    typedef std::shared_ptr<StyleSheet> ptr_t;

    enum BuiltInTypes
    {
        DARK,
        LIGHT
    };
    static ptr_t getBuiltInStyleSheet(const BuiltInTypes &t);

    friend struct StyleConsumer;

  protected:
    static void setupInheritanceMaps();
    static void extendInheritanceMap(const StyleSheet::Class &from, const StyleSheet::Class &to);
    static std::unordered_map<std::string, std::string> inheritFromTo;
};
} // namespace sst::jucegui::style

#endif // SST_JUCEGUI_STYLESHEET_H
