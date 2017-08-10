#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "url_util.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Build the network manager on init
    this->networkManager = new QNetworkAccessManager(this);

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

    this->responseBodyHighlighter = new JsonSyntaxHighlighter(this->responseBodyInput->document());
    this->bodyHighlighter = new JsonSyntaxHighlighter(this->bodyInput->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest() {
    UrlSegments segments = UrlUtil::safeSplitUrl(this->urlText);

    hostLabel->setText(segments.proto + segments.hostname);
    uriLabel->setText(segments.uri);

    auto request = QNetworkRequest(this->urlText);
    UrlUtil::setHeadersFromStringBlob(this->headersText, request);
    HttpVerb verb = UrlUtil::safeParseVerb(this->verbText);

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

void MainWindow::responseReceivedSlot(QNetworkReply * response) {
    auto error = response->errorString();
    qDebug() << error;

    QVariant statusCode = response->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int statusCodeInt = statusCode.toInt();
    QString statusCodeStr = QString::number(statusCodeInt);

    statusCodeLabel->setText(statusCodeStr);

    QString contentType = QString("");
    QVariant contentTypeVar = response->header(QNetworkRequest::KnownHeaders::ContentTypeHeader);
    if (contentTypeVar.canConvert(QVariant::String)) {
        contentType = contentTypeVar.toString();
    }

    qDebug() << contentType;

    if (contentType.indexOf(QString("application/json"), 0, Qt::CaseInsensitive) >= 0) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response->readAll());
        responseBodyInput->setPlainText(jsonDoc.toJson(QJsonDocument::Indented));
    } else {
        QByteArray bodyBytes = response->readAll();
        responseBodyInput->setPlainText(bodyBytes);
    }
}

void MainWindow::on_sendButton_clicked()
{
    this->sendRequest();
}

void MainWindow::on_urlTextInput_textChanged(const QString &arg1)
{
   this->urlText = arg1;
}

void MainWindow::on_urlTextInput_returnPressed()
{
   this->sendRequest();
}

void MainWindow::on_verbInput_textChanged(const QString &arg1)
{
   this->verbText = arg1;
}

void MainWindow::on_bodyInput_textChanged()
{
   this->bodyText = this->bodyInput->toPlainText();
}

void MainWindow::on_headersInput_textChanged()
{
   this->headersText = this->headersInput->toPlainText();
}
