#ifndef PROJECTCONTROLLER_TEST_H
#define PROJECTCONTROLLER_TEST_H

#include "../../src/controller/projectcontroller.h"
#include "../testutils.h"
#include <QObject>
#include <QTest>

class ProjectController_Test : public QObject {
  public:
    ProjectController_Test();

  private:
    ProjectController *projectController;

  private slots:
    void initTestCase();
    void test_upsertDefaultProject();
};

#endif // PROJECTCONTROLLER_TEST_H
