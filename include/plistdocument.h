#ifndef PLISTDOCUMENT_H
#define PLISTDOCUMENT_H

#include <QObject>
#include <QMap>
#include <QDomDocument>
#include <QVariant>
#include <QStringList>

#define ROOT_NODE_NAME    "plist"
#define DICT_NODE_NAME    "dict"
#define STRING_NODE_NAME  "string"
#define ARRAY_NODE_NAME   "array"
#define KEY_NODE_NAME     "key"
#define INTEGER_NODE_NAME "integer"
#define REAL_NODE_NAME    "real"
#define DATE_NODE_NAME    "date"
#define DATA_NODE_NAME    "deta"
#define TRUE_NODE_NAME    "true"
#define FALSE_NODE_NAME   "false"

typedef QMap<QString, QVariant> PListDict;
typedef QList<QVariant> PListArray;

class PListDocument : public QObject
{
    Q_OBJECT
public:
    enum NODE_TYPE {
        DICT_NODE = 0,
        ARRAY_NODE,
        STRING_NODE,
        INTEGER_NODE,
        REAL_NODE,
        DATE_NODE,
        DATA_NODE,
        TRUE_NODE,
        FALSE_NODE
    };

    explicit PListDocument(QObject *parent = 0);
    ~PListDocument();

    const QVariant & root() const;
    QVariant getValue(QString key);
    QVariant getValue(const QVariant &node, QString key);

    void setRoot(const QVariant &root);

    bool load(const QString &filename);
    bool save(const QString &filename);
private:
    QVariant loadValue(const QDomElement &element);

    bool loadDict(const QDomElement &element, PListDict &dict);
    bool loadArray(const QDomElement &element, PListArray &list);
    bool loadString(const QDomElement &element, QString &string);
    bool loadInteger(const QDomElement &element, int &value);
    bool loadReal(const QDomElement &element, qreal &value);
    bool loadDate(const QDomElement &element, QDateTime &date);
    bool loadData(const QDomElement &element, QByteArray &data);

    void getKeyAndIndex(QString node, QString &key, int &index);
private:
    static QStringList m_nodeMap;
    PListDict m_dict;
    QVariant m_root;
};

#endif // PLISTDOCUMENT_H
