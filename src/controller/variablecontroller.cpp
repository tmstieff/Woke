#include "variablecontroller.h"

void setVariable(std::string &name, std::string &value, QString &scope, int scopeId) {
    auto qtName = QString(name.c_str());
    auto qtValue = QString(value.c_str());

    QDjangoQuerySet<Variable> variables;
    auto existingVariable = variables.get(QDjangoWhere("name", QDjangoWhere::Equals, qtName) &&
                                          QDjangoWhere("scope", QDjangoWhere::Equals, scope) &&
                                          QDjangoWhere("scopeId", QDjangoWhere::Equals, scopeId));

    QSharedPointer<Variable> variable;
    if (existingVariable != NULL) {
        variable = QSharedPointer<Variable>(existingVariable);
    } else {
        variable = QSharedPointer<Variable>(new Variable());
    }

    variable.data()->setName(qtName);
    variable.data()->setValue(qtValue);
    variable.data()->setScope(scope);
    variable.data()->setScopeId(scopeId);

    variable.data()->save();
}

void setGlobalVariable(std::string &name, std::string &value) {
    auto scope = QString("global");
    setVariable(name, value, scope, 0);
}

void setProjectVariable(std::string &name, std::string &value) {
    auto scope = QString("project");
    setVariable(name, value, scope, CurrentDataController::getCurrentProjectId());
}

void setLocalVariable(std::string &name, std::string &value) {
    auto scope = QString("local");
    setVariable(name, value, scope, CurrentDataController::getCurrentRequestId());
}

/**
 * @brief
 *
 * Search for a variable by name. Since this method is always called in a request script, the
 * project and request IDs can be infurred from the current request.
 *
 * @param name - The variable name to search for
 */
std::string getVariable(std::string &name) {
    auto qtName = QString(name.c_str());

    QDjangoQuerySet<Variable> variables;

    // Get all variables with the requested name, and filter by name, and the specified scopes
    // Filter in code below to find the highest scoped variable if multiple exist. ScopeID 0
    // always implies global
    QSharedPointer<Variable> globalVar = QSharedPointer<Variable>(variables.get(
        QDjangoWhere("name", QDjangoWhere::Equals, qtName) && QDjangoWhere("scopeId", QDjangoWhere::Equals, 0)));
    QSharedPointer<Variable> projectVar = QSharedPointer<Variable>(
        variables.get(QDjangoWhere("name", QDjangoWhere::Equals, qtName) &&
                      QDjangoWhere("scopeId", QDjangoWhere::Equals, CurrentDataController::getCurrentProjectId()) &&
                      QDjangoWhere("scope", QDjangoWhere::Equals, "project")));
    QSharedPointer<Variable> localVar = QSharedPointer<Variable>(
        variables.get(QDjangoWhere("name", QDjangoWhere::Equals, qtName) &&
                      QDjangoWhere("scopeId", QDjangoWhere::Equals, CurrentDataController::getCurrentRequestId()) &&
                      QDjangoWhere("scope", QDjangoWhere::Equals, "local")));

    if (localVar.data() != NULL) {
        return localVar.data()->getValue().toStdString();
    } else if (projectVar.data() != NULL) {

        return projectVar.data()->getValue().toStdString();
    } else if (globalVar.data() != NULL) {
        return globalVar.data()->getValue().toStdString();
    }

    // Probably need to revisit this
    return std::string("");
}

VariableController::VariableController(QObject *parent) : QObject(parent) {
}

QSharedPointer<Variable> VariableController::getVariable(const QString &name, int projectId, int scopeId) {
    auto variable = this->variables.get(QDjangoWhere("name", QDjangoWhere::Equals, name));




    return QSharedPointer<Variable>(variable);
}

void VariableController::replaceVariables(QString &string, int projectId, int requestId) {
    QSet<QString> variables = findVariables(string);

    auto variableModels = QList<QSharedPointer<Variable>>();
    Q_FOREACH (const QString &varName, variables) {
      variableModels.push_back(this->getVariable(varName, projectId, requestId));
    }

    for (int i = 0; i < variableModels.length(); i++) {
        if (variableModels.at(i).data() != NULL) {
            QString before = QString("{{");
            before.append(variableModels.at(i).data()->getName());
            before.append(QString("}}"));

            QString after = variableModels.at(i).data()->getValue();

            string.replace(before, after);
        }
    }
}

QSet<QString> VariableController::findVariables(QString &string) {
    QSet<QString> variables;

    QRegularExpression rx;
    rx.setPattern("{{([A-z0-9_-]+)}}");

    QRegularExpressionMatchIterator iter = rx.globalMatch(string);
    while (iter.hasNext()) {
        auto captured = iter.next().captured(1);

        qDebug() << "Found capture " << captured;

        variables.insert(captured);
    }

    return variables;
}
