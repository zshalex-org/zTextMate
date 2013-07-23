#include "colorscheme.h"

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
#define COLOR_SCHEME_SUB_FONT_STYLE    "fontStyle"
#define COLOR_SCHEME_SUB_COMMENT_BLOCK "comment.block"
#define COLOR_SCHEME_SUB_BACKGROUND    "background"
#define COLOR_SCHEME_SUB_FOREGROUND    "foreground"

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
        m_name = plist.getValue(COLOR_SCHEME_NAME).toString();
        m_author = plist.getValue(COLOR_SCHEME_AUTHOR).toString();
        m_uuid = plist.getValue(COLOR_SCHEME_UUID).toString();

        m_background = plist.getValue(
                    COLOR_SCHEME_DEF_BACKGROUND).value<QColor>();
        m_caret = plist.getValue(
                    COLOR_SCHEME_DEF_CARET).value<QColor>();
        m_foreground = plist.getValue(
                    COLOR_SCHEME_DEF_FOREGROUND).value<QColor>();
        m_invisibles = plist.getValue(
                    COLOR_SCHEME_DEF_INVISIBLES).value<QColor>();
        m_lineHighLight = plist.getValue(
                    COLOR_SCHEME_DEF_LINEHIGHLIGHT).value<QColor>();
        m_selection = plist.getValue(
                    COLOR_SCHEME_DEF_SELECTION).value<QColor>();

        QVariant value = plist.getValue(COLOR_SCHEME_SETTINGS);
        PListArray array = value.value<PListArray>();
        SubScheme scheme;

        for (int i = 0; i < array.count(); i++) {
            value = plist.getValue(array.at(i),COLOR_SCHEME_NAME);
            if (!value.isValid())
                continue;
            scheme.name = value.toString();
            value = plist.getValue(array.at(i),COLOR_SCHEME_SUB_SCOPE);
            scheme.scope = value.toString();
            value = plist.getValue(array.at(i),COLOR_SCHEME_SETTINGS);
            if(scheme.scope == COLOR_SCHEME_SUB_COMMENT_BLOCK){
                scheme.background = plist.getValue(value, COLOR_SCHEME_SUB_BACKGROUND)
                        .value<QColor>();
                scheme.fontStyle = plist.getValue(value, COLOR_SCHEME_SUB_FONT_STYLE)
                        .toString();
            }
            scheme.foreground = plist.getValue(value, COLOR_SCHEME_SUB_FOREGROUND)
                    .value<QColor>();
            m_map.insert(scheme.scope, scheme);
        }
    }
    return result;
}

SubScheme ColorScheme::scheme(QString key)
{
    return m_map.value(key);
}


