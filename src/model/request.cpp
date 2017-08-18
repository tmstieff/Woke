#include "request.h"

Request::Request() {
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

QString Request::getResponseBody() const {
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

const QString &Request::getRequestScript() const {
    return requestScript;
}

void Request::setRequestScript(const QString &requestScript) {
    this->requestScript = requestScript;
}

const QString &Request::getResponseScript() const {
    return responseScript;
}

void Request::setResponseScript(const QString &responseScript) {
    this->responseScript = responseScript;
}

const QString &Request::getResponseContentType() const {
    return responseContentType;
}

void Request::setResponseContentType(const QString &responseContentType) {
    this->responseContentType = responseContentType;
}
