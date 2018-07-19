#include "projecteditor.h"
#include "ui_projecteditor.h"

ProjectEditor::ProjectEditor(QSharedPointer<QList<QSharedPointer<Project>>> projects, QWidget *parent) : QWidget(parent),
    ui(new Ui::ProjectEditor) {

    ui->setupUi(this);

    this->projectsListWidget = this->ui->projectsList;
    this->cancelProjectButton = ui->cancelProjectButton;

    this->projectController = new ProjectController(this);

    if (projects.data() != NULL) {
        this->refreshProjects(projects);
    }

    this->connections = QSharedPointer<QList<QMetaObject::Connection>>::create();

    this->ui->editMessage->hide();
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
    if (!this->connections.isNull()) {
        for (const auto &i : *this->connections.data()) {
            QObject::disconnect(i);
        }
    }

    this->connections.data()->clear();
    this->projectsListWidget->clear();

    for (const auto &i : *this->projects.data()) {
        auto *item = new QListWidgetItem(this->projectsListWidget);

        auto *projectItem = new ProjectItem(this);
        projectItem->setInformation(i.data()->getName());

        item->setSizeHint(projectItem->sizeHint());

        this->projectsListWidget->setItemWidget(item, projectItem);

        auto conn = QObject::connect(projectItem, &ProjectItem::event_delete,
                         [=]() { this->on_delete(i.data()->getName()); });

        this->connections.data()->append(conn);
    }
}

void ProjectEditor::on_saveProjectSuccess(Project &project) {
    (void) project;
}

void ProjectEditor::validateAndSave() {
    QString name = this->ui->nameEdit->text();
    if (name.trimmed().length() == 0) {
        this->ui->editMessage->setText("Invalid project name.");
        this->ui->editMessage->show();
    } else {

        Project project;
        project.setName(name.trimmed());

        auto existingProject = projectController->getProject(project.getName());
        if (existingProject.isNull()) {
            Q_EMIT event_saveProject(project);
        } else {
            this->ui->editMessage->setText("This project already exists.");
            this->ui->editMessage->show();
        }
    }
}

void ProjectEditor::on_newProjectButton_released() {
    this->validateAndSave();
}

void ProjectEditor::on_delete(QString name) {
    Q_EMIT event_deleteProject(name);
}
