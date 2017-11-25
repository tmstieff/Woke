#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H

#include "../model/request.h"
#include <QDebug>
#include <QObject>
#include <QSharedPointer>
#include <qdjango/db/QDjangoModel.h>
#include <qdjango/db/QDjangoQuerySet.h>

class HistoryController : public QObject {
    Q_OBJECT

  public:
    HistoryController(QObject *parent = nullptr);

    void addEntry(Request &request);
    QSharedPointer<QList<QSharedPointer<Request>>> getLatest(int limit);
    QSharedPointer<Request> get(int id);

  private:
    QDjangoQuerySet<Request> requests;
};

#endif // HISTORYCONTROLLER_H
