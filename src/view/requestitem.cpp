#include "src/view/requestitem.h"
#include "ui_requestitem.h"

RequestItem::RequestItem(QWidget *parent) : QWidget(parent), ui(new Ui::RequestItem) {
    ui->setupUi(this);

    uriLabel = ui->uriLabel;
    urlLabel = ui->urlLabel;
    verbLabel = ui->verbLabel;
}

RequestItem::~RequestItem() {
    delete ui;
}

void RequestItem::setInformation(QString verb, QString uri, QString url) {
    this->uriLabel->setText(uri);
    this->urlLabel->setText(url);
    this->verbLabel->setText(verb);
}

QString RequestItem::getVerb() {
    return this->verbLabel->text();
}

QString RequestItem::getUri() {
    return this->uriLabel->text();
}

QString RequestItem::getUrl() {
    return this->urlLabel->text();
}
