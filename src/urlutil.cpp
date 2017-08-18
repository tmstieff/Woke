#include "urlutil.h"


UrlSegments UrlUtil::safeSplitUrl(const QUrl &url) {
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
UrlSegments UrlUtil::safeSplitUrl(const QString &url) {
    UrlSegments segments;

    if (url == QString::null) {
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
    int protoIndex = urlClone.indexOf(':');

    // http:// or https://
    QString proto = urlClone.left(protoIndex + 3);

    // localhost/u/r/i
    QString urlNoProto(urlClone.mid(protoIndex + 3));

    int startUriIndex = urlNoProto.indexOf('/');
    QString hostname(urlNoProto.left(startUriIndex));

    // /u/r/i
    QString uri;

    // Check in case there was ending slash included
    if (startUriIndex > 0) {
        uri = QString(urlNoProto.mid(startUriIndex));
    } else {
        uri = "/";
    }

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
HttpVerb UrlUtil::safeParseVerb(const QString &verb) {
    auto parsedVerb = HttpVerb::GET;

    // Compare returns 0 for equal strings
    if (QString::compare(verb, QString("POST"), Qt::CaseInsensitive) == 0) {
        parsedVerb = HttpVerb::POST;
    } else if (QString::compare(verb, QString("PATCH"), Qt::CaseInsensitive) == 0) {
        parsedVerb = HttpVerb::PATCH;
    } else if (QString::compare(verb, QString("PUT"), Qt::CaseInsensitive) == 0) {
        parsedVerb = HttpVerb::PUT;
    } else if (QString::compare(verb, QString("DELETE"), Qt::CaseInsensitive) == 0) {
        parsedVerb = HttpVerb::DELETE;
    } else if (QString::compare(verb, QString("OPTIONS"), Qt::CaseInsensitive) == 0) {
        parsedVerb = HttpVerb::OPTIONS;
    } else if (QString::compare(verb, QString("CONNECT"), Qt::CaseInsensitive) == 0) {
        parsedVerb = HttpVerb::CONNECT;
    } else if (QString::compare(verb, QString("HEAD"), Qt::CaseInsensitive) == 0) {
        parsedVerb = HttpVerb::HEAD;
    }

    return parsedVerb;
}

/**
 * @brief UrlUtil::setHeadersFromStringBlob
 * @param rawHeaders blob header string
 * @param request to set headers on
 */
void UrlUtil::setHeadersFromStringBlob(const QString &rawHeaders, QNetworkRequest &request) {
    if (rawHeaders != nullptr) {
        auto headers = rawHeaders.split('\n');
        for (int i = 0; i < headers.length(); i++) {
            const QString &header = headers.at(i);
            const QStringList pieces = header.split(':');

            QString key("");
            QString value("");
            for (int j = 0; j < pieces.length(); j++) {
                if (j == 0) {
                    key = pieces.at(j);
                } else if (j >= 2) {
                    // Make sure to add back the colon
                    value = value.append(":").append(pieces.at(j));
                } else {
                    value = value.append(pieces.at(j));
                }
            }

            request.setRawHeader(key.toUtf8(), value.trimmed().toUtf8());
        }
    }
}
