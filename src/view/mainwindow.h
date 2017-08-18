#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../controller/historycontroller.h"
#include "../controller/requestscontroller.h"
#include "../model/requestlistmodel.h"
#include "../urlutil.h"
#include "jsonsyntaxhighlighter.h"
#include "requestitem.h"
#include "urlplaintextedit.h"
#include "urlsyntaxhighlighter.h"
#include <QCompleter>
#include <QDebug>
#include <QElapsedTimer>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QSharedPointer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <cstdlib>

static const QString DEFAULT_INFO_LABEL_COLOR = "#595b5d";
static const QString BLUE_LABEL = "#445F68";
static const QString RED_LABEL = "#68444D";
static const QString YELLOW_LABEL = "#795C06";
static const QString PURPLE_LABEL = "#412F79";
static const QString GREEN_LABEL = "#3F684A";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow() override;

  protected:
    HistoryController historyController;
    RequestsController requestsController;

    QLineEdit *verbInput;
    UrlPlainTextEdit *urlInput;
    QPlainTextEdit *responseBodyInput;
    QPlainTextEdit *headersInput;
    QPlainTextEdit *bodyInput;
    QLabel *statusCodeLabel;
    QLabel *uriLabel;
    QLabel *timeLabel;
    QLabel *hostLabel;
    QLabel *verbLabel;
    QListWidget *recentRequestsListWidget;

    QSharedPointer<Request> currentRequest;
    QSharedPointer<QList<QSharedPointer<Request>>> recentRequests;
    QString urlText;
    QString headersText;
    QString verbText;
    QString bodyText;

    void refreshRecentRequests();

    void sendRequest();

  protected slots:

    void responseReceivedSlot(QNetworkReply *response);

  private slots:

    void on_sendButton_clicked();
    void on_verbInput_textChanged(const QString &arg1);
    void on_bodyInput_textChanged();
    void on_headersInput_textChanged();
    void on_verbInput_returnPressed();
    void on_recentRequestsListWidget_activated(const QModelIndex &index);
    void on_recentRequestsListWidget_pressed(const QModelIndex &index);
    void on_urlTextMultilineInput_textChanged();

    void on_urlTextMultilineInput_returnPressed();

  private:
    Ui::MainWindow *ui;

    JsonSyntaxHighlighter *responseBodyHighlighter;
    JsonSyntaxHighlighter *bodyHighlighter;
    UrlSyntaxHighlighter *urlHighlighter;

    void setTimeLabel(ResponseInfo responseInfo);
    void setStatusCodeLabel(ResponseInfo responseInfo);
    void setResponseBodyEditor(ResponseInfo responseInfo, QNetworkReply &response);
    void setStylesheetProperty(QWidget &widget, const QString &property, const QString &value);
    void setUiFields(QSharedPointer<Request> request);
    void setStatusCodeLabel(QString statusCode);
    void resetResponseFields(const QString &host, const QString &uri, const QString &verb);
};

#endif // MAINWINDOW_H
