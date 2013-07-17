#ifndef PLISTDOCUMENTTEST_H
#define PLISTDOCUMENTTEST_H

#include "testcase.h"

class PListDocumentTest : public TestCase
{
    Q_OBJECT
public:
    DECLARE_TEST_CASE(PListDocumentTest);
private slots:
    void test();
};

#endif // PLISTDOCUMENTTEST_H
