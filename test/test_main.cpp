#include "controller/historycontroller_test.h"
#include "mainwindow_test.h"
#include "urlutil_test.h"
#include "view/requestitem_test.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    UrlUtil_Test urlutil_test;
    RequestItem_Test requestItem_test;
    MainWindow_Test mainWindow_test;
    HistoryController_Test historyController_test;

    QDjango::setDebugEnabled(true);

    // multiple test suites can be ran like this
    return QTest::qExec(&urlutil_test, argc, argv) | QTest::qExec(&requestItem_test, argc, argv) |
           QTest::qExec(&mainWindow_test, argc, argv) | QTest::qExec(&historyController_test, argc, argv);
}
