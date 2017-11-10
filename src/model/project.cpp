#include "project.h"

Project::Project(QObject *parent) : QDjangoModel(parent) {
}

QString Project::getName() const {
    return this->m_name;
}

void Project::setName(const QString &name) {
    this->m_name = name;
}
