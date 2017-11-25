#include "variable.h"

Variable::Variable(QObject *parent) : QDjangoModel(parent) {
}

QString Variable::getName() const {
    return name;
}

void Variable::setName(const QString &value) {
    name = value;
}

QString Variable::getValue() const {
    return value;
}

void Variable::setValue(const QString &value) {
    this->value = value;
}

QString Variable::getType() const {
    return type;
}

void Variable::setType(const QString &value) {
    type = value;
}

QString Variable::getScope() const {
    return scope;
}

void Variable::setScope(const QString &value) {
    scope = value;
}

int Variable::getScopeId() const {
    return scopeId;
}

void Variable::setScopeId(int value) {
    scopeId = value;
}
