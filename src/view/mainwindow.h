#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../controller/currentdatacontroller.h"
#include "../controller/historycontroller.h"
#include "../controller/projectcontroller.h"
#include "../controller/pythonscriptcontroller.h"
#include "../controller/requestscontroller.h"
#include "../model/project.h"
#include "../model/requestlistmodel.h"
#include "../urlutil.h"
#include "labelutil.h"
#include "syntax/jsonsyntaxhighlighter.h"
#include "popup/projecteditor.h"
#include "requestitem.h"
#include "requesttabbededitor.h"
#include "responsetabbededitor.h"
#include "popup/saveeditor.h"
#include "popup/urleditor.h"
#include "urlplaintextedit.h"
#include "syntax/urlsyntaxhighlighter.h"
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
    PythonScriptController &pythonScriptController = PythonScriptControllerFactory::getInstance();

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
    ProjectEditor *projectEditor;
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
    void updateCurrentRequestFromFields();

  protected Q_SLOTS:
    void responseReceived(QNetworkReply *response);
    void on_recentRequestsListWidget_activated(const QModelIndex &index);

  private Q_SLOTS:
    void on_sendButton_clicked();
    void on_recentRequestsListWidget_pressed(const QModelIndex &index);
    void on_urlTextMultilineInput_returnPressed();
    void on_urlTextMultilineInput_focusIn();
    void on_urlTextMultilineInput_focusOut();

    void on_saveButton_clicked();
    void on_confirmSaveButton_released();
    void on_confirmSaveAsButton_released();
    void on_cancelSaveButton_released();

    void on_projectsListComboBox_currentIndexChanged(int index);
    void on_projectsRequestsList_clicked(const QModelIndex &index);
    void on_projectsRequestsList_activated(const QModelIndex &index);

    void on_projectEditorButton_released();
    void on_cancelProjectButton_released();
    void on_projectEditor_deleteProject(QString &name);

    void on_saveProjectSuccess(Project &project);

private:
    Ui::MainWindow *ui;

    QSharedPointer<Project> defaultProject;
    QList<QSharedPointer<QPushButton>> responseButtons;

    JsonSyntaxHighlighter *responseBodyHighlighter;
    JsonSyntaxHighlighter *bodyHighlighter;
    UrlSyntaxHighlighter *urlHighlighter;
    QPushButton *projectEditorButton;

    static int currentRequestId;
    static int currentProjectId;

    void setTimeLabel(ResponseInfo responseInfo);
    void setStatusCodeLabel(ResponseInfo responseInfo);
    void setResponseInfo(ResponseInfo responseInfo, QNetworkReply &response);
    void setStylesheetProperty(QWidget &widget, const QString &property, const QString &value);
    void setUiFields(QSharedPointer<Request> request, bool setCurrentRequest);
    void setStatusCodeLabel(QString statusCode);
    void resetResponseFields(const QString &host, const QString &uri, const QString &verb);
    void setResponseInfo(Request &request);
    void showUrlEditor();
    void showSaveEditor();
    void showProjectEditor();
    void showPopup(QWidget &popup, QWidget &button, int offsetX, int offsetY);
    void setCurrentRequest(QSharedPointer<Request> newRequest);
    void refreshProjects();
};

#endif // MAINWINDOW_H
