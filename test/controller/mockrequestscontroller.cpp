#include "mockrequestscontroller.h"

MockRequestsController::MockRequestsController()
{
    this->statusCode = 200;
}

QSharedPointer<Request> MockRequestsController::sendRequest(QString &verb, QString &url, QString &headers, QString &body)
{
    QSharedPointer<Request> request = QSharedPointer<Request>(new Request);

    request.data()->setVerb(verb);

    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    request.data()->setProto(segments.proto);
    request.data()->setHost(segments.hostname);
    request.data()->setUri(segments.uri);
    request.data()->setRequestHeaders(headers);
    request.data()->setRequestBody(body);

    return request;
}

ResponseInfo MockRequestsController::handleResponse(QNetworkReply &response)
{
    ResponseInfo responseInfo;

    responseInfo.contentType = "application/json";
    responseInfo.responseTime = 284;
    responseInfo.statusCode = this->statusCode;

    return responseInfo;
}
