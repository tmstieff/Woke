#include "src/view/projecteditor.h"
#include "ui_projecteditor.h"

ProjectEditor::ProjectEditor(QList<QSharedPointer<Project>> &projects, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectEditor)
{
    ui->setupUi(this);

    this->cancelProjectButton = ui->cancelProjectButton;

    this->projects = projects;
}

ProjectEditor::~ProjectEditor()
{
    delete ui;
}
