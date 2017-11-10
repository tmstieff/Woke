#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../controller/historycontroller.h"
#include "../controller/projectcontroller.h"
#include "../controller/requestscontroller.h"
#include "../model/project.h"
#include "../model/requestlistmodel.h"
#include "../urlutil.h"
#include "jsonsyntaxhighlighter.h"
#include "requestitem.h"
#include "requesttabbededitor.h"
#include "responsetabbededitor.h"
#include "saveeditor.h"
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
    HistoryController *historyController;
    RequestsController *requestsController;
    ProjectController *projectController;

    QLineEdit *verbInput;
    UrlPlainTextEdit *urlInput;
    QPlainTextEdit *bodyInput;
    QLabel *statusCodeLabel;
    QLabel *uriLabel;
    QLabel *timeLabel;
    QLabel *hostLabel;
    QLabel *verbLabel;
    QListWidget *recentRequestsListWidget;
    QListWidget *projectRequestsListWidget;
    UrlEditor *urlEditor;
    SaveEditor *saveEditor;
    RequestTabbedEditor *requestEditor;
    ResponseTabbedEditor *responseEditor;

    QSharedPointer<Request> currentRequest;
    QSharedPointer<QList<QSharedPointer<Request>>> recentRequests;
    QSharedPointer<QList<QSharedPointer<Request>>> projectRequests;
    QSharedPointer<QList<QSharedPointer<Project>>> projects;

    void refreshRecentRequests();
    void refreshProjectRequests();
    void sendRequest();
    void saveCurrentRequestToProject();

  protected slots:
    void responseReceived(QNetworkReply *response);
    void on_recentRequestsListWidget_activated(const QModelIndex &index);

  private slots:
    void on_sendButton_clicked();
    void on_recentRequestsListWidget_pressed(const QModelIndex &index);
    void on_urlTextMultilineInput_returnPressed();
    void on_urlTextMultilineInput_focusIn();
    void on_urlTextMultilineInput_focusOut();

    void on_saveButton_clicked();
    void on_confirmSaveButton_released();
    void on_cancelSaveButton_released();

    void on_projectsListComboBox_currentIndexChanged(int index);

    void on_projectsRequestsList_clicked(const QModelIndex &index);

    void on_projectsRequestsList_activated(const QModelIndex &index);

  private:
    Ui::MainWindow *ui;

    QSharedPointer<Project> defaultProject;
    ResponseGuiTabs currentResponseTab = ResponseGuiTabs::RES_BODY;

    QList<QSharedPointer<QPushButton>> responseButtons;

    JsonSyntaxHighlighter *responseBodyHighlighter;
    JsonSyntaxHighlighter *bodyHighlighter;
    UrlSyntaxHighlighter *urlHighlighter;

    void setTimeLabel(ResponseInfo responseInfo);
    void setStatusCodeLabel(ResponseInfo responseInfo);
    void setResponseInfo(ResponseInfo responseInfo, QNetworkReply &response);
    void setStylesheetProperty(QWidget &widget, const QString &property, const QString &value);
    void setUiFields(QSharedPointer<Request> request, bool setCurrentRequest);
    void setStatusCodeLabel(QString statusCode);
    void resetResponseFields(const QString &host, const QString &uri, const QString &verb);
    void setActiveTabStyle(QPushButton &button);
    void setInactiveTabStyle(QPushButton &button);
    void setResponseInfo(Request &request);
    void showUrlEditor();
    void showSaveEditor();
    void setCurrentRequest(QSharedPointer<Request> newRequest);
};

#endif // MAINWINDOW_H
