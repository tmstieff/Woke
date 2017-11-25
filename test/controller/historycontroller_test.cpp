#include "historycontroller_test.h"

HistoryController_Test::HistoryController_Test() : QObject() {
    this->historyController = new HistoryController(0);
}

void HistoryController_Test::initTestCase() {
    initDatabase();
}

/**
 * Given: A request without a name set
 * When: The request is saved
 * Then: A default name is provided
 */
void HistoryController_Test::test_addEntry_defaultName() {
    Request request;
    request.setHost("api.github.com");
    request.setRequestBody("{\"test\": \"entry\"}");
    request.setRequestHeaders("User-Agent: woke");
    request.setProto("https://");
    request.setUri("/users");
    request.setVerb("GET");

    this->historyController->addEntry(request);

    QCOMPARE(request.getName(), QString("api.github.com/users"));
}

/**
 * Given: A saved request
 * When: The latest requests are queried
 * Then: The results are order and limited
 */
void HistoryController_Test::test_getLatest() {
    Request requestUsers;
    requestUsers.setHost("api.github.com");
    requestUsers.setRequestBody("{\"test\": \"entry\"}");
    requestUsers.setRequestHeaders("User-Agent: woke");
    requestUsers.setProto("https://");
    requestUsers.setUri("/users");
    requestUsers.setVerb("GET");

    requestUsers.save();

    auto recentRequests = this->historyController->getLatest(10);

    QCOMPARE(recentRequests.data()->at(0).data()->pk(), requestUsers.pk());

    Request requestUser1234;
    requestUser1234.setHost("api.github.com");
    requestUser1234.setRequestBody("{\"test\": \"entry\"}");
    requestUser1234.setRequestHeaders("User-Agent: woke");
    requestUser1234.setProto("https://");
    requestUser1234.setUri("/users/1234");
    requestUser1234.setVerb("GET");

    requestUser1234.save();

    recentRequests = this->historyController->getLatest(10);

    QCOMPARE(recentRequests.data()->at(0).data()->pk(), requestUser1234.pk());
    QCOMPARE(recentRequests.data()->at(1).data()->pk(), requestUsers.pk());
}
