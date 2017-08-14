#ifndef URLUTIL_TEST_H
#define URLUTIL_TEST_H

#include <QObject>
#include <QTest>
#include "../src/urlutil.h"

class UrlUtil_Test : public QObject
{
  Q_OBJECT

private slots:
  void testHttpSplit();
  void testHttpsSplit();
  void testWithUri();
  void testNulls();
};

#endif // URLUTIL_TEST_H
