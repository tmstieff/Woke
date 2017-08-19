#include "urleditor.h"
#include "ui_urleditor.h"

UrlEditor::UrlEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UrlEditor)
{
    ui->setupUi(this);
}

UrlEditor::~UrlEditor()
{
    delete ui;
}
