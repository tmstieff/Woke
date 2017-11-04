#include "responsetabbededitor.h"

ResponseTabbedEditor::ResponseTabbedEditor(QWidget *parent) : TabbedEditor(parent) {
    auto headersTabData = QSharedPointer<QString>(new QString(""));
    auto headersTab = QSharedPointer<Ui::TabData>(new Ui::TabData());
    headersTab.data()->name = "Headers";
    headersTab.data()->data = headersTabData;

    auto bodyTabData = QSharedPointer<QString>(new QString());
    auto bodyTab = QSharedPointer<Ui::TabData>(new Ui::TabData());
    bodyTab.data()->name = "Body";
    bodyTab.data()->data = bodyTabData;

    auto postScriptTabData = QSharedPointer<QString>(new QString(""));
    auto postScriptTab = QSharedPointer<Ui::TabData>(new Ui::TabData());
    postScriptTab.data()->name = "Post-Response Script";
    postScriptTab.data()->data = postScriptTabData;

    auto requestTabs = QList<QSharedPointer<Ui::TabData>>();
    requestTabs.append(headersTab);
    requestTabs.append(bodyTab);
    requestTabs.append(postScriptTab);

    this->addTabs(requestTabs);
}

void ResponseTabbedEditor::setHeadersData(QSharedPointer<QString> data) {
    this->setTabData(0, data);
}

void ResponseTabbedEditor::setBodyData(QSharedPointer<QString> data) {
    this->setTabData(1, data);
}

void ResponseTabbedEditor::setPostResponseScriptData(QSharedPointer<QString> data) {
    this->setTabData(2, data);
}

QSharedPointer<QString> ResponseTabbedEditor::getHeaderData() {
    return this->getTabData(0);
}

QSharedPointer<QString> ResponseTabbedEditor::getBodyData() {
    return this->getTabData(1);
}

QSharedPointer<QString> ResponseTabbedEditor::getPostResponseScriptData() {
    return this->getTabData(2);
}
