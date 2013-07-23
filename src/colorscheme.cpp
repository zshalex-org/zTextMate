#include "colorscheme.h"

ColorScheme::ColorScheme(QObject *parent) :
    QObject(parent),
    m_result(false)
{
}

QString ColorScheme::name()
{
    return m_name;
}

QString ColorScheme::author()
{
    return m_author;
}

QString ColorScheme::uuid()
{
    return m_uuid;
}

QString ColorScheme::background()
{
    return m_background;
}

QString ColorScheme::caret()
{
    return m_caret;
}

QString ColorScheme::foreground()
{
    return m_foreground;
}

QString ColorScheme::invisibles()
{
    return m_invisibles;
}

QString ColorScheme::lineHighLight()
{
    return m_lineHighLight;
}

QString ColorScheme::selection()
{
    return m_selection;
}

bool ColorScheme::loadColorScheme(QString filename)
{
    PListDocument plist;
    bool result = plist.load(filename);
    m_map.clear();
    if (result) {
        m_name = plist.getValue("name").toString();
        m_author = plist.getValue("author").toString();
        m_uuid = plist.getValue("uuid").toString();
        m_background = plist.getValue(
                    "settings[0].settings.background").toString();
        m_caret = plist.getValue(
                    "settings[0].settings.caret").toString();
        m_foreground = plist.getValue(
                    "settings[0].settings.foreground").toString();
        m_invisibles = plist.getValue(
                    "settings[0].settings.invisibles").toString();
        m_lineHighLight = plist.getValue(
                    "settings[0].settings.lineHighLight").toString();
        m_selection = plist.getValue(
                    "settings[0].settings.selection").toString();
        QVariant value = plist.getValue("settings");
        PListArray array = value.value<PListArray>();
        SubScheme scheme;

        for (int i = 0; i < array.count(); i++) {
            value = plist.getValue(array.at(i),"name");
            if (!value.isValid())
                continue;
            scheme.name = value.toString();
            value = plist.getValue(array.at(i),"scope");
            scheme.scope = value.toString();
            value = plist.getValue(array.at(i),"settings");
            if(scheme.scope == "comment.block"){
                scheme.background = plist.getValue(value, "background")
                        .toString();
                scheme.fontStyle = plist.getValue(value, "fontStyle")
                        .toString();
            }
            scheme.foreground = plist.getValue(value, "foreground")
                    .toString();
            m_map.insert(scheme.scope, scheme);
        }
    }
    return result;
}

SubScheme ColorScheme::scheme(QString key)
{
    return m_map.value(key);
}


