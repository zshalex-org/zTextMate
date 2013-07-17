#include <QCoreApplication>
#include "testsuite.h"

int main(int argc, char *argv[])
{
    return TestSuite::instance()->execute(argc,argv);
}
