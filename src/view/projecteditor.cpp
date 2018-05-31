#include "src/view/projecteditor.h"
#include "ui_projecteditor.h"

ProjectEditor::ProjectEditor(QList<QSharedPointer<Project>> &projects, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectEditor)
{
    ui->setupUi(this);

    this->projectsTableView = this->ui->projectsTable;
    this->cancelProjectButton = ui->cancelProjectButton;

    this->projects = projects;

    QStandardItemModel *projectsTableModel = new QStandardItemModel(2, this->projects.length(), this);
    for (int row = 0; row < this->projects.length(); row++) {
        QStandardItem *name = new QStandardItem(this->projects.at(row).data()->getName());
        projectsTableModel->setItem(row, 0, name);

        QStandardItem *actions = new QStandardItem("X");
        projectsTableModel->setItem(row, 1, actions);
    }


    this->projectsTableView->setModel(projectsTableModel);
}

ProjectEditor::~ProjectEditor()
{
    delete ui;
}
