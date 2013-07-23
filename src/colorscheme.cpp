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
                    "settings[0].settings.background").toString();
    else
        return "";
}

QString ColorScheme::caret()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].settings.caret").toString();
    else
        return "";
}

QString ColorScheme::foreground()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].settings.foreground").toString();
    else
        return "";
}

QString ColorScheme::invisibles()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].settings.invisibles").toString();
    else
        return "";
}

QString ColorScheme::lineHighLight()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].settings.lineHighLight").toString();
    else
        return "";
}

QString ColorScheme::selection()
{
    if(m_result)
        return m_plist.getValue(
                    "settings[0].settings.selection").toString();
    else
        return "";
}

QVariant ColorScheme::getDict(QString key)
{
    return m_map.value(key);
}

bool ColorScheme::loadColorScheme(QString filename)
{
    m_result = m_plist.load(filename);
    m_map.clear();
    if (m_result) {
        QVariant value = m_plist.getValue("settings");
        PListArray array = value.value<PListArray>();

        for (int i = 0; i < array.count(); i++) {
            value = m_plist.getValue(array.at(i),"name");
            if (!value.isValid())
                continue;
            value = m_plist.getValue(array.at(i),"scope");
            m_map.insert(value.toString(),array.at(i));
        }
    }
    return m_result;
}
