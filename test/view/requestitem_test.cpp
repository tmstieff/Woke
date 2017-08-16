#include "requestitem_test.h"


void RequestItem_Test::test_setInformation_valid()
{
    RequestItem requestItem;
    requestItem.setInformation("GET", "/user", "http://api.github.com");

    QCOMPARE(requestItem.getVerb(), QString("GET"));
    QCOMPARE(requestItem.getUri(), QString("/user"));
    QCOMPARE(requestItem.getUrl(), QString("http://api.github.com"));
}
