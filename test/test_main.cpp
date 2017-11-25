#include "controller/historycontroller_test.h"
#include "controller/projectcontroller_test.h"
#include "controller/pythonscriptcontroller_test.h"
#include "controller/variablecontroller_test.h"
#include "mainwindow_test.h"
#include "urlutil_test.h"
#include "view/requestitem_test.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    UrlUtil_Test urlutil_test;
    RequestItem_Test requestItem_test;
    MainWindow_Test mainWindow_test;
    HistoryController_Test historyController_test;
    ProjectController_Test projectController_test;
    PythonScriptController_Test pythonScriptController_test;
    VariableController_Test variableController_test;

    QDjango::setDebugEnabled(true);

    // multiple test suites can be ran like this
    return QTest::qExec(&urlutil_test, argc, argv) | QTest::qExec(&requestItem_test, argc, argv) |
           QTest::qExec(&mainWindow_test, argc, argv) | QTest::qExec(&historyController_test, argc, argv) |
           QTest::qExec(&projectController_test, argc, argv) | QTest::qExec(&pythonScriptController_test, argc, argv) |
           QTest::qExec(&variableController_test, argc, argv);
}
