#include "tabbededitor_test.h"

void TabbedEditor_Test::test_setupTabs() {
    QList<QSharedPointer<Ui::TabData>> tabs;

    Ui::TabData tab1Data;
    tab1Data.button = QSharedPointer<QPushButton>::create(new QPushButton());
    tab1Data.name = QString("Tab 1");
    tab1Data.data = QSharedPointer<QString>::create(QString("Tab 1 data"));
    tabs.append(QSharedPointer<Ui::TabData>::create(tab1Data));

    auto tabbedEditor = new TabbedEditor(0, tabs);
}
