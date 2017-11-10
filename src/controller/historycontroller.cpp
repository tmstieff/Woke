#include "historycontroller.h"

HistoryController::HistoryController(QObject *parent) : QObject(parent) {
}

void HistoryController::addEntry(Request &request) {
    if (QString::compare(request.getName(), QString("")) == 0) {
        auto name = request.getHost() + request.getUri();
        request.setName(name);
    }

    bool saved = request.save();

    qDebug() << "Save request" << request.getName() << saved;
}

QSharedPointer<QList<QSharedPointer<Request>>> HistoryController::getLatest(int limit) {
    QDjangoQuerySet<Request> resultSet = this->requests.orderBy(QStringList("-id")).limit(0, limit);

    auto results = QSharedPointer<QList<QSharedPointer<Request>>>(new QList<QSharedPointer<Request>>());
    for (int i = 0; i < resultSet.size(); i++) {
        auto result = QSharedPointer<Request>(resultSet.at(i));
        results.data()->append(result);
    }

    qDebug() << "Recent results" << results.data()->length();

    return results;
}
