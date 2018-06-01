#include "ui_saveeditor.h"
#include "saveeditor.h"


SaveEditor::SaveEditor(QWidget *parent) : QWidget(parent), ui(new Ui::SaveEditor) {
    ui->setupUi(this);

    this->confirmSaveButton = this->ui->confirmSaveButton;
    this->confirmSaveAsButton = this->ui->confirmSaveAsButton;
    this->cancelSaveButton = this->ui->cancelSaveButton;

    this->projectComboBox = this->ui->projectComboBox;
    this->nameEdit = this->ui->nameEdit;
}

SaveEditor::~SaveEditor() {
    delete ui;
}

void SaveEditor::clearFields() {
    this->projectComboBox->setCurrentIndex(0);
    this->nameEdit->setText("");
}

void SaveEditor::updateFields(Request &request) {
    // Update the save editor with this name and project if already assigned and saved
    if (request.project() != nullptr) {
        this->nameEdit->setText(request.getName());

        auto index = 0;
        for (int i = 0; i < this->projectComboBox->count(); i++) {
            auto projectId = this->projectComboBox->itemData(i).toInt();

            if (projectId == request.project()->pk()) {
                index = i;
                break;
            }
        }

        this->projectComboBox->setCurrentIndex(index);
    }
}

void SaveEditor::refreshProjects(QList<QSharedPointer<Project>> &projects) {
    this->projectComboBox->clear();
    for (int i = 0; i < projects.size(); i++) {
        auto project = projects.at(i).data();

        this->projectComboBox->addItem(project->getName(), QVariant(project->pk()));
    }
}

int SaveEditor::getSelectedProject() {
    return this->projectComboBox->currentData().toInt();
}
