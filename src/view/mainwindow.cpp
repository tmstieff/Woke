#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Woke");

    historyController = new HistoryController(this);
    projectController = new ProjectController(this);
    requestsController = new RequestsController(this);

    connect(this->requestsController->networkManager.data(), SIGNAL(finished(QNetworkReply *)), this,
            SLOT(responseReceived(QNetworkReply *)));

    bodyInput = ui->bodyInput;
    bodyInput = ui->bodyInput;
    verbInput = ui->verbInput;
    urlInput = ui->urlTextMultilineInput;

    requestEditor = ui->requestEditor;
    responseEditor = ui->responseEditor;

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
    projectRequestsListWidget = ui->projectsRequestsList;
    urlInput = ui->urlTextMultilineInput;

    // Set the default font for all editors
    QFont defaultMonoFont;
    defaultMonoFont.setFamily("Courier");
    defaultMonoFont.setStyleHint(QFont::Monospace);
    defaultMonoFont.setFixedPitch(true);
    defaultMonoFont.setPointSize(10);
    bodyInput->setFont(defaultMonoFont);

    const int tabSpaces = 2;
    QFontMetrics metrics(defaultMonoFont);

    // Set tab width to 2 spaces
    bodyInput->setTabStopWidth(tabSpaces * metrics.width(' '));

    // Add the default syntax highlighters
    this->bodyHighlighter = new JsonSyntaxHighlighter(this->bodyInput->document());
    this->urlHighlighter = new UrlSyntaxHighlighter(this->urlInput->document());

    defaultProject = this->projectController->upsertDefaultProject();
    projects = this->projectController->getProjects();

    this->currentRequest = QSharedPointer<Request>(new Request(this));
    this->refreshRecentRequests();

    if (this->recentRequests.data()->length() > 0) {
        this->setUiFields(this->recentRequests.data()->at(0), true);
    }

    this->urlEditor = new UrlEditor(this);
    this->urlEditor->hide();

    this->saveEditor = new SaveEditor(this);
    this->saveEditor->hide();

    for (int i = 0; i < projects.data()->size(); i++) {
        auto project = projects.data()->at(i).data();

        this->saveEditor->projectComboBox->addItem(project->getName(), QVariant(project->pk()));
        this->ui->projectsListComboBox->addItem(project->getName(), QVariant(project->pk()));
    }

    this->saveEditor->updateFields(*this->currentRequest.data());

    QObject::connect(this->saveEditor->confirmSaveButton, SIGNAL(released()), this,
                     SLOT(on_confirmSaveButton_released()));
    QObject::connect(this->saveEditor->cancelSaveButton, SIGNAL(released()), this,
                     SLOT(on_cancelSaveButton_released()));
    QObject::connect(this->saveEditor->confirmSaveAsButton, SIGNAL(released()), this,
                     SLOT(on_confirmSaveAsButton_released()));
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
    auto headers = *this->requestEditor->getHeaderData().data();
    auto preReqScript = *this->requestEditor->getPreRequestScriptData().data();
    auto postResScript = *this->responseEditor->getPostResponseScriptData().data();

    auto body = this->bodyInput->toPlainText();

    auto sentRequest = this->requestsController->sendRequest(verb, url, headers, body, preReqScript, true,
                                                             this->defaultProject, postResScript, this->currentRequest);
    this->resetResponseFields(this->currentRequest.data()->getHost(), this->currentRequest.data()->getUri(),
                              this->verbInput->text());
}

/**
 * @brief MainWindow::saveCurrentRequestToProject
 *
 * Save the MainWindow::currentRequest to the project currently selected
 * in the save editor
 */
void MainWindow::saveCurrentRequestToProject() {
    this->updateCurrentRequestFromFields();

    auto selectedProjectId = this->saveEditor->projectComboBox->currentData().toInt();
    auto selectedProject = this->projectController->getProjectPointer(selectedProjectId, this->currentRequest.data());

    this->currentRequest->setProject(selectedProject);

    auto name = this->saveEditor->nameEdit->text();
    this->currentRequest->setName(name);
    this->currentRequest->save();

    this->refreshProjectRequests();
}

