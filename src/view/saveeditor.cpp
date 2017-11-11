#include "src/view/saveeditor.h"
#include "ui_saveeditor.h"

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
    this->projectComboBox->setCurrentIndex(-1);
    this->nameEdit->setText("");
}
