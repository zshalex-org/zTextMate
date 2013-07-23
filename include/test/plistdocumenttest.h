#ifndef PLISTDOCUMENTTEST_H
#define PLISTDOCUMENTTEST_H

#include "testcase.h"

class PListDocumentTest : public TestCase
{
    Q_OBJECT
public:
    DECLARE_TEST_CASE(PListDocumentTest);
private slots:
    void testIsArray();
    void testIsArray_data();
    void testSplitNode();
    void testSplitNode_data();
    void testGetDict();
    void testColorsCheme();
};

#endif // PLISTDOCUMENTTEST_H
