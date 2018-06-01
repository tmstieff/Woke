#include "projectitem.h"
#include "ui_projectitem.h"

ProjectItem::ProjectItem(QWidget *parent) : QWidget(parent), ui(new Ui::ProjectItem) {
    ui->setupUi(this);

    this->nameLabel = ui->nameLabel;
}

ProjectItem::~ProjectItem() {
    delete ui;
}

void ProjectItem::setInformation(QString name) {
    this->nameLabel->setText(name);
}

QString ProjectItem::getName() {
    return this->nameLabel->text();
}
