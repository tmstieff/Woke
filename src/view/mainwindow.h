#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QJsonDocument>
#include <QDebug>
#include <QElapsedTimer>
#include <QListWidget>
#include <QSharedPointer>
#include <QListView>
#include "jsonsyntaxhighlighter.h"
#include "stdlib.h"
#include "../controller/historycontroller.h"
#include "../model/requestlistmodel.h"
#include "requestitem.h"
#include "../urlutil.h"
#include "../controller/requestscontroller.h"
#include <QCompleter>


static const QString DEFAULT_INFO_LABEL_COLOR = "#595b5d";
static const QString BLUE_LABEL = "#445F68";
static const QString RED_LABEL = "#68444D";
static const QString YELLOW_LABEL = "#795C06";
static const QString PURPLE_LABEL = "#412F79";
static const QString GREEN_LABEL = "#3F684A";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    HistoryController historyController;
    RequestsController requestsController;

    QSharedPointer<Request> currentRequest;
    QSharedPointer<QList<QSharedPointer<Request>>> recentRequests;
    QString urlText;
    QString headersText;
    QString verbText;
    QString bodyText;

    void refreshRecentReqests();
    void sendRequest();

protected slots:
    void responseReceivedSlot(QNetworkReply *response);

private slots:
    void on_sendButton_clicked();

    void on_urlTextInput_textChanged(const QString &text);
    void on_urlTextInput_returnPressed();
    void on_verbInput_textChanged(const QString &arg1);
    void on_bodyInput_textChanged();
    void on_headersInput_textChanged();
    void on_verbInput_returnPressed();
    void on_recentRequestsListWidget_activated(const QModelIndex &index);
    void on_recentRequestsListWidget_pressed(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    JsonSyntaxHighlighter *responseBodyHighlighter;
    JsonSyntaxHighlighter *bodyHighlighter;

    QLineEdit *verbInput;
    QLineEdit *urlInput;
    QPlainTextEdit *responseBodyInput;
    QPlainTextEdit *headersInput;
    QPlainTextEdit *bodyInput;
    QLabel *statusCodeLabel;
    QLabel *uriLabel;
    QLabel *timeLabel;
    QLabel *hostLabel;
    QLabel *verbLabel;
    QListWidget *recentRequestsListWidget;

    void setTimeLabel(ResponseInfo responseInfo);
    void setStatusCodeLabel(ResponseInfo responseInfo);
    void setResponseBodyEditor(ResponseInfo responseInfo, QNetworkReply &response);
    void setStylesheetProperty(QWidget &widget, const QString &property, const QString &value);
    void setUiFields(QSharedPointer<Request> request);
    void setStatusCodeLabel(QString statusCode);
};

#endif // MAINWINDOW_H
