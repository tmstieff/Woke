#ifndef PYTHONSCRIPTCONTROLLER_TEST_H
#define PYTHONSCRIPTCONTROLLER_TEST_H

#include "../../src/controller/currentdatacontroller.h"
#include "../../src/controller/pythonscriptcontroller.h"
#include "../../src/controller/variablecontroller.h"
#include "../../src/model/project.h"
#include "../../src/model/request.h"
#include "../../src/model/variable.h"
#include "../testutils.h"
#include <QObject>
#include <QRegExp>
#include <QSharedPointer>
#include <QTest>
#include <QUuid>

class PythonScriptController_Test : public QObject {
    Q_OBJECT
  public:
    explicit PythonScriptController_Test(QObject *parent = 0);

  private:
    QSharedPointer<Request> createRequest();
    QSharedPointer<Variable> createVariable(QString &varName, QString &scope, QString &varValue, int scopeId = 0);

    PythonScriptController &pythonScriptController = PythonScriptControllerFactory::getInstance();
    VariableController *variableController;

  private Q_SLOTS:
    void initTestCase();
    void test_executeScript_basic();
    void test_executeScript_withSetVariables();
    void test_executeScript_withGetVariables();
    void test_executeScript_withGetVariablesOrderedByScope();
};

#endif // PYTHONSCRIPTCONTROLLER_TEST_H
