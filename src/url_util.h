#ifndef URL_UTIL_H
#define URL_UTIL_H

#include <QString>
#include <QUrl>

struct UrlSegments {
    QString proto;
    QString hostname;
    QString uri;
};

class UrlUtil
{
public:
    UrlUtil();
    static UrlSegments safeSplitUrl(QUrl url);
    static UrlSegments safeSplitUrl(QString &url);
};

#endif // URL_UTIL_H
