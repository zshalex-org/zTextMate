#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QObject>
#include <QColor>
#include <QMap>

struct SubScheme
{
    QString name;
    QString scope;
    QColor background;
    QColor foreground;
    QString fontStyle;
    bool italic;
    bool underline;
};

class ColorScheme : public QObject
{
    Q_OBJECT
public:
    explicit ColorScheme(QObject *parent = 0);

    const QString & name() const;
    const QString & author() const;
    const QString & uuid() const;
    const QColor & background() const;
    const QColor & caret() const;
    const QColor & foreground() const;
    const QColor & invisibles() const;
    const QColor & lineHighLight() const;
    const QColor & selection() const;

    bool loadColorScheme(QString filename);
    SubScheme scheme(QString key);
private:
    QMap<QString,SubScheme> m_map;
    QString m_name;
    QString m_author;
    QString m_uuid;
    QColor m_background;
    QColor m_caret;
    QColor m_foreground;
    QColor m_invisibles;
    QColor m_lineHighLight;
    QColor m_selection;
};

#endif // COLORSCHEME_H
