#include "colorscheme.h"

ColorScheme::ColorScheme(QObject *parent) :
    QObject(parent),
    m_result(false)
{
}

QString ColorScheme::name()
{
    if(m_result)
        return m_plist.getValue("name").toString();
    else
        return "";
}

QString ColorScheme::author()
{
    if(m_result)
        return m_plist.getValue("author").toString();
    else
        return "";
}

QString ColorScheme::uuid()
{
    if(m_result)
        return m_plist.getValue("uuid").toString();
    else
        return "";
}

QString ColorScheme::background()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].setting.background").toString();
    else
        return "";
}

QString ColorScheme::caret()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].setting.caret").toString();
    else
        return "";
}

QString ColorScheme::foreground()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].setting.foreground").toString();
    else
        return "";
}

QString ColorScheme::invisibles()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].setting.invisibles").toString();
    else
        return "";
}

QString ColorScheme::lineHighLight()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].setting.lineHighLight").toString();
    else
        return "";
}

QString ColorScheme::selection()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].setting.selection").toString();
    else
        return "";
}

QVariant ColorScheme::getDict(QString key)
{
    return m_map.value(key);
}

bool ColorScheme::loadColorScheme(QString &filename)
{
    m_result = m_plist.load(filename);
    return m_result;
}
