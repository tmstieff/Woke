#ifndef REQUESTSCONTROLLER_H
#define REQUESTSCONTROLLER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSharedPointer>
#include <QElapsedTimer>

#include "../model/request.h"
#include "../urlutil.h"

struct ResponseInfo {
    int responseTime;
    int statusCode;
    QString contentType;
};

class RequestsController
{
public:
    RequestsController();

    QSharedPointer<QNetworkAccessManager> networkManager;

    virtual QSharedPointer<Request> sendRequest(QString &verb, QString &url, QString &headers, QString &body);
    virtual ResponseInfo handleResponse(QNetworkReply &response);

private:
    QElapsedTimer responseTimer;
};

#endif // REQUESTSCONTROLLER_H
