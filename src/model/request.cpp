#include "request.h"

Request::Request(QObject *parent) : QDjangoModel(parent) {
    setForeignKey("project", new Project(this));
}

QString Request::getHost() const {
    return host;
}

void Request::setHost(const QString &host) {
    this->host = host;
}

QString Request::getProto() const {
    return proto;
}

void Request::setProto(const QString &proto) {
    this->proto = proto;
}

QString Request::getUri() const {
    return uri;
}

void Request::setUri(const QString &value) {
    uri = value;
}

QString Request::getStatusCode() const {
    return statusCode;
}

void Request::setStatusCode(const QString &value) {
    statusCode = value;
}

int Request::getTime() const {
    return time;
}

void Request::setTime(int value) {
    time = value;
}

QString Request::getRequestHeaders() const {
    return requestHeaders;
}

void Request::setRequestHeaders(const QString &value) {
    requestHeaders = value;
}

QString Request::getRequestBody() const {
    return requestBody;
}

void Request::setRequestBody(const QString &value) {
    requestBody = value;
}

QString Request::getVerb() const {
    return verb;
}

void Request::setVerb(const QString &value) {
    verb = value;
}

QString Request::getResponseHeaders() const {
    return responseHeaders;
}

void Request::setResponseHeaders(const QString &value) {
    responseHeaders = value;
}

const QString Request::getResponseBody() const {
    return responseBody;
}

void Request::setResponseBody(const QString &value) {
    responseBody = value;
}

QString Request::getName() const {
    return this->name;
}

void Request::setName(const QString &name) {
    this->name = name;
}

const QString Request::getRequestScript() const {
    return requestScript;
}

void Request::setRequestScript(const QString &requestScript) {
    this->requestScript = requestScript;
}

const QString Request::getResponseScript() const {
    return responseScript;
}

void Request::setResponseScript(const QString &responseScript) {
    this->responseScript = responseScript;
}

const QString Request::getResponseContentType() const {
    return responseContentType;
}

void Request::setResponseContentType(const QString &responseContentType) {
    this->responseContentType = responseContentType;
}

Project *Request::project() const {
    return qobject_cast<Project *>(foreignKey("project"));
}

void Request::setProject(Project *project) {
    setForeignKey("project", project);
}

QSharedPointer<Request> Request::clone() {
    QSharedPointer<Request> clone = QSharedPointer<Request>(new Request);

    clone.data()->setName(QString(this->getName().toUtf8()));
    clone.data()->setProto(QString(this->getProto().toUtf8()));
    clone.data()->setUri(QString(this->getUri().toUtf8()));
    clone.data()->setVerb(QString(this->getVerb().toUtf8()));
    clone.data()->setHost(QString(this->getHost().toUtf8()));
    clone.data()->setRequestBody(QString(this->getRequestBody().toUtf8()));
    clone.data()->setRequestHeaders(QString(this->getRequestHeaders().toUtf8()));
    clone.data()->setRequestScript(QString(this->getRequestScript().toUtf8()));
    clone.data()->setResponseScript(QString(this->getResponseScript().toUtf8()));
    clone.data()->setResponseBody(QString(this->getResponseBody().toUtf8()));
    clone.data()->setResponseHeaders(QString(this->getResponseHeaders().toUtf8()));
    clone.data()->setStatusCode(QString(this->getStatusCode().toUtf8()));
    clone.data()->setTime(this->getTime());
    clone.data()->setProperty("project_id", QVariant());

    return clone;
}

Q_DECLARE_METATYPE(Request *)
