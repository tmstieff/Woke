#include "mainwindow_test.h"

#include "controller/mockrequestscontroller.h"


void MainWindow_Test::initTestCase()
{
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

void MainWindow_Test::test_sendRequest_valid()
{
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
    QCOMPARE(mostRecent.data()->at(0).data()->getVerb(), this->currentRequest.data()->getVerb());
    QCOMPARE(mostRecent.data()->at(0).data()->getProto(), this->currentRequest.data()->getProto());
    QCOMPARE(mostRecent.data()->at(0).data()->getHost(), this->currentRequest.data()->getHost());
    QCOMPARE(mostRecent.data()->at(0).data()->getUri(), this->currentRequest.data()->getUri());
    QCOMPARE(mostRecent.data()->at(0).data()->getRequestHeaders(), this->currentRequest.data()->getRequestHeaders());
    QCOMPARE(mostRecent.data()->at(0).data()->getRequestBody(), this->currentRequest.data()->getRequestBody());

    // recentRequests should be updated
    QCOMPARE(this->recentRequests.data()->at(0).data()->getVerb(), this->currentRequest.data()->getVerb());
    QCOMPARE(this->recentRequests.data()->at(0).data()->getProto(), this->currentRequest.data()->getProto());
    QCOMPARE(this->recentRequests.data()->at(0).data()->getHost(), this->currentRequest.data()->getHost());
    QCOMPARE(this->recentRequests.data()->at(0).data()->getUri(), this->currentRequest.data()->getUri());
    QCOMPARE(this->recentRequests.data()->at(0).data()->getRequestHeaders(), this->currentRequest.data()->getRequestHeaders());
    QCOMPARE(this->recentRequests.data()->at(0).data()->getRequestBody(), this->currentRequest.data()->getRequestBody());
}
