#include "projecteditor.h"
#include "ui_projecteditor.h"

ProjectEditor::ProjectEditor(QSharedPointer<QList<QSharedPointer<Project>>> projects, QWidget *parent) : QWidget(parent),
    ui(new Ui::ProjectEditor) {

    ui->setupUi(this);

    this->projectsListWidget = this->ui->projectsList;
    this->cancelProjectButton = ui->cancelProjectButton;

    if (projects.data() != NULL) {
        this->refreshProjects(projects);
    }

    this->connections = QSharedPointer<QList<QMetaObject::Connection>>::create();
}

ProjectEditor::~ProjectEditor() {
    delete ui;
}

/**
 * @brief ProjectEditor::refreshProjects
 *
 * Update the model containing the list of projects and then sync the UI with the new list
 *
 * @param projects - List of projects to display
 */
void ProjectEditor::refreshProjects(QSharedPointer<QList<QSharedPointer<Project>>> projects) {
    this->projects = projects;
    this->refreshProjectsList();
}

void ProjectEditor::refreshProjectsList() { 
    /*for (const auto &i : *this->connections.data()) {
        QObject::disconnect(i);
    }*/

    this->connections.clear();
    this->projectsListWidget->clear();

    for (const auto &i : *this->projects.data()) {
        auto *item = new QListWidgetItem(this->projectsListWidget);

        auto *projectItem = new ProjectItem(this);
        projectItem->setInformation(i.data()->getName());

        item->setSizeHint(projectItem->sizeHint());

        this->projectsListWidget->setItemWidget(item, projectItem);

        QObject::connect(projectItem, &ProjectItem::event_delete,
                         [=]() { this->on_delete(i.data()->getName()); });
    }
}

void ProjectEditor::on_saveProjectSuccess(Project &project) {
    (void) project;
}

void ProjectEditor::validateAndSave() {
    QString name = this->ui->nameEdit->text();
    if (name.trimmed().length() == 0) {
        return;
    }

    Project project;
    project.setName(name.trimmed());

    Q_EMIT event_saveProject(project);
}

void ProjectEditor::on_newProjectButton_released() {
    this->validateAndSave();
}

void ProjectEditor::on_delete(QString name) {
    Q_EMIT event_deleteProject(name);
}
