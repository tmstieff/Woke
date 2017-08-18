#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Woke");

    QObject::connect(this->requestsController.networkManager.data(), SIGNAL(finished(QNetworkReply *)), this,
                     SLOT(responseReceivedSlot(QNetworkReply *)));

    bodyInput = ui->bodyInput;
    responseTabsInput = ui->responseTabsInput;
    requestTabsInput = ui->requestTabsInput;
    bodyInput = ui->bodyInput;
    verbInput = ui->verbInput;
    urlInput = ui->urlTextMultilineInput;

    // Order is important so we can just index based on the enum ordinal
    this->requestButtons.push_back(QSharedPointer<QPushButton>(this->ui->requestHeadersButton));
    this->requestButtons.push_back(QSharedPointer<QPushButton>(this->ui->requestScriptButton));

    this->responseButtons.push_back(QSharedPointer<QPushButton>(this->ui->responseHeadersButton));
    this->responseButtons.push_back(QSharedPointer<QPushButton>(this->ui->responseBodyButton));
    this->responseButtons.push_back(QSharedPointer<QPushButton>(this->ui->responseScriptButton));

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
    responseTabsInput->setFont(defaultMonoFont);
    requestTabsInput->setFont(defaultMonoFont);

    const int tabSpaces = 2;
    QFontMetrics metrics(defaultMonoFont);

    // Set tab width to 2 spaces
    bodyInput->setTabStopWidth(tabSpaces * metrics.width(' '));
    responseTabsInput->setTabStopWidth(tabSpaces * metrics.width(' '));

    // Ad the default syntax highlighters
    this->responseBodyHighlighter = new JsonSyntaxHighlighter(this->responseTabsInput->document());
    this->bodyHighlighter = new JsonSyntaxHighlighter(this->bodyInput->document());
    this->urlHighlighter = new UrlSyntaxHighlighter(this->urlInput->document());

    this->currentRequest = QSharedPointer<Request>(new Request);
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
    auto verb = this->verbInput->text();
    auto url = this->urlInput->toPlainText();
    auto headers = this->requestTabsInput->toPlainText();
    auto body = this->bodyInput->toPlainText();

    this->currentRequest = this->requestsController.sendRequest(verb, url, headers, body);
    this->resetResponseFields(this->currentRequest.data()->getHost(), this->currentRequest.data()->getUri(),
                              this->verbInput->text());
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
void MainWindow::setResponseTabsInput(ResponseInfo responseInfo, QNetworkReply &response) {
    auto headerList = response.rawHeaderList();
    QString headerStr;
    foreach (QByteArray head, headerList) {
        headerStr = headerStr.append(head + ": " + response.rawHeader(head)).append("\n");
    }

    this->currentRequest->setResponseHeaders(headerStr);
    this->currentRequest->setResponseContentType(responseInfo.contentType);
    this->currentRequest->setResponseBody(response.readAll());

    this->setResponseTabsInput(*this->currentRequest.data());
}

