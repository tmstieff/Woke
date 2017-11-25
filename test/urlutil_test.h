#ifndef URLUTIL_TEST_H
#define URLUTIL_TEST_H

#include "../src/urlutil.h"
#include <QNetworkRequest>
#include <QObject>
#include <QTest>

class UrlUtil_Test : public QObject {
    Q_OBJECT

  private Q_SLOTS:
    void test_httpSplit();
    void test_httpsSplit();
    void test_httpSplit_WithUri();
    void test_httpSplit_Null();
    void test_setHeadersFromStringBlob_Single();
    void test_setHeadersFromStringBlob_Multi();
    void test_setHeadersFromStringBlob_Malformed();
    void test_safeParseVerb_Valid();
    void test_safeParseVerb_Invalid();
    void test_safeParseVerb_Null();
};

#endif // URLUTIL_TEST_H
