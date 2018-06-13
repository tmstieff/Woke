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
}

ProjectEditor::~ProjectEditor() {
    delete ui;
}

void ProjectEditor::refreshProjects(QSharedPointer<QList<QSharedPointer<Project>>> projects) {
    this->projects = projects;
    this->refreshProjectsList();
}

void ProjectEditor::refreshProjectsList() {
    this->projectsListWidget->clear();

    for (const auto &i : *this->projects.data()) {
        auto *item = new QListWidgetItem(this->projectsListWidget);

        auto *projectItem = new ProjectItem(this);
        item->setSizeHint(projectItem->sizeHint());

        projectItem->setInformation(i.data()->getName());
        this->projectsListWidget->setItemWidget(item, projectItem);
    }
}

void ProjectEditor::on_saveProjectSuccess(Project &project) {

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
