#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QObject>
#include <QUuid>
#include <QColor>

#include "plistdocument.h"

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

    QVariant getDict(QString key);
    bool loadColorScheme(QString filename);

private:
    PListDocument m_plist;
    PListDict m_map;
    bool m_result;
};

#endif // COLORSCHEME_H
