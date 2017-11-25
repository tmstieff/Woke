#ifndef REQUESTITEM_TEST_H
#define REQUESTITEM_TEST_H

#include "../../src/view/requestitem.h"
#include <QObject>
#include <QTest>

class RequestItem_Test : public QObject {
    Q_OBJECT

  private Q_SLOTS:
    void test_setInformation_valid();
};

#endif // REQUESTITEM_TEST_H
