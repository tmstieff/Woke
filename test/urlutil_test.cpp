#include "urlutil_test.h"

void UrlUtil_Test::testHttpSplit() {
    QString url = "http://www.google.com";
    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QCOMPARE(segments.proto, QString("http://"));
    QCOMPARE(segments.hostname, QString("www.google.com"));
    QCOMPARE(segments.uri, QString("/"));
}

void UrlUtil_Test::testHttpsSplit() {
    QString url = "https://www.google.com";
    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QCOMPARE(segments.proto, QString("https://"));
    QCOMPARE(segments.hostname, QString("www.google.com"));
    QCOMPARE(segments.uri, QString("/"));
}

void UrlUtil_Test::testWithUri() {
    QString url = "https://api.github.com/users/1076/name/test";
    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QCOMPARE(segments.proto, QString("https://"));
    QCOMPARE(segments.hostname, QString("api.github.com"));
    QCOMPARE(segments.uri, QString("/users/1076/name/test"));
}

void UrlUtil_Test::testNulls() {
    QString url;
    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QCOMPARE(segments.proto, QString(""));
    QCOMPARE(segments.hostname, QString(""));
    QCOMPARE(segments.uri, QString(""));
}
