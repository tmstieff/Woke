#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../controller/historycontroller.h"
#include "../controller/requestscontroller.h"
#include "../model/requestlistmodel.h"
#include "../urlutil.h"
#include "jsonsyntaxhighlighter.h"
#include "requestitem.h"
#include "urleditor.h"
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
#include <QPushButton>
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

enum RequestGuiTabs { REQ_HEADERS, REQ_SCRIPT };
enum ResponseGuiTabs { RES_HEADERS, RES_BODY, RES_SCRIPT };

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
    QPlainTextEdit *responseTabsInput;
    QPlainTextEdit *requestTabsInput;
    QPlainTextEdit *bodyInput;
    QLabel *statusCodeLabel;
    QLabel *uriLabel;
    QLabel *timeLabel;
    QLabel *hostLabel;
    QLabel *verbLabel;
    QListWidget *recentRequestsListWidget;
    UrlEditor *urlEditor;

    QSharedPointer<Request> currentRequest;
    QSharedPointer<QList<QSharedPointer<Request>>> recentRequests;

    void refreshRecentRequests();
    void sendRequest();

  protected slots:
    void responseReceivedSlot(QNetworkReply *response);
    void on_recentRequestsListWidget_activated(const QModelIndex &index);

  private slots:
    void on_sendButton_clicked();
    void on_recentRequestsListWidget_pressed(const QModelIndex &index);
    void on_urlTextMultilineInput_returnPressed();
    void on_requestHeadersButton_clicked();
    void on_requestScriptButton_clicked();
    void on_responseHeadersButton_clicked();
    void on_responseBodyButton_clicked();
    void on_responseScriptButton_clicked();
    void on_urlTextMultilineInput_focusIn();
    void on_urlTextMultilineInput_focusOut();

  private:
    Ui::MainWindow *ui;

    RequestGuiTabs currentRequestTab = RequestGuiTabs::REQ_HEADERS;
    ResponseGuiTabs currentResponseTab = ResponseGuiTabs::RES_BODY;

    QList<QSharedPointer<QPushButton>> requestButtons;
    QList<QSharedPointer<QPushButton>> responseButtons;

    JsonSyntaxHighlighter *responseBodyHighlighter;
    JsonSyntaxHighlighter *bodyHighlighter;
    UrlSyntaxHighlighter *urlHighlighter;

    void setTimeLabel(ResponseInfo responseInfo);
    void setStatusCodeLabel(ResponseInfo responseInfo);
    void setResponseTabsInput(ResponseInfo responseInfo, QNetworkReply &response);
    void setStylesheetProperty(QWidget &widget, const QString &property, const QString &value);
    void setUiFields(QSharedPointer<Request> request, bool setCurrentRequest);
    void setStatusCodeLabel(QString statusCode);
    void resetResponseFields(const QString &host, const QString &uri, const QString &verb);
    void setRequestInput(RequestGuiTabs tab);
    void setResponseInput(ResponseGuiTabs tab);
    void setActiveTab(QList<QSharedPointer<QPushButton>> &buttons, int tabIndex);
    void setActiveTabStyle(QPushButton &button);
    void setInactiveTabStyle(QPushButton &button);
    void setResponseTabsInput(Request &request);
    void showUrlEditor();
};

#endif // MAINWINDOW_H
