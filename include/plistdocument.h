#ifndef PLISTDOCUMENT_H
#define PLISTDOCUMENT_H

#include <QObject>
#include <QMap>
#include <QDomDocument>
#include <QVariant>

#define ROOT_NODE "plist"
#define DICT_NODE "dict"
#define STRING_NODE "string"
#define ARRAY_NODE "array"
#define KEY_NODE "key"
#define INTEGER_NODE "integer"
#define REAL_NODE "real"
#define DATE_NODE "date"
#define DATA_NODE "deta"

typedef QMap<QString, QVariant> PListDict;
typedef QList<QVariant> PListArray;

class PListDocument : public QObject
{
    Q_OBJECT
public:
    explicit PListDocument(QObject *parent = 0);
    ~PListDocument();

    const PListDict & dict() const;

    bool load(QString filename);
    bool save(QString filename);
private:
    QString getType(QDomElement &element, bool direct = false);

    bool loadDict(QDomElement &element, PListDict &dict);
    bool loadArray(QDomElement &element, PListArray &list);
    bool loadString(QDomElement &element, QString &string);
    bool loadInteger(QDomElement &element, int &value);
    bool loadReal(QDomElement &element, float &value);
    bool loadDate(QDomElement &element, QDateTime &date);
    bool loadData(QDomElement &element, QByteArray &data);
//    bool load
private:
    PListDict m_dict;
};

#endif // PLISTDOCUMENT_H