void MainWindow::setResponseTabsInput(Request &request) {
    if (ResponseGuiTabs::RES_HEADERS == this->currentResponseTab) {
        this->responseTabsInput->setPlainText(request.getResponseHeaders());
    } else if (ResponseGuiTabs::RES_SCRIPT == this->currentResponseTab) {
        this->responseTabsInput->setPlainText(request.getResponseScript());
    } else if (ResponseGuiTabs::RES_BODY == this->currentResponseTab) {
        qDebug() << "Set response body" << request.getResponseContentType();

        QString body;
        if (request.getResponseContentType().indexOf(QString("application/json"), 0, Qt::CaseInsensitive) >= 0) {
            qDebug() << "Set JSON response body";

            QJsonDocument jsonDoc = QJsonDocument::fromJson(request.getResponseBody().toUtf8());
            body = jsonDoc.toJson(QJsonDocument::Indented);
            request.setResponseBody(body);
        } else {
            QByteArray bodyBytes = request.getResponseBody().toUtf8();
            body = QString::fromUtf8(bodyBytes);
        }

        this->responseTabsInput->setPlainText(body);
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

    this->setResponseTabsInput(responseInfo, *response);

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

    const QString &newStylesheet =
        stylesheet.replace(QRegularExpression(QString(property + ": .+;")), property + ": " + value + ";");

    widget.setStyleSheet(newStylesheet);
}

void MainWindow::setUiFields(QSharedPointer<Request> request) {
    this->urlInput->setPlainText(request.data()->getProto() + request.data()->getHost() + request.data()->getUri());
    this->requestTabsInput->setPlainText(request.data()->getRequestHeaders());
    this->bodyInput->setPlainText(request.data()->getRequestBody());
    this->timeLabel->setText(QString::number(request.data()->getTime()) + " ms");
    this->hostLabel->setText(request.data()->getHost());
    this->uriLabel->setText(request.data()->getUri());
    this->verbLabel->setText(request.data()->getVerb());
    this->verbInput->setText(request.data()->getVerb());
    this->setStatusCodeLabel(request.data()->getStatusCode());
    this->setResponseTabsInput(*request.data());
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
    this->responseTabsInput->setPlainText(QString(""));
}

void MainWindow::setRequestInput(RequestGuiTabs tab) {
    // Save the current text, then set the new tab content
    if (RequestGuiTabs::REQ_HEADERS == this->currentRequestTab) {
        this->currentRequest.data()->setRequestHeaders(this->requestTabsInput->toPlainText());
    } else if (RequestGuiTabs::REQ_SCRIPT == this->currentRequestTab) {
        this->currentRequest.data()->setRequestScript(this->requestTabsInput->toPlainText());
    }

    // Set the input with the content for the requested tab
    this->currentRequestTab = tab;
    this->setActiveTab(this->requestButtons, tab);

    qDebug() << "Request tab" << tab;

    if (RequestGuiTabs::REQ_HEADERS == tab) {
        this->requestTabsInput->setPlainText(this->currentRequest.data()->getRequestHeaders());
    } else if (RequestGuiTabs::REQ_SCRIPT == tab) {
        this->requestTabsInput->setPlainText(this->currentRequest.data()->getRequestScript());
    }
}

void MainWindow::setResponseInput(ResponseGuiTabs tab) {
    // Save the current text, then set the new tab content
    if (ResponseGuiTabs::RES_HEADERS == this->currentResponseTab) {
        this->currentRequest.data()->setRequestHeaders(this->responseTabsInput->toPlainText());
    } else if (ResponseGuiTabs::RES_SCRIPT == this->currentResponseTab) {
        this->currentRequest.data()->setRequestScript(this->responseTabsInput->toPlainText());
    } else if (ResponseGuiTabs::RES_BODY == this->currentResponseTab) {
        this->currentRequest.data()->setRequestBody(this->responseTabsInput->toPlainText());
    }

    // Set the input with the content for the requested tab
    this->currentResponseTab = tab;
    this->setActiveTab(this->responseButtons, tab);

    if (ResponseGuiTabs::RES_HEADERS == tab) {
        this->responseTabsInput->setPlainText(this->currentRequest.data()->getResponseHeaders());
    } else if (ResponseGuiTabs::RES_SCRIPT == tab) {
        this->responseTabsInput->setPlainText(this->currentRequest.data()->getResponseScript());
    } else if (ResponseGuiTabs::RES_BODY == tab) {
        this->responseTabsInput->setPlainText(this->currentRequest.data()->getResponseBody());
    }
}

void MainWindow::setActiveTabStyle(QPushButton &button) {
    QString property("border-bottom");
    QString value("3px solid #6ABDDB");

    this->setStylesheetProperty(button, property, value);

    property = "background-color";
    value = "#3c3e3f";

    this->setStylesheetProperty(button, property, value);
}

void MainWindow::setInactiveTabStyle(QPushButton &button) {
    QString property("border-bottom");
    QString value("3px solid #2C2E2F");

    this->setStylesheetProperty(button, property, value);

    property = "background-color";
    value = "#313335";

    this->setStylesheetProperty(button, property, value);
}

void MainWindow::setActiveTab(QList<QSharedPointer<QPushButton>> &buttons, int tabIndex) {
    for (int i = 0; i < buttons.length(); i++) {
        if (tabIndex == i) {
            this->setActiveTabStyle(*buttons.at(i).data());
        } else {
            this->setInactiveTabStyle(*buttons.at(i).data());
        }
    }
}

/*
 * Event Handlers
 */
void MainWindow::on_sendButton_clicked() {
    this->sendRequest();
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

void MainWindow::on_urlTextMultilineInput_returnPressed() {
    this->sendRequest();
}

void MainWindow::on_requestHeadersButton_clicked() {
    this->setRequestInput(RequestGuiTabs::REQ_HEADERS);
}

void MainWindow::on_requestScriptButton_clicked() {
    this->setRequestInput(RequestGuiTabs::REQ_SCRIPT);
}

void MainWindow::on_responseHeadersButton_clicked() {
    this->setResponseInput(ResponseGuiTabs::RES_HEADERS);
}

void MainWindow::on_responseBodyButton_clicked() {
    this->setResponseInput(ResponseGuiTabs::RES_BODY);
}

void MainWindow::on_responseScriptButton_clicked() {
    this->setResponseInput(ResponseGuiTabs::RES_SCRIPT);
}
