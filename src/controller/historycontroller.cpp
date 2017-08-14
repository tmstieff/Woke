#include "historycontroller.h"

HistoryController::HistoryController() {
}

void HistoryController::addEntry(Request &request) {
    bool saved = request.save();

    qDebug() << "Save request" << request.getUri() << saved;
}

QSharedPointer<QList<QSharedPointer<Request>>> HistoryController::getLatest(int limit) {
    QDjangoQuerySet<Request> resultSet = this->requests.orderBy(QStringList("-id")).limit(0, limit);

    // We specifically want a pointer returned because some of these results can be MBs in size
    // due to having both a response and request body present
    auto results = QSharedPointer<QList<QSharedPointer<Request>>>(new QList<QSharedPointer<Request>>());
    for (int i = 0; i < resultSet.size(); i++) {
        auto result = QSharedPointer<Request>(resultSet.at(i));
        results.data()->append(result);
    }

    qDebug() << "Recent results" << results.data()->length();

    return results;
}
