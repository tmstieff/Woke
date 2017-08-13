#ifndef URL_UTIL_H
#define URL_UTIL_H

#include <QString>
#include <QUrl>
#include <QNetworkRequest>

enum HttpVerb {
    CONNECT,
    HEAD,
    OPTIONS,
    GET,
    PUT,
    POST,
    PATCH,
    DELETE
};

static const char * HttpVerbStrings[] = {
    "CONNECT",
    "HEAD",
    "OPTIONS",
    "GET",
    "PUT",
    "POST",
    "PATCH",
    "DELETE"
};

struct UrlSegments {
    QString proto;
    QString hostname;
    QString uri;
};

class UrlUtil
{
public:
    UrlUtil();
    static UrlSegments safeSplitUrl(QUrl &url);
    static UrlSegments safeSplitUrl(QString &url);
    static HttpVerb safeParseVerb(QString &verb);
    static void setHeadersFromStringBlob(QString &rawHeaders, QNetworkRequest &request);
};

#endif // URL_UTIL_H
