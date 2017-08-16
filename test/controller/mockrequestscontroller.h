#ifndef MOCKREQUESTSCONTROLLER_H
#define MOCKREQUESTSCONTROLLER_H

#include "../qt/mocknetworkreply.h"
#include "../../src/controller/requestscontroller.h"
#include "../../src/urlutil.h"

class MockRequestsController : public RequestsController
{
public:
    MockRequestsController();

    int statusCode;

    // RequestsController interface
public:
    QSharedPointer<Request> sendRequest(QString &verb, QString &url, QString &headers, QString &body);
    ResponseInfo handleResponse(QNetworkReply &response);
};

#endif // MOCKREQUESTSCONTROLLER_H
