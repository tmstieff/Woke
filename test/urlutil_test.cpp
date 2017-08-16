#include "urlutil_test.h"

void UrlUtil_Test::test_httpSplit() {
    QString url = "http://www.google.com";
    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QCOMPARE(segments.proto, QString("http://"));
    QCOMPARE(segments.hostname, QString("www.google.com"));
    QCOMPARE(segments.uri, QString("/"));
}

void UrlUtil_Test::test_httpsSplit() {
    QString url = "https://www.google.com";
    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QCOMPARE(segments.proto, QString("https://"));
    QCOMPARE(segments.hostname, QString("www.google.com"));
    QCOMPARE(segments.uri, QString("/"));
}

void UrlUtil_Test::test_httpSplit_WithUri() {
    QString url = "https://api.github.com/users/1076/name/test";
    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QCOMPARE(segments.proto, QString("https://"));
    QCOMPARE(segments.hostname, QString("api.github.com"));
    QCOMPARE(segments.uri, QString("/users/1076/name/test"));
}

void UrlUtil_Test::test_httpSplit_Null() {
    QString url;
    UrlSegments segments = UrlUtil::safeSplitUrl(url);

    QCOMPARE(segments.proto, QString(""));
    QCOMPARE(segments.hostname, QString(""));
    QCOMPARE(segments.uri, QString(""));
}

void UrlUtil_Test::test_setHeadersFromStringBlob_Single() {
    QString rawHeaders("Content-Type: test-application");

    QNetworkRequest mockRequest;

    UrlUtil::setHeadersFromStringBlob(rawHeaders, mockRequest);

    QString headerName("Content-Type");
    QCOMPARE(QString(mockRequest.rawHeader(headerName.toUtf8())), QString("test-application"));
}

void UrlUtil_Test::test_setHeadersFromStringBlob_Multi() {
    QString rawHeaders("Content-Type: test-application\nAuth: thisIs-an:auth_token");

    QNetworkRequest mockRequest;

    UrlUtil::setHeadersFromStringBlob(rawHeaders, mockRequest);

    QString headerName("Content-Type");
    QCOMPARE(QString(mockRequest.rawHeader(headerName.toUtf8())), QString("test-application"));

    headerName = "Auth";
    QCOMPARE(QString(mockRequest.rawHeader(headerName.toUtf8())), QString("thisIs-an:auth_token"));
}

void UrlUtil_Test::test_setHeadersFromStringBlob_Malformed() {
    QString rawHeaders("Content-Type: test-application\nAuth: thisIs-an:auth_token\nIncomplete-");

    QNetworkRequest mockRequest;

    UrlUtil::setHeadersFromStringBlob(rawHeaders, mockRequest);

    QString headerName("Content-Type");
    QCOMPARE(QString(mockRequest.rawHeader(headerName.toUtf8())), QString("test-application"));

    headerName = "Auth";
    QCOMPARE(QString(mockRequest.rawHeader(headerName.toUtf8())), QString("thisIs-an:auth_token"));

    headerName = "Incomplete-";
    QCOMPARE(QString(mockRequest.rawHeader(headerName.toUtf8())), QString(""));
}

void UrlUtil_Test::test_safeParseVerb_Valid() {
    QString verb("GET");
    HttpVerb resultVerb = UrlUtil::safeParseVerb(verb);
    QCOMPARE(HttpVerb::GET, resultVerb);

    verb = "get";
    resultVerb = UrlUtil::safeParseVerb(verb);
    QCOMPARE(HttpVerb::GET, resultVerb);
}

void UrlUtil_Test::test_safeParseVerb_Invalid() {
    QString verb("P0ST");
    HttpVerb resultVerb = UrlUtil::safeParseVerb(verb);
    QCOMPARE(HttpVerb::GET, resultVerb);

    verb = "DEL ETE";
    resultVerb = UrlUtil::safeParseVerb(verb);
    QCOMPARE(HttpVerb::GET, resultVerb);
}

void UrlUtil_Test::test_safeParseVerb_Null() {
    QString verb;
    HttpVerb resultVerb = UrlUtil::safeParseVerb(verb);
    QCOMPARE(HttpVerb::GET, resultVerb);
}
