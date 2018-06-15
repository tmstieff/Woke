#include "projectcontroller.h"

ProjectController::ProjectController(QObject *parent) : QObject(parent) {
    //QObject::connect(this, &ProjectController::saveProject, this, SLOT(on_saveProject(Project&)));
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
        auto defaultName = "Default";
        QSharedPointer<Project> projectTarget = QSharedPointer<Project>::create();
        resultSet.at(0, projectTarget.data());
        if (QString::compare(projectTarget.data()->getName(), defaultName) == 0) {
            auto result = resultSet.at(0);

            return QSharedPointer<Project>(result);
        }
    }

    Project *defaultProject = new Project(this);
    defaultProject->setName("Default");

    bool saved = defaultProject->save();
    qDebug() << "Default project saved?" << saved;

    return QSharedPointer<Project>(defaultProject);
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

Project *ProjectController::getProjectPointer(int id, QObject *parent = 0) {
    auto result = this->projects.get(QDjangoWhere("id", QDjangoWhere::Equals, id));

    if (result != nullptr) {
        result->setParent(parent);
    }

    return result;
}

QSharedPointer<Project> ProjectController::getProject(const QString &name) {
    auto result = this->projects.get(QDjangoWhere("name", QDjangoWhere::Equals, name));
    return QSharedPointer<Project>(result);
}

bool ProjectController::deleteByName(QString &name) {
    auto project = this->getProject(name);

    if (!project.isNull()) {
        project.data()->remove();
        project.clear();

        return true;
    }

    return false;
}

void ProjectController::on_saveProject(Project &project) {
    project.save();

    Q_EMIT event_saveProjectSuccess(project);
}
