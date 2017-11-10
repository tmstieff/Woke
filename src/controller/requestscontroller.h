#ifndef REQUESTSCONTROLLER_H
#define REQUESTSCONTROLLER_H

#include <QElapsedTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QSharedPointer>

#include "../model/request.h"
#include "../urlutil.h"

struct ResponseInfo {
    int responseTime;
    int statusCode;
    QString contentType;
};

class RequestsController : public QObject {
  public:
    RequestsController(QObject *parent = 0);

    QSharedPointer<QNetworkAccessManager> networkManager;

    virtual QSharedPointer<Request> sendRequest(QString &verb, QString &url, QString &headers, QString &body);
    virtual ResponseInfo handleResponse(QNetworkReply &response);

  private:
    QElapsedTimer responseTimer;
};

#endif // REQUESTSCONTROLLER_H
