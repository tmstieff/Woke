#include "mainwindow_test.h"

#include "controller/mockrequestscontroller.h"


void MainWindow_Test::initTestCase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        Q_ASSERT(false);
    } else {
        qDebug() << "Database: connection ok";
    }

    QDjango::setDatabase(db);
    QDjango::registerModel<Request>();
    QDjango::createTables();

    this->requestsController = MockRequestsController();
}

/**
 * Given: A blank GUI
 * When: A valid request is sent
 * Then: The currentRequest is set with all appropriate fields, and the request/response data is saved in the database
 */
void MainWindow_Test::test_sendRequest_valid() {
    QString verb("GET");
    QString url("https://api.github.com/users");
    QString headers("User-Agent: test-agent");
    QString body("");

    this->verbInput->setText(verb);
    this->urlInput->setPlainText(url);
    this->requestTabsInput->setPlainText(headers);
    this->bodyInput->setPlainText(body);

    this->sendRequest();

    // currentRequest should have all fields set except response fields
    QCOMPARE(this->currentRequest.data()->getVerb(), QString("GET"));
    QCOMPARE(this->currentRequest.data()->getProto(), QString("https://"));
    QCOMPARE(this->currentRequest.data()->getHost(), QString("api.github.com"));
    QCOMPARE(this->currentRequest.data()->getUri(), QString("/users"));
    QCOMPARE(this->currentRequest.data()->getRequestHeaders(), QString("User-Agent: test-agent"));
    QCOMPARE(this->currentRequest.data()->getRequestBody(), QString(""));

    auto reply = QSharedPointer<QNetworkReply>(new MockNetworkReply());
    this->responseReceived(reply.data());

    QCOMPARE(this->currentRequest.data()->getStatusCode(), QString::number(200));
    QCOMPARE(this->currentRequest.data()->getTime(), 0);

    // Request object should be saved in the DB
    auto mostRecent = this->historyController.getLatest(1);
    this->compareRequests(*mostRecent.data()->at(0).data(), *this->currentRequest.data());

    // recentRequests should be updated
    this->compareRequests(*this->recentRequests.data()->at(0).data(), *this->currentRequest.data());
}

void MainWindow_Test::compareRequests(Request &left, Request &right) {
    QCOMPARE(left.getVerb(), right.getVerb());
    QCOMPARE(left.getProto(), right.getProto());
    QCOMPARE(left.getHost(), right.getHost());
    QCOMPARE(left.getUri(), right.getUri());
    QCOMPARE(left.getRequestHeaders(), right.getRequestHeaders());
    QCOMPARE(left.getRequestBody(), right.getRequestBody());
}

/**
 * Given: An existing response populating the response body
 * When: A new request is sent
 * Then: The response fields are reset
 */
void MainWindow_Test::test_sendRequest_gui() {
    this->statusCodeLabel->setText("200");
    this->verbLabel->setText("POST");
    this->timeLabel->setText("2031 ms");
    this->hostLabel->setText("api.github.com");
    this->uriLabel->setText("/users");
    this->responseTabsInput->setPlainText("Existing response data");

    QString verb("GET");
    QString url("https://api.github.com/users");
    QString headers("User-Agent: test-agent");
    QString body("");

    this->verbInput->setText(verb);
    this->urlInput->setPlainText(url);
    this->requestTabsInput->setPlainText(headers);
    this->bodyInput->setPlainText(body);

    this->sendRequest();

    // Response body should be reset once the request is sent
    QCOMPARE(this->statusCodeLabel->text(), QString("-"));
    QCOMPARE(this->verbLabel->text(), QString("GET"));
    QCOMPARE(this->timeLabel->text(), QString("- ms"));
    QCOMPARE(this->hostLabel->text(), QString("api.github.com"));
    QCOMPARE(this->uriLabel->text(), QString("/users"));
    QCOMPARE(this->responseTabsInput->toPlainText(), QString(""));
}

/**
 * Given: An existing response populating the response body
 * When: A new request is sent
 * Then: The response fields are reset
 */
void MainWindow_Test::test_responseReceived_gui() {
    this->statusCodeLabel->setText("200");
    this->verbLabel->setText("POST");
    this->timeLabel->setText("2031 ms");
    this->hostLabel->setText("api.github.com");
    this->uriLabel->setText("/users");
    this->responseTabsInput->setPlainText("Existing response data");

    QString verb("GET");
    QString url("https://api.github.com/users");
    QString headers("User-Agent: test-agent");
    QString body("");

    this->verbInput->setText(verb);
    this->urlInput->setPlainText(url);

    auto reply = QSharedPointer<MockNetworkReply>(new MockNetworkReply);
    QString bodyString("Test response data");
    reply.data()->setResponseStatus(301);

    this->responseReceived(reply.data());

    QCOMPARE(this->statusCodeLabel->text(), QString("301"));
    // TODO: Figure out how to mock the reply data
}

/**
 * Give: An existing request is populated
 * When: A new request is selected from the recent requests list
 * Then: The GUI updates and the currentRequest updates
 */
void MainWindow_Test::test_recentRequestPressed_currentRequest() {
    // Add a recent request first
    auto request = QSharedPointer<Request>(new Request());
    request.data()->setStatusCode("200");
    request.data()->setVerb("POST");
    request.data()->setProto("http://");
    request.data()->setHost("localhost:8080");
    request.data()->setUri("/project");
    request.data()->setRequestBody("{\"key\": \"value\"}");
    request.data()->setTime(125);
    request.data()->save();

    this->refreshRecentRequests();

    this->statusCodeLabel->setText("200");
    this->verbLabel->setText("POST");
    this->timeLabel->setText("2031 ms");
    this->hostLabel->setText("api.github.com");
    this->uriLabel->setText("/users");
    this->requestTabsInput->setPlainText("Existing request data");
    this->responseTabsInput->setPlainText("Existing response data");

    auto index = this->recentRequestsListWidget->model()->index(0, 0);
    this->on_recentRequestsListWidget_activated(index);

    this->compareRequests(*this->currentRequest.data(), *request.data());

    QCOMPARE(this->statusCodeLabel->text(), QString("200"));
    QCOMPARE(this->verbLabel->text(), QString("POST"));
    QCOMPARE(this->timeLabel->text(), QString("125 ms"));
    QCOMPARE(this->hostLabel->text(), QString("localhost:8080"));
    QCOMPARE(this->uriLabel->text(), QString("/project"));
    QCOMPARE(this->bodyInput->toPlainText(), QString("{\"key\": \"value\"}"));
    QCOMPARE(this->responseTabsInput->toPlainText(), QString(""));
}
