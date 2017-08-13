#include "urlutil.h"

UrlSegments UrlUtil::safeSplitUrl(QUrl &url) {
    auto urlStr = url.toString();

    return UrlUtil::safeSplitUrl(urlStr);
}

/**
 * @brief UrlUtil::safeSplitUrl
 *
 * Split a string into its component URL segments
 *
 * @param url
 * @return segments struct
 */
UrlSegments UrlUtil::safeSplitUrl(QString &url) {
    UrlSegments segments;

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
    QString urlNoProto(urlClone.mid(protoIndex + 3));

    size_t startUriIndex = urlNoProto.indexOf('/');
    QString hostname(urlNoProto.left(startUriIndex));

    // /u/r/i
    QString uri(urlNoProto.mid(startUriIndex));

    // http://localhost
    QString host(proto + hostname);

    segments.proto = proto;
    segments.hostname = hostname;
    segments.uri = uri;

    return segments;
}

/**
 * @brief UrlUtil::safeParseVerb
 * @param verb Potentially null or mispelled verb to parse
 * @return HttpVerb enum
 */
HttpVerb UrlUtil::safeParseVerb(QString &verb) {
    if (verb != nullptr) {
        // Compare returns 0 for equal strings
        if (QString::compare(verb, QString("POST"), Qt::CaseInsensitive) == 0) {
            return HttpVerb::POST;
        } else if (QString::compare(verb, QString("PATCH"), Qt::CaseInsensitive) == 0) {
            return HttpVerb::PATCH;
        } else  if (QString::compare(verb, QString("PUT"), Qt::CaseInsensitive) == 0) {
            return HttpVerb::PUT;
        } else  if (QString::compare(verb, QString("DELETE"), Qt::CaseInsensitive) == 0) {
            return HttpVerb::DELETE;
        } else  if (QString::compare(verb, QString("OPTIONS"), Qt::CaseInsensitive) == 0) {
            return HttpVerb::OPTIONS;
        } else  if (QString::compare(verb, QString("CONNECT"), Qt::CaseInsensitive) == 0) {
            return HttpVerb::CONNECT;
        } else  if (QString::compare(verb, QString("HEAD"), Qt::CaseInsensitive) == 0) {
            return HttpVerb::HEAD;
        }
    }

    return HttpVerb::GET;
}

/**
 * @brief UrlUtil::setHeadersFromStringBlob
 * @param rawHeaders blob header string
 * @param request to set headers on
 */
void UrlUtil::setHeadersFromStringBlob(QString &rawHeaders, QNetworkRequest &request) {
    if (rawHeaders != nullptr) {
        auto headers = rawHeaders.split('\n');
        for (int i = 0; i < headers.length(); i++) {
            QString header = headers.at(i);
            QStringList pieces = header.split(':');

            QString key("");
            QString value("");
            for (int j = 0; j < pieces.length(); j++) {
                if (j == 0) {
                    key = pieces.at(j);
                } else {
                    value = value.append(pieces.at(j));
                }
            }

            request.setRawHeader(key.toUtf8(), value.toUtf8());
        }
    }
}
