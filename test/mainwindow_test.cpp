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

    this->verbText = verb;
    this->urlText = url;
    this->headersText = headers;
    this->bodyText = body;

    this->sendRequest();

    // currentRequest should have all fields set except response fields
    QCOMPARE(this->currentRequest.data()->getVerb(), QString("GET"));
    QCOMPARE(this->currentRequest.data()->getProto(), QString("https://"));
    QCOMPARE(this->currentRequest.data()->getHost(), QString("api.github.com"));
    QCOMPARE(this->currentRequest.data()->getUri(), QString("/users"));
    QCOMPARE(this->currentRequest.data()->getRequestHeaders(), QString("User-Agent: test-agent"));
    QCOMPARE(this->currentRequest.data()->getRequestBody(), QString(""));

    auto reply = QSharedPointer<QNetworkReply>(new MockNetworkReply());
    this->responseReceivedSlot(reply.data());

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

    this->verbText = verb;
    this->urlText = url;
    this->headersText = headers;
    this->bodyText = body;

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

    this->verbText = verb;
    this->urlText = url;

    auto reply = QSharedPointer<MockNetworkReply>(new MockNetworkReply);
    QString bodyString("Test response data");
    reply.data()->setResponseStatus(301);

    this->responseReceivedSlot(reply.data());

    QCOMPARE(this->statusCodeLabel->text(), QString("301"));
    QCOMPARE(this->timeLabel->text(), QString("0 ms"));

    // TODO: Figure out how to mock the reply data
}
