#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Build the network manager on init
    this->networkManager = new QNetworkAccessManager(this);

    QObject::connect(this->networkManager, SIGNAL(finished(QNetworkReply*)), this , SLOT(responseReceivedSlot(QNetworkReply*)));

    responseBodyInput = ui->responseBodyInput;
    statusCodeLabel = ui->statusCodeLabel;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest() {
    QUrl url = QUrl(this->urlText);

    auto request = QNetworkRequest(url);
    auto response = this->networkManager->get(request);
}

void MainWindow::responseReceivedSlot(QNetworkReply * response) {
    qDebug() << response->errorString();

    auto error = response->errorString();

    responseBodyInput->setPlainText(error);

    QVariant statusCode = response->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int statusCodeInt = statusCode.toInt();
    QString statusCodeStr = QString::number(statusCodeInt);

    qDebug() << statusCodeStr;

    statusCodeLabel->setText(statusCodeStr);
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
