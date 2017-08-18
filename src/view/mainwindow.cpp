#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Woke");

    QObject::connect(this->requestsController.networkManager.data(), SIGNAL(finished(QNetworkReply *)), this,
                     SLOT(responseReceivedSlot(QNetworkReply *)));

    bodyInput = ui->bodyInput;
    responseBodyInput = ui->responseBodyInput;
    headersInput = ui->headersInput;
    bodyInput = ui->bodyInput;
    verbInput = ui->verbInput;
    urlInput = ui->urlTextMultilineInput;

    // Verb list auto-complete
    QStringList verbList;
    verbList << "GET"
             << "PUT"
             << "PATCH"
             << "POST"
             << "DELETE";
    auto *verbAutoComplete = new QCompleter(verbList, this);
    verbAutoComplete->setCaseSensitivity(Qt::CaseInsensitive);
    verbAutoComplete->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
    verbInput->setCompleter(verbAutoComplete);

    statusCodeLabel = ui->statusCodeLabel;
    uriLabel = ui->uriLabel;
    timeLabel = ui->timeLabel;
    hostLabel = ui->hostLabel;
    verbLabel = ui->verbLabel;
    recentRequestsListWidget = ui->recentRequestsListWidget;
    urlInput = ui->urlTextMultilineInput;

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
    this->urlHighlighter = new UrlSyntaxHighlighter(this->urlInput->document());

    this->refreshRecentRequests();

    if (this->recentRequests.data()->length() > 0) {
        this->setUiFields(this->recentRequests.data()->at(0));
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
    this->currentRequest =
        this->requestsController.sendRequest(this->verbText, this->urlText, this->headersText, this->bodyText);
    this->resetResponseFields(this->currentRequest.data()->getHost(), this->currentRequest.data()->getUri(),
                              this->verbText);
}

void MainWindow::setTimeLabel(ResponseInfo responseInfo) {
    auto responseTimeStr = QString::number(responseInfo.responseTime) + " ms";
    this->timeLabel->setText(responseTimeStr);
    this->currentRequest->setTime(responseInfo.responseTime);
}

void MainWindow::setStatusCodeLabel(ResponseInfo responseInfo) {
    auto statusCodeStr = QString::number(responseInfo.statusCode);

    if (responseInfo.statusCode == 0) {
        statusCodeStr = QString("-");
    }

    this->setStatusCodeLabel(statusCodeStr);
}

void MainWindow::setStatusCodeLabel(QString statusCode) {
    this->statusCodeLabel->setText(statusCode);

    int statusCodeInt = statusCode.toInt();

    if (statusCodeInt >= 200 && statusCodeInt <= 299) {
        QString property("background-color");
        QString value(GREEN_LABEL);
        this->setStylesheetProperty(*this->statusCodeLabel, property, value);
    } else if (statusCodeInt >= 300 && statusCodeInt <= 399) {
        QString property("background-color");
        QString value(DEFAULT_INFO_LABEL_COLOR);
        this->setStylesheetProperty(*this->statusCodeLabel, property, value);
    } else if (statusCodeInt >= 400 && statusCodeInt <= 499) {
        QString property("background-color");
        QString value(YELLOW_LABEL);
        this->setStylesheetProperty(*this->statusCodeLabel, property, value);
    } else if (statusCodeInt >= 500 && statusCodeInt <= 599) {
        QString property("background-color");
        QString value(RED_LABEL);
        this->setStylesheetProperty(*this->statusCodeLabel, property, value);
    } else {
        QString property("background-color");
        QString value(DEFAULT_INFO_LABEL_COLOR);
        this->setStylesheetProperty(*this->statusCodeLabel, property, value);
    }
}

/**
 * Set the response body fields based on the content-type
 * @param responseInfo
 * @param response
 */
