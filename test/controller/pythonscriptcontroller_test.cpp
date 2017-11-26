#include "pythonscriptcontroller_test.h"

PythonScriptController_Test::PythonScriptController_Test(QObject *parent) : QObject(parent) {
    this->variableController = new VariableController(this);
    initDatabase();
}

QSharedPointer<Request> PythonScriptController_Test::createRequest() {
    Request *request = new Request();
    request->setName("Test Request");
    request->setHost("api.github.com");
    request->setProto("https://");
    request->setRequestBody("{\"test\": \"value\"}");
    request->setRequestHeaders("Content-Type: application/json");

    request->save();

    Project *project = new Project(0);
    project->setName("Test Project");
    project->save();

    request->setProject(project);

    request->save();

    return QSharedPointer<Request>(request);
}

void PythonScriptController_Test::initTestCase() {
}

/**
 * Given: A basic python script
 * When: A new request or project object is created
 * Then: The script executes sucessfully without an exception
 */
void PythonScriptController_Test::test_executeScript_basic() {
    auto script = QString();
    script.append("print('Hey')");

    auto request = this->createRequest();
    request.data()->setRequestScript(script);

    CurrentDataController::setCurrentProjectId(request.data()->project()->pk().toInt());
    CurrentDataController::setCurrentRequestId(request.data()->pk().toInt());

    auto result = this->pythonScriptController.executeScript(script, request);

    QCOMPARE(result, true);
}

/**
 * Given: A script that calls setGlobalVariable
 * When: The script is executed
 * Then: The new variable is set in the database
 */
void PythonScriptController_Test::test_executeScript_withSetVariables() {
    auto varName = QUuid::createUuid().toString().replace(QRegExp("[{|}]"), "");

    auto script = QString();
    script.append("setGlobalVar('");
    script.append(varName);
    script.append("', '12GHJghj')");

    auto request = this->createRequest();
    request.data()->setRequestScript(script);

    CurrentDataController::setCurrentProjectId(request.data()->project()->pk().toInt());
    CurrentDataController::setCurrentRequestId(request.data()->pk().toInt());

    auto result = this->pythonScriptController.executeScript(script, request);

    QCOMPARE(result, true);

    auto newVariable = this->variableController->getVariable(varName);
    if (newVariable.data() == NULL) {
        QFAIL("No variable found after script executed");
    }

    QCOMPARE(newVariable.data()->getName(), varName);
}

void PythonScriptController_Test::test_executeScript_withGetVariables() {
    auto varName = QUuid::createUuid().toString().replace(QRegExp("[{|}]"), "");
    auto varValue = QUuid::createUuid().toString().replace(QRegExp("[{|}]"), "");
    auto var = QSharedPointer<Variable>(new Variable());
    var.data()->setName(varName);
    var.data()->setValue(varValue);
    var.data()->setScope("global");
    var.data()->setScopeId(0);
    var.data()->save();

    auto script = QString();
    script.append("get_var =  getVar('");
    script.append(varName);
    script.append("')");
    script.append("\n");
    script.append("setGlobalVar('test_getVariables', get_var)");

    auto request = this->createRequest();
    request.data()->setRequestScript(script);

    CurrentDataController::setCurrentProjectId(request.data()->project()->pk().toInt());
    CurrentDataController::setCurrentRequestId(request.data()->pk().toInt());

    auto result = this->pythonScriptController.executeScript(script, request);

    QCOMPARE(result, true);
    auto newVariable = this->variableController->getVariable("test_getVariables");
    if (newVariable.data() == NULL) {
        QFAIL("No variable found after script executed");
    }

    QCOMPARE(newVariable.data()->getValue(), varValue);
}

QSharedPointer<Variable> PythonScriptController_Test::createVariable(QString &varName, QString &scope,
                                                                     QString &varValue, int scopeId) {
    auto var = QSharedPointer<Variable>(new Variable());
    var.data()->setName(varName);
    var.data()->setValue(varValue);
    var.data()->setScope(scope);
    var.data()->setScopeId(scopeId);
    var.data()->save();

    return var;
}

void PythonScriptController_Test::test_executeScript_withGetVariablesOrderedByScope() {
    auto request = this->createRequest();

    CurrentDataController::setCurrentProjectId(request.data()->project()->pk().toInt());
    CurrentDataController::setCurrentRequestId(request.data()->pk().toInt());

    auto varName = QUuid::createUuid().toString().replace(QRegExp("[{|}]"), "");
    auto globalVarVal = QUuid::createUuid().toString().replace(QRegExp("[{|}]"), "");
    auto projectVarVal = QUuid::createUuid().toString().replace(QRegExp("[{|}]"), "");
    auto localVarVal = QUuid::createUuid().toString().replace(QRegExp("[{|}]"), "");

    auto global = QString("global");
    auto globalVar = createVariable(varName, global, globalVarVal);
    auto project = QString("project");
    auto projectVar = createVariable(varName, project, projectVarVal, request.data()->project()->pk().toInt());
    auto local = QString("local");
    auto localVar = createVariable(varName, local, localVarVal, request.data()->pk().toInt());

    auto script = QString();
    script.append("get_var =  getVar('");
    script.append(varName);
    script.append("')");
    script.append("\n");
    script.append("setGlobalVar('test_getVariables_local', get_var)");

    request.data()->setRequestScript(script);

    auto result = this->pythonScriptController.executeScript(script, request);

    QCOMPARE(result, true);
    auto newVariable = this->variableController->getVariable("test_getVariables_local");
    if (newVariable.data() == NULL) {
        QFAIL("No variable found after script executed");
    }

    QCOMPARE(newVariable.data()->getValue(), localVarVal);
}