void MainWindow::updateCurrentRequestFromFields() {
    auto urlSegments = UrlUtil::safeSplitUrl(this->urlInput->toPlainText());

    this->currentRequest.data()->setProto(urlSegments.proto);
    this->currentRequest.data()->setHost(urlSegments.hostname);
    this->currentRequest.data()->setUri(urlSegments.uri);
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

    LabelUtil::setStatusCodeLabel(statusCodeStr, *this->statusCodeLabel);
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
void MainWindow::setResponseInfo(ResponseInfo responseInfo, QNetworkReply &response) {
    auto headerList = response.rawHeaderList();
    QString headerStr;
    Q_FOREACH (QByteArray head, headerList) {
        headerStr = headerStr.append(head + ": " + response.rawHeader(head)).append("\n");
    }

    this->currentRequest->setResponseHeaders(headerStr);
    this->currentRequest->setResponseContentType(responseInfo.contentType);
    this->currentRequest->setResponseBody(response.readAll());

    this->setResponseInfo(*this->currentRequest.data());
}

void MainWindow::setResponseInfo(Request &request) {
    QString body;
    if (request.getResponseContentType().indexOf(QString("application/json"), 0, Qt::CaseInsensitive) >= 0) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(request.getResponseBody().toUtf8());
        body = jsonDoc.toJson(QJsonDocument::Indented);
        request.setResponseBody(body);
    } else {
        QByteArray bodyBytes = request.getResponseBody().toUtf8();
        body = QString::fromUtf8(bodyBytes);
    }

    this->responseEditor->setHeadersData(QSharedPointer<QString>::create(request.getResponseHeaders()));
    this->responseEditor->setBodyData(QSharedPointer<QString>::create(body));
    this->responseEditor->refreshUi();
    request.save();
}

/**
 * @brief MainWindow::responseReceivedSlot
 *
 * Handle a response received event from the network manager instance
 *
 * @param response pushed from the network manager
 */
void MainWindow::responseReceived(QNetworkReply *response) {
    ResponseInfo responseInfo = this->requestsController->handleResponse(*response);

    this->currentRequest.data()->setStatusCode(QString::number(responseInfo.statusCode));
    this->setTimeLabel(responseInfo);
    this->setStatusCodeLabel(responseInfo);

    this->setResponseInfo(responseInfo, *response);

    auto script = this->responseEditor->getPostResponseScriptData().data();
    auto scriptCopy = QString(script->data());
    this->pythonScriptController.executeScript(scriptCopy, this->currentRequest);

    this->historyController->addEntry(*this->currentRequest.data());
    this->refreshRecentRequests();
}
void MainWindow::setStylesheetProperty(QWidget &widget, const QString &property, const QString &value) {
    auto stylesheet = widget.styleSheet();

    const QString &newStylesheet =
        stylesheet.replace(QRegularExpression(QString(property + ": .+;")), property + ": " + value + ";");

    widget.setStyleSheet(newStylesheet);
}

void MainWindow::setUiFields(QSharedPointer<Request> request, bool setCurrentRequest) {
    this->urlInput->setPlainText(request.data()->getProto() + request.data()->getHost() + request.data()->getUri());

    const auto requestHeaders = request.data()->getRequestHeaders();
    this->requestEditor->setHeadersData(QSharedPointer<QString>::create(requestHeaders));

    const auto requestScript = request.data()->getRequestScript();
    this->requestEditor->setPreRequestScriptData(QSharedPointer<QString>::create(requestScript));

    const auto responseHeaders = request.data()->getResponseHeaders();
    this->responseEditor->setHeadersData(QSharedPointer<QString>::create(responseHeaders));

    const auto responseBody = request.data()->getResponseBody();
    this->responseEditor->setBodyData(QSharedPointer<QString>::create(responseBody));

    const auto responseScript = request.data()->getResponseScript();
    this->responseEditor->setPostResponseScriptData(QSharedPointer<QString>::create(responseScript));

    this->bodyInput->setPlainText(request.data()->getRequestBody());
    this->timeLabel->setText(QString::number(request.data()->getTime()) + " ms");
    this->hostLabel->setText(request.data()->getHost());
    this->uriLabel->setText(request.data()->getUri());
    this->verbLabel->setText(request.data()->getVerb());
    this->verbInput->setText(request.data()->getVerb());
    this->setStatusCodeLabel(request.data()->getStatusCode());
    this->setResponseInfo(*request.data());

    if (setCurrentRequest) {
        this->currentRequest = request;
    }
}

void MainWindow::refreshRecentRequests() {
    this->recentRequests = this->historyController->getLatest(10);
    this->recentRequestsListWidget->clear();

    for (const auto &i : *this->recentRequests.data()) {
        auto *item = new QListWidgetItem(recentRequestsListWidget);
        item->setSizeHint(QSize(200, 67));

        auto *requestItem = new RequestItem(this);
        requestItem->setInformation(i.data()->getVerb(), i.data()->getUri(), i.data()->getHost());
        recentRequestsListWidget->setItemWidget(item, requestItem);
    }
}

