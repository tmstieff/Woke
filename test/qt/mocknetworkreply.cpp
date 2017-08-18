#include "mocknetworkreply.h"

MockNetworkReply::MockNetworkReply() {
    this->setAttribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute, QVariant(200));
}

qint64 MockNetworkReply::readData(char *data, qint64 maxlen) {
    qDebug() << "readData" << *data;

    qint64 r = QByteArray(this->responseData.toUtf8()).toLongLong();
    return r;
}

void MockNetworkReply::abort() {
}

void MockNetworkReply::setResponseStatus(int status) {
    this->setAttribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute, QVariant(status));
}


