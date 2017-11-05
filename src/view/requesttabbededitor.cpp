#include "requesttabbededitor.h"

RequestTabbedEditor::RequestTabbedEditor(QWidget *parent) : TabbedEditor(parent) {
    auto headersTabData = QSharedPointer<QString>(new QString(""));
    auto headersTab = QSharedPointer<Ui::TabData>(new Ui::TabData());
    headersTab.data()->name = "Headers";
    headersTab.data()->data = headersTabData;
    headersTab.data()->syntaxHighlighter = QSharedPointer<QSyntaxHighlighter>(new HeaderSyntaxHighlighter);

    auto preScriptTabData = QSharedPointer<QString>(new QString(""));
    auto preScriptTab = QSharedPointer<Ui::TabData>(new Ui::TabData());
    preScriptTab.data()->name = "Pre-Request Script";
    preScriptTab.data()->data = preScriptTabData;

    auto requestTabs = QList<QSharedPointer<Ui::TabData>>();
    requestTabs.append(headersTab);
    requestTabs.append(preScriptTab);

    this->addTabs(requestTabs);
}

void RequestTabbedEditor::setHeadersData(QSharedPointer<QString> data) {
    this->setTabData(0, data);
}

void RequestTabbedEditor::setPreRequestScriptData(QSharedPointer<QString> data) {
    this->setTabData(1, data);
}

QSharedPointer<QString> RequestTabbedEditor::getHeaderData() {
    return this->getTabData(0);
}

QSharedPointer<QString> RequestTabbedEditor::getPreRequestScriptData() {
    return this->getTabData(1);
}
