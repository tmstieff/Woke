#ifndef URL_UTIL_H
#define URL_UTIL_H

#include <QNetworkRequest>
#include <QString>
#include <QUrl>

enum HttpVerb { CONNECT, HEAD, OPTIONS, GET, PUT, POST, PATCH, DELETE };

static const char *const HttpVerbStrings[] = {"CONNECT", "HEAD", "OPTIONS", "GET", "PUT", "POST", "PATCH", "DELETE"};

struct UrlSegments {
    QString proto;
    QString hostname;
    QString uri;
};

class UrlUtil {
  public:
    UrlUtil();
    static UrlSegments safeSplitUrl(QUrl &url);
    static UrlSegments safeSplitUrl(QString &url);
    static HttpVerb safeParseVerb(QString &verb);
    static void setHeadersFromStringBlob(const QString &rawHeaders, QNetworkRequest &request);
};

#endif // URL_UTIL_H
