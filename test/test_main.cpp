#include <QtTest>
#include "urlutil_test.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    UrlUtil_Test urlutil_test;
    // multiple test suites can be ran like this
    return QTest::qExec(&urlutil_test, argc, argv);
}
