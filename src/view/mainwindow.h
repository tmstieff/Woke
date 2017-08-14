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

const QString DEFAULT_INFO_LABEL_COLOR = "#595b5d";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void on_urlTextInput_textChanged(const QString &text);
    void responseReceivedSlot(QNetworkReply *response);

    void on_urlTextInput_returnPressed();

    void on_verbInput_textChanged(const QString &arg1);

    void on_bodyInput_textChanged();

    void on_headersInput_textChanged();

    void on_verbInput_returnPressed();

    void on_recentRequestsListWidget_activated(const QModelIndex &index);

    void on_recentRequestsListWidget_pressed(const QModelIndex &index);

private:
    void sendRequest();
    Ui::MainWindow *ui;

    HistoryController historyController;

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

    QElapsedTimer responseTimer;
    QString urlText;
    QString headersText;
    QString verbText;
    QString bodyText;
    QNetworkAccessManager *networkManager;
    QSharedPointer<QList<QSharedPointer<Request>>> recentRequests;
    Request *currentRequest;

    void setTimeLabel();
    void setStatusCodeLabel(QNetworkReply &response);
    void setResponseBodyEditor(QNetworkReply &response);
    void setStylesheetProperty(QWidget &widget, const QString &property, const QString &value);
    void setUi(QSharedPointer<Request> request);
    void refreshRecentReqests();
};

#endif // MAINWINDOW_H
