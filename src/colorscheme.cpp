#include "colorscheme.h"
#include "plistdocument.h"

#define COLOR_SCHEME_NAME              "name"
#define COLOR_SCHEME_AUTHOR            "author"
#define COLOR_SCHEME_UUID              "uuid"
#define COLOR_SCHEME_SETTINGS          "settings"
#define COLOR_SCHEME_DEF_BACKGROUND    "settings[0].settings.background"
#define COLOR_SCHEME_DEF_CARET         "settings[0].settings.caret"
#define COLOR_SCHEME_DEF_FOREGROUND    "settings[0].settings.foreground"
#define COLOR_SCHEME_DEF_INVISIBLES    "settings[0].settings.invisibles"
#define COLOR_SCHEME_DEF_LINEHIGHLIGHT "settings[0].settings.lineHighLight"
#define COLOR_SCHEME_DEF_SELECTION     "settings[0].settings.selection"
#define COLOR_SCHEME_SUB_SCOPE         "scope"
#define COLOR_SCHEME_SUB_FONT_STYLE    "settings.fontStyle"
#define COLOR_SCHEME_SUB_BACKGROUND    "settings.background"
#define COLOR_SCHEME_SUB_FOREGROUND    "settings.foreground"

ColorScheme::ColorScheme(QObject *parent) :
    QObject(parent)
{
}

const QString & ColorScheme::name() const
{
    return m_name;
}

const QString & ColorScheme::author() const
{
    return m_author;
}

const QString & ColorScheme::uuid() const
{
    return m_uuid;
}

const QColor & ColorScheme::background() const
{
    return m_background;
}

const QColor & ColorScheme::caret() const
{
    return m_caret;
}

const QColor & ColorScheme::foreground() const
{
    return m_foreground;
}

const QColor & ColorScheme::invisibles() const
{
    return m_invisibles;
}

const QColor & ColorScheme::lineHighLight() const
{
    return m_lineHighLight;
}

const QColor & ColorScheme::selection() const
{
    return m_selection;
}

bool ColorScheme::loadColorScheme(QString filename)
{
    PListDocument plist;
    bool result = plist.load(filename);
    m_map.clear();
    if (result) {
        m_name = plist.getString(COLOR_SCHEME_NAME);
        m_author = plist.getString(COLOR_SCHEME_AUTHOR);
        m_uuid = plist.getString(COLOR_SCHEME_UUID);

        m_background = plist.getColor(COLOR_SCHEME_DEF_BACKGROUND);
        m_caret = plist.getColor(COLOR_SCHEME_DEF_CARET);
        m_foreground = plist.getColor(COLOR_SCHEME_DEF_FOREGROUND);
        m_invisibles = plist.getColor(COLOR_SCHEME_DEF_INVISIBLES);
        m_lineHighLight = plist.getColor(COLOR_SCHEME_DEF_LINEHIGHLIGHT);
        m_selection = plist.getColor(COLOR_SCHEME_DEF_SELECTION);

        QVariant value = plist.getValue(COLOR_SCHEME_SETTINGS);
        PListArray array = value.value<PListArray>();
        SubScheme scheme;

        for (int i = 0; i < array.count(); i++) {
            scheme.name = plist.getString(array.at(i),COLOR_SCHEME_NAME);
            scheme.scope = plist.getString(array.at(i),COLOR_SCHEME_SUB_SCOPE);
            scheme.background = plist.getColor(array.at(i), COLOR_SCHEME_SUB_BACKGROUND);
            scheme.fontStyle = plist.getString(array.at(i), COLOR_SCHEME_SUB_FONT_STYLE);
            scheme.foreground = plist.getColor(array.at(i), COLOR_SCHEME_SUB_FOREGROUND);

            scheme.italic = scheme.fontStyle == "italic";
            scheme.underline = scheme.fontStyle == "underline";
            m_map.insert(scheme.scope, scheme);
        }
    }
    return result;
}

SubScheme ColorScheme::scheme(QString key)
{
    return m_map.value(key);
}


