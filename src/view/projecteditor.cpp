#include "src/view/projecteditor.h"
#include "ui_projecteditor.h"

ProjectEditor::ProjectEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectEditor)
{
    ui->setupUi(this);
}

ProjectEditor::~ProjectEditor()
{
    delete ui;
}
