#include <QRegExp>
#include <QDebug>

#include "test/plistdocumenttest.h"
#include "plistdocument.h"
#include "colorscheme.h"

INIT_TEST_CASE(PListDocumentTest,"plsitTest");

void PListDocumentTest::testIsArray()
{
    QFETCH(QString,str);
    QFETCH(bool,result);
    PListDocument doc;
    QCOMPARE(doc.isArray(str),result);
}

void PListDocumentTest::testIsArray_data()
{
    QTest::addColumn<QString>("str");
    QTest::addColumn<bool>("result");
    QTest::newRow("1") << "test[1]" << true;
    QTest::newRow("2") << "test" << false;
    QTest::newRow("3") << "test[" << false;
    QTest::newRow("4") << "test[1" << false;
    QTest::newRow("5") << "teste[343f]" << false;
}

void PListDocumentTest::testSplitNode()
{
    QFETCH(QString,str);
    QFETCH(bool,result);
    QFETCH(QString,key);
    QFETCH(int,index);

    PListDocument doc;
    QString tmpkey;
    int tmpindex;
    QCOMPARE(doc.splitKeyAndIndex(str,tmpkey,tmpindex),result);
    QCOMPARE(key,tmpkey);
    QCOMPARE(index,tmpindex);
}

void PListDocumentTest::testSplitNode_data()
{
    QTest::addColumn<QString>("str");
    QTest::addColumn<bool>("result");
    QTest::addColumn<QString>("key");
    QTest::addColumn<int>("index");
    QTest::newRow("1") << "test[1]" << true << "test" << 1;
    QTest::newRow("1") << "te_3d2st[1332]" << true << "te_3d2st" << 1332;
    QTest::newRow("1") << "test[1" << false << "" << -1;
}

void PListDocumentTest::testGetDict()
{
    PListDocument doc;
    QCOMPARE(doc.load("Amy.xml"),true);
    QVariant var = doc.getValue("name");
    QCOMPARE(var.toString(),QString("Amy"));
    var = doc.getValue("settings");
    QCOMPARE(QString(var.typeName()),QString("QVariantList"));
    var = doc.getValue("settings[0].settings.background");
    QCOMPARE(var.toString(),QString("#200020"));
}

void PListDocumentTest::testColorsCheme()
{
    ColorScheme scheme;
    SubScheme value;

    bool result = scheme.loadColorScheme("Amy.xml");
    value = scheme.scheme("comment.block");
    QCOMPARE(result,true);
    QCOMPARE(scheme.name(),QString("Amy"));
    QCOMPARE(scheme.background(),QColor("#200020"));
    QCOMPARE(scheme.caret(),QColor("#7070FF"));
    QCOMPARE(value.name,QString("Comment"));
    QCOMPARE(value.scope,QString("comment.block"));
    QCOMPARE(value.background,QColor("#200020"));
    QCOMPARE(value.fontStyle,QString("italic"));
    QCOMPARE(value.foreground,QColor("#404080"));

    value = scheme.scheme("string");
    QCOMPARE(value.foreground,QColor("#999999"));
}
