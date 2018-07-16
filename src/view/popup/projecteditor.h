#ifndef PROJECTEDITOR_H
#define PROJECTEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QSharedPointer>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QMetaObject>
#include "../projectitem.h"
#include "../../model/project.h"
#include "../../controller/projectcontroller.h"

namespace Ui {
class ProjectEditor;
}

class ProjectEditor : public QWidget
{
    Q_OBJECT

Q_SIGNALS:
    void event_saveProject(Project &project);
    void event_deleteProject(QString &name);

public Q_SLOTS:
    void on_saveProjectSuccess(Project &project);

public:
    explicit ProjectEditor(QSharedPointer<QList<QSharedPointer<Project>>> projects, QWidget *parent = 0);
    ~ProjectEditor();

    QPushButton *cancelProjectButton;

    void refreshProjects(QSharedPointer<QList<QSharedPointer<Project>>> projects);

private Q_SLOTS:
    void on_newProjectButton_released();
    void on_delete(QString name);

private:
    Ui::ProjectEditor *ui;

    QListWidget *projectsListWidget;
    QSharedPointer<QList<QMetaObject::Connection>> connections;

    QSharedPointer<QList<QSharedPointer<Project>>> projects;

    void refreshProjectsList();
    void validateAndSave();
};

#endif // PROJECTEDITOR_H
