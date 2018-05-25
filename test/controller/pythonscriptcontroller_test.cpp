#include "pythonscriptcontroller_test.h"

PythonScriptController_Test::PythonScriptController_Test(QObject *parent) : QObject(parent) {
    this->variableController = new VariableController(this);
    initDatabase();
}

QSharedPointer<Request> PythonScriptController_Test::createRequest() {
    auto *request = new Request();
    request->setName("Test Request");
    request->setHost("api.github.com");
    request->setProto("https://");
    request->setRequestBody("{\"test\": \"value\"}");
    request->setRequestHeaders("Content-Type: application/json");

    request->save();

    auto *project = new Project();
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
    QString varName = QUuid::createUuid().toString();

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

    auto newVariable = this->variableController->getVariable(varName, CurrentDataController::getCurrentProjectId(), CurrentDataController::getCurrentRequestId());
    if (newVariable.data() == NULL) {
        QFAIL("No variable found after script executed");
    }

    QCOMPARE(newVariable.data()->getName(), varName);
}

void PythonScriptController_Test::test_executeScript_withGetVariables() {
    QString varName = QUuid::createUuid().toString();
    QString varValue = QUuid::createUuid().toString();
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
    auto newVariable = this->variableController->getVariable("test_getVariables", CurrentDataController::getCurrentProjectId(), CurrentDataController::getCurrentRequestId());
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

/**
 * Given: Multiple variables of different scopes with the same name
 * When: The Python getVar function is called for the variable
 * Then: The most specifically scoped variable value is chosen
 */
void PythonScriptController_Test::test_executeScript_withGetVariablesOrderedByScope() {
    auto request = this->createRequest();

    CurrentDataController::setCurrentProjectId(request.data()->project()->pk().toInt());
    CurrentDataController::setCurrentRequestId(request.data()->pk().toInt());

    QString varName = QUuid::createUuid().toString();
    QString globalVarVal = QUuid::createUuid().toString();
    QString projectVarVal = QUuid::createUuid().toString();
    QString localVarVal = QUuid::createUuid().toString();

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
    auto newVariable = this->variableController->getVariable("test_getVariables_local", -1, -1);
    if (newVariable.data() == NULL) {
        QFAIL("No variable found after script executed");
    }

    QCOMPARE(newVariable.data()->getValue(), localVarVal);
}
