#ifndef VARIABLECONTROLLER_H
#define VARIABLECONTROLLER_H

#include "../model/variable.h"
#include "currentdatacontroller.h"
#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QSet>
#include <QSharedPointer>
#include <pybind11/pybind11.h>
#include <qdjango/db/QDjangoModel.h>
#include <qdjango/db/QDjangoQuerySet.h>

namespace py = pybind11;

void setVariable(std::string &name, std::string &value, QString &scope, int scopeId);
void setGlobalVariable(std::string &name, std::string &value);
void setProjectVariable(std::string &name, std::string &value);
void setLocalVariable(std::string &name, std::string &value);
std::string getVariable(std::string &name);

class VariableController : public QObject {
    Q_OBJECT
  public:
    explicit VariableController(QObject *parent = nullptr);

    QSharedPointer<Variable> getVariable(const QString &name);
    void replaceVariables(QString &string, int projectId, int requestId);

  private:
    QDjangoQuerySet<Variable> variables;
    QSet<QString> findVariables(QString &string);
};

#endif // VARIABLECONTROLLER_H
