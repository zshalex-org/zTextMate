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
    QCOMPARE(doc.load("Amy.tmTheme"),true);
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

    bool result = scheme.loadColorScheme("Amy.tmTheme");
    QCOMPARE(result,true);
    QCOMPARE(scheme.background(),QString("#200020"));
    QVariant var = scheme.getDict("comment.block");
    QCOMPARE(PListDocument::getValue(var,"name").toString(),
             QString("Comment"));
    QCOMPARE(PListDocument::getValue(var,"scope").toString(),
             QString("comment.block"));
}
