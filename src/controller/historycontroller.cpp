#include "historycontroller.h"

HistoryController::HistoryController(QObject *parent) : QObject(parent) {
}

void HistoryController::addEntry(Request &request) {
    // Copy all fields by project and ID
    auto clone = request.clone();

    if (QString::compare(request.getName(), QString("")) == 0) {
        auto name = request.getHost() + request.getUri();
        request.setName(name);
    }

    bool saved = clone.data()->save();

    qDebug() << "Save request" << request.getName() << saved;
}

QSharedPointer<QList<QSharedPointer<Request>>> HistoryController::getLatest(int limit) {
    QDjangoQuerySet<Request> resultSet = this->requests.filter(QDjangoWhere("project_id", QDjangoWhere::IsNull, true)).orderBy(QStringList("-id")).limit(0, limit);

    auto results = QSharedPointer<QList<QSharedPointer<Request>>>(new QList<QSharedPointer<Request>>());
    for (int i = 0; i < resultSet.size(); i++) {
        auto result = QSharedPointer<Request>(resultSet.at(i));
        results.data()->append(result);
    }

    qDebug() << "Recent results" << results.data()->length();

    return results;
}

QSharedPointer<Request> HistoryController::get(int id) {
    return QSharedPointer<Request>(this->requests.selectRelated().get(QDjangoWhere("id", QDjangoWhere::Equals, id)));
}
