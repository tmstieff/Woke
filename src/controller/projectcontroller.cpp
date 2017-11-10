#include "projectcontroller.h"

ProjectController::ProjectController(QObject *parent) : QObject(parent) {
}

QSharedPointer<QList<QSharedPointer<Project>>> ProjectController::getProjects() {
    QDjangoQuerySet<Project> allProjects = this->projects.orderBy(QStringList("name")).limit(0, 128);

    auto results = QSharedPointer<QList<QSharedPointer<Project>>>(new QList<QSharedPointer<Project>>());
    for (int i = 0; i < allProjects.size(); i++) {
        auto result = QSharedPointer<Project>(allProjects.at(i));
        results.data()->append(result);
    }

    return results;
}

QSharedPointer<Project> ProjectController::upsertDefaultProject() {
    QDjangoQuerySet<Project> resultSet = this->projects.orderBy(QStringList("id")).limit(0, 1);
    if (resultSet.size() == 1) {
        if (QString::compare(resultSet.at(0)->getName(), "Default") == 0) {
            return QSharedPointer<Project>(resultSet.at(0));
        }
    }

    Project *defaultProject = new Project(this);
    defaultProject->setName("Default");

    defaultProject->save();

    return QSharedPointer<Project>::create(defaultProject);
}

QSharedPointer<QList<QSharedPointer<Request>>> ProjectController::getRequests(int projectId) {
    auto results =
        this->requests.filter(QDjangoWhere("project_id", QDjangoWhere::Equals, projectId)).orderBy(QStringList("name"));

    auto projectRequests = QSharedPointer<QList<QSharedPointer<Request>>>(new QList<QSharedPointer<Request>>());
    for (int i = 0; i < results.size(); i++) {
        auto result = QSharedPointer<Request>(results.at(i));
        projectRequests.data()->append(result);
    }

    return projectRequests;
}

QSharedPointer<Project> ProjectController::getProject(int id) {
    auto result = this->projects.get(QDjangoWhere("id", QDjangoWhere::Equals, id));

    return QSharedPointer<Project>(result);
}
