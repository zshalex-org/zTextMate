#include <QFile>
#include <QDebug>
#include <QDateTime>

#include "plistdocument.h"

QStringList PListDocument::m_nodeMap(
        QStringList() << DICT_NODE_NAME << ARRAY_NODE_NAME
        << STRING_NODE_NAME << INTEGER_NODE_NAME << REAL_NODE_NAME
        << DATE_NODE_NAME << DATA_NODE_NAME << TRUE_NODE_NAME << FALSE_NODE_NAME);

PListDocument::PListDocument(QObject *parent) :
    QObject(parent)
{
    QString tmp = "sdfsdf[3]";
    QString key;
    int index;
    getKeyAndIndex(tmp,key,index);
    qDebug() << key << index;
}

PListDocument::~PListDocument()
{

}

const QVariant &PListDocument::root() const
{
    return m_root;
}

QVariant PListDocument::getValue(QString key)
{
    return getValue(m_root,key);
}

QVariant PListDocument::getValue(const QVariant &node, QString key)
{
    QVariant result;
    QStringList keys = key.split(".");
    QString subKey = "";
    qDebug() << keys;
    if (keys.count() == 0)
        return result;
    if (keys.count() >= 1) {
        qDebug() << node.typeName();
        if (QString(node.typeName()) == "QVariantMap") {
            PListDict dict = node.value<QVariantMap>();
            result = dict.value(keys.at(0));
        } else if (QString(node.typeName()) == "QVariantList") {
//            int begin = keys.at(0)

        } else {
            return result;
        }
    }
    if (keys.count() > 1){
        subKey = key.right(key.count() - keys.at(0).count() - 1);
        result = getValue(result, subKey);
    }
    return result;
}


void PListDocument::setRoot(const QVariant &root)
{
    m_root = root;
}

bool PListDocument::load(const QString &filename)
{
    m_root.clear();
    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!doc.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();

    QDomElement root = doc.documentElement();

    if (root.nodeName() != ROOT_NODE_NAME)
        return false;

    QDomElement element = root.firstChildElement();

    m_root = loadValue(element);

    return m_root.isValid();
}

bool PListDocument::save(const QString &)
{
    return false;
}

QVariant PListDocument::loadValue(const QDomElement &element)
{
    QVariant result;
    if (element.isNull())
        return result;
    QString type = element.nodeName();
    switch(m_nodeMap.indexOf(type)) {
    case DICT_NODE: {
        PListDict dict;
        if (loadDict(element,dict))
            result = dict;
        break;
    }
    case ARRAY_NODE: {
        PListArray array;
        if (loadArray(element,array))
            result = array;
        break;
    }
    case STRING_NODE: {
        QString str;
        if (loadString(element,str))
            result = str;
        break;
    }
    case INTEGER_NODE: {
        int value;
        if (loadInteger(element,value))
            result = value;
        break;
    }
    case REAL_NODE: {
        qreal value;
        if (loadReal(element,value))
            result = value;
        break;
    }
    case DATE_NODE: {
        QDateTime date;
        if (loadDate(element,date))
            result = date;
        break;
    }
    case TRUE_NODE: {
        result = true;
        break;
    }
    case FALSE_NODE: {
        result = false;
        break;
    }
    default:
        break;
    }
    return result;
}

bool PListDocument::loadDict(const QDomElement &element, PListDict &dict)
{
    if (element.isNull() || element.nodeName() != DICT_NODE_NAME) {
        return false;
    }

    QDomElement n = element.firstChildElement(KEY_NODE_NAME);
    QVariant var;
    QDomElement value;
    dict.clear();
    while (!n.isNull()) {
        value = n.nextSiblingElement();
        if (value.isNull()) {
            return false;
        }
        var = loadValue(value);
        if (!var.isValid()) {
            return false;
        }
        dict.insert(n.firstChild().nodeValue(),
                    var);
        n = n.nextSiblingElement(KEY_NODE_NAME);
    }
    return true;
}

bool PListDocument::loadArray(const QDomElement &element, PListArray &list)
{
    if (element.isNull() || element.nodeName() != ARRAY_NODE_NAME)
        return false;

    list.clear();
    QDomElement n = element.firstChildElement();
    QVariant var;
    while (!n.isNull()) {
        var = loadValue(n);
        if (!var.isValid())
            return false;
        list.append(var);
        n = n.nextSiblingElement();
    }
    return true;
}

bool PListDocument::loadString(const QDomElement &element, QString &string)
{
    if (element.isNull() || element.nodeName() != STRING_NODE_NAME) {
        return false;
    }
    string = element.firstChild().nodeValue();
    return true;
}

bool PListDocument::loadInteger(const QDomElement &element, int &value)
{
    if (element.isNull() || element.nodeName() != INTEGER_NODE_NAME) {
        return false;
    }
    value = element.firstChild().nodeValue().toInt();
    return true;
}

bool PListDocument::loadReal(const QDomElement &element, qreal &value)
{
    if (element.isNull() || element.nodeName() != REAL_NODE_NAME) {
        return false;
    }
    value = element.firstChild().nodeValue().toDouble();
    return true;
}

bool PListDocument::loadDate(const QDomElement &element, QDateTime &date)
{
    if (element.isNull() || element.nodeName() != DATE_NODE_NAME) {
        return false;
    }
    date = QDateTime::fromString(element.firstChild().nodeValue(),"yyyy-MM-dd hh:mm:ss");
    return true;
}

bool PListDocument::loadData(const QDomElement &element, QByteArray &data)
{
    if (element.isNull() || element.nodeName() != DATA_NODE_NAME) {
        return false;
    }
    data = QByteArray::fromBase64(
                element.firstChild().nodeValue().toLatin1());
    return true;
}

void PListDocument::getKeyAndIndex(QString node, QString &key, int &index)
{
    QString tmp = node.section("[",1);
    if (!tmp.endsWith("]"))
        return;
    QString indexStr = tmp.remove("]");
    bool ok;
    int tmpIndex = indexStr.toInt(&ok);
    if (ok)
        index = tmpIndex;

    key = node.left(node.count() - indexStr.count() - 2);
}
