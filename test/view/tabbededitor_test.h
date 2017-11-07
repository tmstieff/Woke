#ifndef TABBEDEDITOR_TEST_H
#define TABBEDEDITOR_TEST_H

#include "../../src/view/tabbededitor.h"
#include <QObject>
#include <QPushButton>
#include <QSharedPointer>

class TabbedEditor_Test : public QObject {
    Q_OBJECT

  public:
    TabbedEditor_Test();

  private:
    TabbedEditor editor;

  private slots:
    void test_setupTabs();
};

#endif // TABBEDEDITOR_TEST_H
