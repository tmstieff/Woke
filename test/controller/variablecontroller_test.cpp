#include "variablecontroller_test.h"

VariableController_Test::VariableController_Test(QObject *parent) : QObject(parent) {
    this->variableController = new VariableController();
}

void VariableController_Test::test_replaceVariables() {
    auto string = QString("Some text\nSome-Header-123: val\nAuthentication: {{auth_token}}\nAnother-Header: text");

    Variable authToken;
    authToken.setName("auth_token");
    authToken.setValue("fake_auth_token");
    authToken.setScope("global");
    authToken.setScopeId(0);
    authToken.save();

    this->variableController->replaceVariables(string, 0, 0);

    QCOMPARE(string.indexOf("fake_auth_token"), 47);
}

void VariableController_Test::test_replaceVariables_multipleSame() {
    auto string =
        QString("Some text\nSome-Header-123: {{auth_token2}}\nAuthentication: {{auth_token2}}\nAnother-Header: text");

    Variable authToken;
    authToken.setName("auth_token2");
    authToken.setValue("fake_auth_token");
    authToken.setScope("global");
    authToken.setScopeId(0);
    authToken.save();

    this->variableController->replaceVariables(string, 0, 0);

    QCOMPARE(string.indexOf("fake_auth_token"), 27);
    QCOMPARE(string.indexOf("fake_auth_token", 30), 59);
}

void VariableController_Test::test_replaceVariables_multipleDifferent() {
    auto string =
        QString("Some text\nSome-Header-123: {{some_var}}\nAuthentication: {{some_other_var}}\nAnother-Header: text");

    Variable someVar;
    someVar.setName("some_var");
    someVar.setValue("some_val");
    someVar.setScope("global");
    someVar.setScopeId(0);
    someVar.save();

    Variable someOtherVar;
    someOtherVar.setName("some_other_var");
    someOtherVar.setValue("some_other_val");
    someOtherVar.setScope("global");
    someOtherVar.setScopeId(0);
    someOtherVar.save();

    this->variableController->replaceVariables(string, 0, 0);

    QCOMPARE(string.indexOf("some_val"), 27);
    QCOMPARE(string.indexOf("some_other_val"), 52);
}

void VariableController_Test::test_replaceVariables_multipleDifferentAndAsHeaderName() {
    auto string =
        QString("Some text\n{{header_name}}: {{some_var}}\nAuthentication: {{some_other_var}}\nAnother-Header: text");

    Variable headerNameVar;
    headerNameVar.setName("header_name");
    headerNameVar.setValue("Content-Type");
    headerNameVar.setScope("global");
    headerNameVar.setScopeId(0);
    headerNameVar.save();

    Variable someVar;
    someVar.setName("some_var");
    someVar.setValue("some_val");
    someVar.setScope("global");
    someVar.setScopeId(0);
    someVar.save();

    Variable someOtherVar;
    someOtherVar.setName("some_other_var");
    someOtherVar.setValue("some_other_val");
    someOtherVar.setScope("global");
    someOtherVar.setScopeId(0);
    someOtherVar.save();

    this->variableController->replaceVariables(string, 0, 0);

    QCOMPARE(string.indexOf("Content-Type"), 10);
    QCOMPARE(string.indexOf("some_val"), 27);
    QCOMPARE(string.indexOf("some_other_val"), 52);
}

