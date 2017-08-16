#ifndef REQUESTITEM_TEST_H
#define REQUESTITEM_TEST_H

#include <QObject>
#include <QTest>
#include "../../src/view/requestitem.h"


class RequestItem_Test : public QObject
{
    Q_OBJECT

private slots:
   void test_setInformation_valid();
};

#endif // REQUESTITEM_TEST_H
