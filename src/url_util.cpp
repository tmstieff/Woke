#include "url_util.h"

UrlSegments UrlUtil::safeSplitUrl(QUrl url) {
    return UrlUtil::safeSplitUrl(url.toString());
}

UrlSegments UrlUtil::safeSplitUrl(QString &url) {
    UrlSegments segments = UrlSegments();

    if (url == nullptr) {
        segments.proto = QString("");
        segments.hostname = QString("");
        segments.uri = QString("");

        return segments;
    }

    if (url.length() <= 6) {
        segments.proto = QString(url);
        segments.hostname = QString("");
        segments.uri = QString("");
    }

    auto urlClone = QString(url);
    size_t protoIndex = urlClone.indexOf(':');

    // http:// or https://
    QString proto = urlClone.left(protoIndex + 3);

    // localhost/u/r/i
    QString urlNoProto = QString(urlClone.mid(protoIndex + 3));

    size_t startUriIndex = urlNoProto.indexOf('/');
    QString hostname = urlNoProto.left(startUriIndex);

    // /u/r/i
    QString uri = QString(urlNoProto.mid(startUriIndex));

    // http://localhost
    QString host = QString(proto + hostname);

    segments.proto = proto;
    segments.hostname = hostname;
    segments.uri = uri;

    return segments;
}
