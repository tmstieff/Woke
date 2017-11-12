#include "projectcontroller_test.h"

ProjectController_Test::ProjectController_Test() : QObject() {
}

void ProjectController_Test::initTestCase() {
    initDatabase();

    this->projectController = new ProjectController(0);
}

void ProjectController_Test::test_upsertDefaultProject() {
    auto project = this->projectController->upsertDefaultProject();

    QCOMPARE(project.data()->getName(), QString("Default"));
}
