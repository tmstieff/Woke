#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../urlutil.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Woke");

    // Build the network manager on init
    this->networkManager = new QNetworkAccessManager(this);

    this->responseTimer = QElapsedTimer();

    QObject::connect(this->networkManager, SIGNAL(finished(QNetworkReply*)), this , SLOT(responseReceivedSlot(QNetworkReply*)));

    bodyInput = ui->bodyInput;
    responseBodyInput = ui->responseBodyInput;
    headersInput = ui->headersInput;
    bodyInput = ui->bodyInput;
    verbInput = ui->verbInput;
    urlInput = ui->urlTextInput;

    statusCodeLabel = ui->statusCodeLabel;
    uriLabel = ui->uriLabel;
    timeLabel = ui->timeLabel;
    hostLabel = ui->hostLabel;
    verbLabel = ui->verbLabel;
    recentRequestsListWidget = ui->recentRequestsListWidget;

    // Set the default font for all editors
    QFont defaultMonoFont;
    defaultMonoFont.setFamily("Courier");
    defaultMonoFont.setStyleHint(QFont::Monospace);
    defaultMonoFont.setFixedPitch(true);
    defaultMonoFont.setPointSize(10);
    bodyInput->setFont(defaultMonoFont);
    responseBodyInput->setFont(defaultMonoFont);
    headersInput->setFont(defaultMonoFont);

    const int tabSpaces = 2;
    QFontMetrics metrics(defaultMonoFont);

    // Set tab width to 2 spaces
    bodyInput->setTabStopWidth(tabSpaces * metrics.width(' '));
    responseBodyInput->setTabStopWidth(tabSpaces * metrics.width(' '));

    // Ad the default syntax highlighters
    this->responseBodyHighlighter = new JsonSyntaxHighlighter(this->responseBodyInput->document());
    this->bodyHighlighter = new JsonSyntaxHighlighter(this->bodyInput->document());

    this->refreshRecentReqests();

    if (this->recentRequests.data()->length() > 0) {
      this->setUi(this->recentRequests.data()->at(0));
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief MainWindow::sendRequest
 *
 * Send a network request over the wire
 */
void MainWindow::sendRequest() {
    this->currentRequest = new Request();

    UrlSegments segments = UrlUtil::safeSplitUrl(this->urlText);

    hostLabel->setText(segments.proto + segments.hostname);
    uriLabel->setText(segments.uri);
    QNetworkRequest request(this->urlText);
    UrlUtil::setHeadersFromStringBlob(this->headersText, request);
    HttpVerb verb = UrlUtil::safeParseVerb(this->verbText);

    this->timeLabel->setText("- ms");
    this->responseTimer.start();

    this->verbLabel->setText(HttpVerbStrings[verb]);
    this->setStylesheetProperty(*this->statusCodeLabel, "background-color", DEFAULT_INFO_LABEL_COLOR);

    this->currentRequest->setProto(segments.proto);
    this->currentRequest->setHost(segments.hostname);
    this->currentRequest->setUri(segments.uri);
    this->currentRequest->setVerb(HttpVerbStrings[verb]);
    this->currentRequest->setRequestHeaders(this->headersText);
    this->currentRequest->setRequestBody(this->bodyText);

    switch (verb) {
    case HttpVerb::GET:
        this->networkManager->get(request);
        break;
    case HttpVerb::POST:
        this->networkManager->post(request, this->bodyText.toUtf8());
        break;
    case HttpVerb::PUT:
        this->networkManager->put(request, this->bodyText.toUtf8());
        break;
    case HttpVerb::PATCH:
        this->networkManager->put(request, this->bodyText.toUtf8());
        break;
    case HttpVerb::DELETE:
        this->networkManager->deleteResource(request);
        break;
    case HttpVerb::HEAD:
        this->networkManager->head(request);
        break;
    case HttpVerb::OPTIONS:
        this->networkManager->get(request);
        break;
    case HttpVerb::CONNECT:
        this->networkManager->get(request);
        break;
    default:
        break;
    }
}

void MainWindow::setTimeLabel()
{
    int responseTime = this->responseTimer.elapsed();
    auto responseTimeStr = QString::number(responseTime) + " ms";
    this->timeLabel->setText(responseTimeStr);
    this->currentRequest->setTime(responseTime);
}

void MainWindow::setStatusCodeLabel(QNetworkReply &response)
{
    auto statusCode = response.attribute(QNetworkRequest::HttpStatusCodeAttribute);
    auto statusCodeInt = statusCode.toInt();
    auto statusCodeStr = QString::number(statusCodeInt);

    if (statusCodeInt == 0) {
        statusCodeStr = QString("-");
    }

    this->statusCodeLabel->setText(statusCodeStr);
    this->currentRequest->setStatusCode(statusCodeStr);

    if (statusCodeInt >= 200 && statusCodeInt <= 299) {
        QString property("background-color");
        QString value("#117844");
        this->setStylesheetProperty(*this->statusCodeLabel, property, value);
    }
}

void MainWindow::setResponseBodyEditor(QNetworkReply &response)
{
    QString contentType("");
    auto contentTypeVar = response.header(QNetworkRequest::KnownHeaders::ContentTypeHeader);
    if (contentTypeVar.canConvert(QVariant::String)) {
        contentType = contentTypeVar.toString();
    }

    qDebug() << contentType;

    if (contentType.indexOf(QString("application/json"), 0, Qt::CaseInsensitive) >= 0) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response.readAll());
        responseBodyInput->setPlainText(jsonDoc.toJson(QJsonDocument::Indented));
    } else {
        QByteArray bodyBytes = response.readAll();
        responseBodyInput->setPlainText(bodyBytes);
    }

    this->currentRequest->setResponseBody(responseBodyInput->toPlainText());
}

