#include "responsetabbededitor.h"

ResponseTabbedEditor::ResponseTabbedEditor(QWidget *parent) : TabbedEditor(parent) {
    auto headersTabData = QSharedPointer<QString>(new QString(""));
    auto headersTab = QSharedPointer<Ui::TabData>(new Ui::TabData());
    headersTab.data()->name = "Headers";
    headersTab.data()->data = headersTabData;
    headersTab.data()->syntaxHighlighter = QSharedPointer<QSyntaxHighlighter>(new HeaderSyntaxHighlighter);

    auto bodyTabData = QSharedPointer<QString>(new QString());
    auto bodyTab = QSharedPointer<Ui::TabData>(new Ui::TabData());
    auto bodySyntaxHighlighter = QSharedPointer<JsonSyntaxHighlighter>(new JsonSyntaxHighlighter);
    bodyTab.data()->name = "Body";
    bodyTab.data()->data = bodyTabData;
    bodyTab.data()->syntaxHighlighter = bodySyntaxHighlighter;

    auto postScriptTabData = QSharedPointer<QString>(new QString(""));
    auto postScriptTab = QSharedPointer<Ui::TabData>(new Ui::TabData());
    postScriptTab.data()->name = "Post-Response Script";
    postScriptTab.data()->data = postScriptTabData;
    postScriptTab.data()->syntaxHighlighter = QSharedPointer<QSyntaxHighlighter>(new KickPythonSyntaxHighlighter);

    auto requestTabs = QList<QSharedPointer<Ui::TabData>>();
    requestTabs.append(headersTab);
    requestTabs.append(bodyTab);
    requestTabs.append(postScriptTab);

    this->addTabs(requestTabs);
}

void ResponseTabbedEditor::resetTabData() {
    // Don't reset the last tab (script tab)
    for (int i = 0; i < this->tabs.length() - 1; i++) {
        this->tabs.at(i).data()->data = QSharedPointer<QString>(new QString(""));
    }
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
