#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include "../model/project.h"
#include "../model/request.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <qdjango/db/QDjangoModel.h>
#include <qdjango/db/QDjangoQuerySet.h>

class ProjectController : public QObject {
    Q_OBJECT

  Q_SIGNALS:
    void event_saveProjectSuccess(Project &project);

  public Q_SLOTS:
    void on_saveProject(Project &project);

  public:
    ProjectController(QObject *parent = 0);

    QSharedPointer<QList<QSharedPointer<Project>>> getProjects();
    QSharedPointer<QList<QSharedPointer<Request>>> getRequests(int projectId);
    QSharedPointer<Project> upsertDefaultProject();
    Project *getProjectPointer(int id, QObject *parent);
    QSharedPointer<Project> getProject(int id);
    QSharedPointer<Project> getProject(const QString &name);

  private:
    QDjangoQuerySet<Project> projects;
    QDjangoQuerySet<Request> requests;
};

#endif // PROJECTCONTROLLER_H
