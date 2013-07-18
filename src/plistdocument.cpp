#include <QFile>
#include <QDebug>
#include <QDateTime>

#include "plistdocument.h"

PListDocument::PListDocument(QObject *parent) :
    QObject(parent)
{
}

PListDocument::~PListDocument()
{

}

bool PListDocument::load(QString filename)
{
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

    if (root.nodeName() != ROOT_NODE)
        return false;

    QDomElement element = root.firstChildElement();

    return loadDict(element,m_dict);
}

bool PListDocument::save(QString filename)
{
}

QString PListDocument::getType(QDomElement &element, bool direct)
{
    if (element.isNull())
        return "";
    if (direct) {
        return element.nodeName();
    } else {
        QDomElement value = element.nextSiblingElement();
        if (value.isNull())
            return "";
        return value.nodeName();
    }
}

bool PListDocument::loadDict(QDomElement &element, PListDict &dict)
{
    if (element.isNull() || element.nodeName() != DICT_NODE)
        return false;

    QDomElement n = element.firstChildElement(KEY_NODE);
    QString type;
    QString key;
    QDomElement value;
    bool result;
    dict.clear();
    while (!n.isNull()) {
        type = getType(n);
        if (type.isEmpty())
            return false;

        value = n.nextSiblingElement();
        key = n.firstChild().nodeValue();

        if (type == STRING_NODE) {
            QString str;
            result = loadString(value,str);
            if (result) {
                dict.insert(key, str);
            }
        } else if (type == DICT_NODE) {
            PListDict subDict;
            result = loadDict(value,subDict);
            if (result)
                dict.insert(key,subDict);
        } else if (type == ARRAY_NODE) {
            PListArray array;
            result = loadArray(value,array);
            if (result)
                dict.insert(key,array);
        } else if (type == INTEGER_NODE) {
            int i;
            result = loadInteger(value, i);
            if(result)
                dict.insert(key,i);
        } else if (type == REAL_NODE) {
            float f;
            result = loadReal(value, f);
            if(result)
                dict.insert(key,f);
        } else if (type == DATE_NODE) {
            QDateTime date;
            result = loadDate(value, date);
            if(result)
                dict.insert(key,date);
        } else if (type == DATA_NODE) {
            QByteArray data;
            result = loadData(value, data);
            if(result)
                dict.insert(key,data);
        }
        n = n.nextSiblingElement(KEY_NODE);
    }
    return true;
}

bool PListDocument::loadArray(QDomElement &element, PListArray &list)
{
    if (element.isNull() || element.nodeName() != ARRAY_NODE)
        return false;

    list.clear();
    QDomElement n = element.firstChildElement();
    QString type;
    bool result = false;
    while (!n.isNull()) {
        type = getType(n,true);
        if (type.isEmpty())
            break;

        if (type == STRING_NODE) {
            QString str;
            result = loadString(n,str);
            if (result)
                list.append(str);
        } else if (type == DICT_NODE) {
            PListDict dict;
            result = loadDict(n,dict);
            if (result)
                list.append(dict);
        } else if (type == ARRAY_NODE) {
            PListArray array;
            result = loadArray(n,array);
            if (result)
                list.append(array);
        } else if (type == INTEGER_NODE) {
            int i;
            result = loadInteger(n, i);
            if(result)
                list.append(i);
        } else if (type == REAL_NODE) {
            float f;
            result = loadReal(n, f);
            if(result)
                list.append(f);
        } else if (type == DATE_NODE) {
            QDateTime date;
            result = loadDate(n, date);
            if(result)
                list.append(date);
        }
        else if (type == DATA_NODE) {
            QByteArray data;
            result = loadData(n, data);
            if(result)
                list.append(data);
        }
        n = n.nextSiblingElement();
    }
    return true;
}

bool PListDocument::loadString(QDomElement &element, QString &string)
{
    if (element.isNull() || element.nodeName() != STRING_NODE)
        return false;
    string = element.firstChild().nodeValue();
    return true;
}

bool PListDocument::loadInteger(QDomElement &element, int &value)
{
    if (element.isNull() || element.nodeName() != STRING_NODE)
        return false;
    value = element.firstChild().nodeValue().toInt();
    return true;
}

bool PListDocument::loadReal(QDomElement &element, float &value)
{
    if (element.isNull() || element.nodeName() != STRING_NODE)
        return false;
    value = element.firstChild().nodeValue().toFloat();
    return true;
}

bool PListDocument::loadDate(QDomElement &element, QDateTime &date)
{
    if (element.isNull() || element.nodeName() != STRING_NODE)
        return false;
    date = QDateTime::fromString(element.firstChild().nodeValue(),"yyyy-MM-dd hh:mm:ss");
    return true;
}

bool PListDocument::loadData(QDomElement &element, QByteArray &data)
{
    if (element.isNull() || element.nodeName() != STRING_NODE)
        return false;
    data = QByteArray::fromBase64(
                element.firstChild().nodeValue().toAscii());
    return true;
}

const PListDict & PListDocument::dict() const
{
    return m_dict;
}


