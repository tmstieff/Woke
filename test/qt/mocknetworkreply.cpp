#include "mocknetworkreply.h"

MockNetworkReply::MockNetworkReply() {
    this->setAttribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute, QVariant(200));
}

qint64 MockNetworkReply::readData(char *data, qint64 maxlen) {
    qint64 r = 1;
    return r;
}

void MockNetworkReply::abort() {
}
