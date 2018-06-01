#include "model/project.h"
#include "model/request.h"
#include "model/variable.h"
#include "view/mainwindow.h"
#include <cmath>
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
    }

    QDjango::setDatabase(db);
    QDjango::registerModel<Project>();
    QDjango::registerModel<Request>();
    QDjango::registerModel<Variable>();
    QDjango::createTables();

    QDjango::setDebugEnabled(false);

    MainWindow w;
    w.show();

    return a.exec();
}
