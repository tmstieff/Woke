#include "testutils.h"

void initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        Q_ASSERT(false);
    }

    QDjango::setDatabase(db);
    QDjango::registerModel<Project>();
    QDjango::registerModel<Request>();
    QDjango::registerModel<Variable>();
    QDjango::createTables();
}

TestUtils::TestUtils() {
}
