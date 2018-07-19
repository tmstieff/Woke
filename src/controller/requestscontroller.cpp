#include "requestscontroller.h"

RequestsController::RequestsController(QObject *parent) : QObject(parent) {
    this->networkManager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager);
    this->variableController = QSharedPointer<VariableController>(new VariableController);
}

/**
 * @brief RequestsController::sendRequest
 *
 * Send a network request with an optional body and headers
 *
 * @param verb HTTP request type verb (GET, POST, ...)
 * @param url with protocol and hostname
 * @param headers or empty string
 * @param body if relavant or empty string
 * @return pointer to a fat request model object
 */
QSharedPointer<Request> RequestsController::sendRequest(QString &verb, QString &url, QString &headers, QString &body,
                                                        QString &prerequestScript, bool saveCurrentRequest,
                                                        QSharedPointer<Project> defaultProject, QString &responseScript,
                                                        QSharedPointer<Request> existingRequest) {
    QSharedPointer<Request> currentRequest;
    if (!existingRequest.isNull()) {
        currentRequest = existingRequest;
    } else {
        currentRequest = QSharedPointer<Request>::create();
    }

    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QNetworkRequest request(url);
    HttpVerb verbEnum = UrlUtil::safeParseVerb(verb);

    currentRequest.data()->setProto(segments.proto);
    currentRequest.data()->setHost(segments.hostname);
    currentRequest.data()->setUri(segments.uri);
    currentRequest.data()->setVerb(HttpVerbStrings[verbEnum]);
    currentRequest.data()->setRequestHeaders(headers);
    currentRequest.data()->setRequestBody(body);
    currentRequest.data()->setRequestScript(prerequestScript);
    currentRequest.data()->setResponseScript(responseScript);

    currentRequest.data()->save();

    if (currentRequest.data()->project() != nullptr) {
        CurrentDataController::setCurrentProjectId(currentRequest.data()->project()->pk().toInt());
    }
    CurrentDataController::setCurrentRequestId(currentRequest.data()->pk().toInt());

    this->pythonScriptController.executeScript(prerequestScript, currentRequest);

    QString bodyCopy = QString(body.data());
    this->variableController.data()->replaceVariables(bodyCopy, CurrentDataController::getCurrentProjectId(),
                                                      CurrentDataController::getCurrentRequestId());

    QString headersCopy = QString(headers.data());
    this->variableController.data()->replaceVariables(headersCopy, CurrentDataController::getCurrentProjectId(),
                                                      CurrentDataController::getCurrentRequestId());

    UrlUtil::setHeadersFromStringBlob(headersCopy, request);

    this->responseTimer.start();

    switch (verbEnum) {
    case HttpVerb::GET:
        this->networkManager.data()->get(request);
        break;
    case HttpVerb::POST:
        this->networkManager.data()->post(request, bodyCopy.toUtf8());
        break;
    case HttpVerb::PUT:
        this->networkManager.data()->put(request, bodyCopy.toUtf8());
        break;
    case HttpVerb::PATCH:
        this->networkManager.data()->put(request, bodyCopy.toUtf8());
        break;
    case HttpVerb::DELETE:
        this->networkManager.data()->deleteResource(request);
        break;
    case HttpVerb::HEAD:
        this->networkManager.data()->head(request);
        break;
    case HttpVerb::OPTIONS:
        this->networkManager.data()->get(request);
        break;
    case HttpVerb::CONNECT:
        this->networkManager.data()->get(request);
        break;
    default:
        break;
    }

    return currentRequest;
}

/**
 * @brief RequestsController::handleResponse
 *
 * Parse any relavant response information from the QNetworkReply
 *
 * @param response
 * @return response info struct
 */
ResponseInfo RequestsController::handleResponse(QNetworkReply &response) {
    int responseTime = this->responseTimer.elapsed();

    auto statusCode = response.attribute(QNetworkRequest::HttpStatusCodeAttribute);
    auto statusCodeInt = statusCode.toInt();

    QString contentType("");
    auto contentTypeVar = response.header(QNetworkRequest::KnownHeaders::ContentTypeHeader);
    if (contentTypeVar.canConvert(QVariant::String)) {
        contentType = contentTypeVar.toString();
    }

    qDebug() << contentType;

    ResponseInfo responseInfo;
    responseInfo.responseTime = responseTime;
    responseInfo.statusCode = statusCodeInt;
    responseInfo.contentType = contentType;

    return responseInfo;
}