void MainWindow::refreshProjectRequests() {
    auto selectedProjectId = this->ui->projectsListComboBox->currentData().toInt();

    this->projectRequests = this->projectController->getRequests(selectedProjectId);
    this->projectRequestsListWidget->clear();

    for (const auto &i : *this->projectRequests.data()) {
        auto *item = new QListWidgetItem(this->projectRequestsListWidget);
        item->setSizeHint(QSize(200, 67));

        auto *requestItem = new RequestItem(this);

        requestItem->setInformation(i.data()->getVerb(), i.data()->getUri(), i.data()->getName());
        this->projectRequestsListWidget->setItemWidget(item, requestItem);
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
    this->responseEditor->resetTabData();
}

void MainWindow::showUrlEditor() {
    this->urlEditor->move(0, 0);

    auto urlInputPos = this->urlInput->mapToGlobal(QPoint(0, 0));
    this->urlEditor->resize(this->urlInput->width(), this->urlEditor->size().height());

    auto editorPos = urlInputPos;
    editorPos.setX(urlInputPos.x());
    editorPos.setY(urlInputPos.y() + 45);
    this->urlEditor->show();
    auto newPos = this->urlEditor->mapFromGlobal(editorPos);
    this->urlEditor->move(newPos);
}

void MainWindow::showSaveEditor() {

    qDebug() << "Move save editor";

    this->saveEditor->move(0, 0);

    auto saveButtonPos = this->ui->saveButton->mapToGlobal(QPoint(0, 0));

    auto editorPos = saveButtonPos;
    editorPos.setX(saveButtonPos.x() - this->saveEditor->width() + 50);
    editorPos.setY(saveButtonPos.y() + 45);
    this->saveEditor->show();
    auto newPos = this->saveEditor->mapFromGlobal(editorPos);
    this->saveEditor->move(newPos);
}

void MainWindow::setCurrentRequest(QSharedPointer<Request> newRequest) {
    this->currentRequest.data()->setRequestHeaders(*this->requestEditor->getHeaderData().data());
    this->currentRequest.data()->setRequestBody(this->bodyInput->toPlainText());
    this->currentRequest.data()->setRequestScript(*this->requestEditor->getPreRequestScriptData().data());
    this->currentRequest.data()->setResponseBody(*this->responseEditor->getBodyData().data());
    this->currentRequest.data()->setResponseHeaders(*this->responseEditor->getHeaderData().data());
    this->currentRequest.data()->setResponseScript(*this->responseEditor->getPostResponseScriptData().data());
    this->currentRequest.data()->save();

    this->currentRequest = newRequest;
    this->setUiFields(this->currentRequest, false);

    CurrentDataController::setCurrentRequestId(newRequest.data()->pk().toInt());

    if (this->currentRequest.data()->project() == nullptr) {
        CurrentDataController::setCurrentProjectId(this->defaultProject.data()->pk().toInt());
    } else {
        CurrentDataController::setCurrentProjectId(this->currentRequest.data()->project()->pk().toInt());
    }

    this->saveEditor->updateFields(*this->currentRequest.data());
}

/*
 * Event Handlers
 */
void MainWindow::on_sendButton_clicked() {
    this->sendRequest();
}

void MainWindow::on_recentRequestsListWidget_activated(const QModelIndex &index) {
    auto selectedRequest = this->recentRequests.data()->at(index.row());
    this->setCurrentRequest(selectedRequest);
}

void MainWindow::on_recentRequestsListWidget_pressed(const QModelIndex &index) {
    auto selectedRequest = this->recentRequests.data()->at(index.row());
    this->setCurrentRequest(selectedRequest);
}

void MainWindow::on_urlTextMultilineInput_returnPressed() {
    this->sendRequest();
}

void MainWindow::on_urlTextMultilineInput_focusIn() {
    // this->hideUrlEditor();
}

void MainWindow::on_urlTextMultilineInput_focusOut() {
    this->urlEditor->hide();
    auto urlEditGeometry = this->urlInput->geometry();
    urlEditGeometry.setHeight(36);
    this->urlInput->setGeometry(urlEditGeometry);
}

void MainWindow::on_saveButton_clicked() {
    this->showSaveEditor();
}

void MainWindow::on_confirmSaveButton_released() {
    this->saveEditor->hide();
    this->saveCurrentRequestToProject();
}

void MainWindow::on_confirmSaveAsButton_released() {
    this->saveEditor->hide();
    this->currentRequest.data()->setPk(QVariant());
    this->saveCurrentRequestToProject();
}

void MainWindow::on_cancelSaveButton_released() {
    this->saveEditor->hide();
    this->saveEditor->clearFields();
}

void MainWindow::on_projectsListComboBox_currentIndexChanged(int index) {
    // Unused param
    (void)index;

    this->refreshProjectRequests();
}

void MainWindow::on_projectsRequestsList_clicked(const QModelIndex &index) {
    auto selectedRequest = this->projectRequests.data()->at(index.row());
    selectedRequest = this->historyController->get(selectedRequest.data()->pk().toInt());
    this->setCurrentRequest(selectedRequest);
}

void MainWindow::on_projectsRequestsList_activated(const QModelIndex &index) {
    auto selectedRequest = this->projectRequests.data()->at(index.row());
    selectedRequest = this->historyController->get(selectedRequest.data()->pk().toInt());
    this->setCurrentRequest(selectedRequest);
}
