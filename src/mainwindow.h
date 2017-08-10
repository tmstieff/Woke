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
#include "jsonsyntaxhighlighter.h"
#include "stdlib.h"


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

private:
    void sendRequest();
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

    QString urlText;
    QString headersText;
    QString verbText;
    QString bodyText;
    QNetworkAccessManager *networkManager;
};

#endif // MAINWINDOW_H