/**
 * @brief MainWindow::responseReceivedSlot
 *
 * Handle a response received event from the network manager instance
 *
 * @param response pushed from the network manager
 */
void MainWindow::responseReceivedSlot(QNetworkReply * response) {
    this->setTimeLabel();
    this->setStatusCodeLabel(*response);

    auto error = response->errorString();
    qDebug() << error;

    this->setResponseBodyEditor(*response);

    this->historyController.addEntry(*this->currentRequest);
    this->refreshRecentReqests();
}

/**
 * @brief MainWindow::setStylesheetProperty
 *
 * Set or replace a specific stylesheet property on a widget
 *
 * @param widget
 * @param property
 * @param value
 */
void MainWindow::setStylesheetProperty(QWidget &widget, const QString &property, const QString &value) {
    auto stylesheet = widget.styleSheet();

    stylesheet = stylesheet.replace(QRegularExpression(QString(property + ": .+;")), property + ": " + value + ";");

    qDebug() << stylesheet;

    widget.setStyleSheet(stylesheet);
}

void MainWindow::setUi(QSharedPointer<Request> request)
{
    this->urlInput->setText(request.data()->getProto() + request.data()->getHost() + request.data()->getUri());
    this->headersInput->setPlainText(request.data()->getRequestHeaders());
    this->bodyInput->setPlainText(request.data()->getRequestBody());
    this->responseBodyInput->setPlainText(request.data()->getResponseBody());
    this->timeLabel->setText(QString::number(request.data()->getTime()) + " ms");
    this->hostLabel->setText(request.data()->getProto() + request.data()->getHost());
    this->uriLabel->setText(request.data()->getUri());
    this->verbLabel->setText(request.data()->getVerb());
    this->statusCodeLabel->setText(request.data()->getStatusCode());
}

void MainWindow::refreshRecentReqests()
{
    this->recentRequests = this->historyController.getLatest(10);
    this->recentRequestsListWidget->clear();

    for (int i = 0; i < this->recentRequests.data()->size(); i++) {
        QListWidgetItem *item = new QListWidgetItem(recentRequestsListWidget);
        item->setSizeHint(QSize(200, 80));

        RequestItem *requestItem = new RequestItem(this);
        requestItem->setInformation(this->recentRequests.data()->at(i).data()->getVerb(),
                                    this->recentRequests.data()->at(i).data()->getUri(),
                                    this->recentRequests.data()->at(i).data()->getHost());
        recentRequestsListWidget->setItemWidget(item, requestItem);
    }
}

/*
 * Event Handlers
 */
void MainWindow::on_sendButton_clicked() {
    this->sendRequest();
}

void MainWindow::on_urlTextInput_textChanged(const QString &arg1) {
   this->urlText = arg1;
}

void MainWindow::on_urlTextInput_returnPressed() {
   this->sendRequest();
}

void MainWindow::on_verbInput_textChanged(const QString &arg1) {
   this->verbText = arg1;
}

void MainWindow::on_bodyInput_textChanged() {
   this->bodyText = this->bodyInput->toPlainText();
}

void MainWindow::on_headersInput_textChanged() {
   this->headersText = this->headersInput->toPlainText();
}

void MainWindow::on_verbInput_returnPressed()
{
   this->sendRequest();
}

void MainWindow::on_recentRequestsListWidget_activated(const QModelIndex &index)
{
   this->setUi(this->recentRequests.data()->at(index.row()));
}

void MainWindow::on_recentRequestsListWidget_pressed(const QModelIndex &index)
{
   this->setUi(this->recentRequests.data()->at(index.row()));
}