void MainWindow::setResponseBodyEditor(ResponseInfo responseInfo, QNetworkReply &response) {
    if (responseInfo.contentType.indexOf(QString("application/json"), 0, Qt::CaseInsensitive) >= 0) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response.readAll());
        responseBodyInput->setPlainText(jsonDoc.toJson(QJsonDocument::Indented));
        this->currentRequest->setResponseBody(responseBodyInput->toPlainText());
    } else {
        QByteArray bodyBytes = response.readAll();

        auto body = QString::fromUtf8(bodyBytes);

        qDebug() << "Response body:" << body;

        responseBodyInput->setPlainText(body);
        this->currentRequest.data()->setRequestBody(body);
    }
}

/**
 * @brief MainWindow::responseReceivedSlot
 *
 * Handle a response received event from the network manager instance
 *
 * @param response pushed from the network manager
 */
void MainWindow::responseReceivedSlot(QNetworkReply *response) {
    ResponseInfo responseInfo = this->requestsController.handleResponse(*response);

    this->currentRequest.data()->setStatusCode(QString::number(responseInfo.statusCode));
    this->setTimeLabel(responseInfo);
    this->setStatusCodeLabel(responseInfo);

    auto error = response->errorString();
    qDebug() << error;

    this->setResponseBodyEditor(responseInfo, *response);

    this->historyController.addEntry(*this->currentRequest.data());
    this->refreshRecentRequests();
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

void MainWindow::setUiFields(QSharedPointer<Request> request) {
    this->urlInput->setPlainText(request.data()->getProto() + request.data()->getHost() + request.data()->getUri());
    this->headersInput->setPlainText(request.data()->getRequestHeaders());
    this->bodyInput->setPlainText(request.data()->getRequestBody());
    this->responseBodyInput->setPlainText(request.data()->getResponseBody());
    this->timeLabel->setText(QString::number(request.data()->getTime()) + " ms");
    this->hostLabel->setText(request.data()->getHost());
    this->uriLabel->setText(request.data()->getUri());
    this->verbLabel->setText(request.data()->getVerb());
    this->verbInput->setText(request.data()->getVerb());
    this->setStatusCodeLabel(request.data()->getStatusCode());
}

void MainWindow::refreshRecentRequests() {
    this->recentRequests = this->historyController.getLatest(10);
    this->recentRequestsListWidget->clear();

    for (const auto &i : *this->recentRequests.data()) {
        auto *item = new QListWidgetItem(recentRequestsListWidget);
        item->setSizeHint(QSize(200, 67));

        auto *requestItem = new RequestItem(this);
        requestItem->setInformation(i.data()->getVerb(), i.data()->getUri(), i.data()->getHost());
        recentRequestsListWidget->setItemWidget(item, requestItem);
    }
}

/**
 * Reset the response fields after a new request is sent
 * @param host
 * @param uri
 * @param verb
 */
void MainWindow::resetResponseFields(const QString &host, const QString &uri, const QString &verb) {
    this->hostLabel->setText(host);
    this->uriLabel->setText(uri);

    this->timeLabel->setText("- ms");
    this->statusCodeLabel->setText("-");
    this->verbLabel->setText(HttpVerbStrings[UrlUtil::safeParseVerb(verb)]);
    this->setStylesheetProperty(*this->statusCodeLabel, "background-color", DEFAULT_INFO_LABEL_COLOR);
    this->responseBodyInput->setPlainText(QString(""));
}

/*
 * Event Handlers
 */
void MainWindow::on_sendButton_clicked() {
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

void MainWindow::on_verbInput_returnPressed() {
    this->sendRequest();
}

void MainWindow::on_recentRequestsListWidget_activated(const QModelIndex &index) {
    this->setUiFields(this->recentRequests.data()->at(index.row()));
}

void MainWindow::on_recentRequestsListWidget_pressed(const QModelIndex &index) {
    this->setUiFields(this->recentRequests.data()->at(index.row()));
}

void MainWindow::on_urlTextMultilineInput_textChanged() {
    this->urlText = this->urlInput->toPlainText();
}

void MainWindow::on_urlTextMultilineInput_returnPressed() {
    this->sendRequest();
}
