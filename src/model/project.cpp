#include "project.h"

Project::Project(QObject *parent) : QDjangoModel(parent) {
}

QString Project::getName() const {
    return this->name;
}

void Project::setName(const QString &name) {
    this->name = name;
}

Q_DECLARE_METATYPE(Project *)
