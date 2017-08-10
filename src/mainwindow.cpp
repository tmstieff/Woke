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

    responseBodyInput = ui->responseBodyInput;
    headersInput = ui->headersInput;
    bodyInput = ui->bodyInput;

    statusCodeLabel = ui->statusCodeLabel;
    uriLabel = ui->uriLabel;
    timeLabel = ui->timeLabel;
    hostLabel = ui->hostLabel;
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
    auto response = this->networkManager->get(request)	;
}

void MainWindow::responseReceivedSlot(QNetworkReply * response) {
    auto error = response->errorString();
    qDebug() << error;

    QVariant statusCode = response->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int statusCodeInt = statusCode.toInt();
    QString statusCodeStr = QString::number(statusCodeInt);

    statusCodeLabel->setText(statusCodeStr);

    QByteArray bodyBytes = response->readAll();

    qDebug() << bodyBytes;

    responseBodyInput->setPlainText(bodyBytes);
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
