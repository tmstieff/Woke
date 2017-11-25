#ifndef VARIABLECONTROLLER_TEST_H
#define VARIABLECONTROLLER_TEST_H

#include "../../src/controller/variablecontroller.h"
#include <QObject>
#include <QTest>

class VariableController_Test : public QObject {
    Q_OBJECT
  public:
    explicit VariableController_Test(QObject *parent = 0);

  private:
    VariableController *variableController;

  private Q_SLOTS:
    void test_replaceVariables();
    void test_replaceVariables_multipleSame();
    void test_replaceVariables_multipleDifferent();
};

#endif // VARIABLECONTROLLER_TEST_H
