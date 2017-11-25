#ifndef HISTORYCONTROLLER_TEST_H
#define HISTORYCONTROLLER_TEST_H

#include "../../src/controller/historycontroller.h"
#include "../testutils.h"
#include <QObject>
#include <QTest>

class HistoryController_Test : public QObject {
    Q_OBJECT

  public:
    HistoryController_Test();

  private:
    HistoryController *historyController;

  private Q_SLOTS:
    void initTestCase();
    void test_addEntry_defaultName();
    void test_getLatest();
};

#endif // HISTORYCONTROLLER_TEST_H
