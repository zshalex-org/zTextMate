#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QObject>
#include <QUuid>
#include <QColor>

#include "plistdocument.h"

struct SubScheme
{
    QString name;
    QString scope;
    QString background;
    QString foreground;
    QString fontStyle;
};

class ColorScheme : public QObject
{
    Q_OBJECT
public:
    explicit ColorScheme(QObject *parent = 0);

    QString name();
    QString author();
    QString uuid();
    QString background();
    QString caret();
    QString foreground();
    QString invisibles();
    QString lineHighLight();
    QString selection();

    bool loadColorScheme(QString filename);
    SubScheme scheme(QString key);

private:
    QMap<QString,SubScheme> m_map;
    bool m_result;
    QString m_name;
    QString m_author;
    QString m_uuid;
    QString m_background;
    QString m_caret;
    QString m_foreground;
    QString m_invisibles;
    QString m_lineHighLight;
    QString m_selection;
};

#endif // COLORSCHEME_H
