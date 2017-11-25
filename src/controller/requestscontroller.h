#ifndef REQUESTSCONTROLLER_H
#define REQUESTSCONTROLLER_H

#include <QElapsedTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QSharedPointer>

#include "../controller/projectcontroller.h"
#include "../controller/pythonscriptcontroller.h"
#include "../controller/variablecontroller.h"
#include "../model/request.h"
#include "../urlutil.h"

struct ResponseInfo {
    int responseTime;
    int statusCode;
    QString contentType;
};

class RequestsController : public QObject {
  public:
    RequestsController(QObject *parent = 0);

    QSharedPointer<QNetworkAccessManager> networkManager;
    QSharedPointer<VariableController> variableController;

    virtual QSharedPointer<Request> sendRequest(QString &verb, QString &url, QString &headers, QString &body,
                                                QString &prerequestScript, bool saveCurrentRequest,
                                                QSharedPointer<Project> defaultProject, QString &responseScript,
                                                QSharedPointer<Request> existingRequest);
    virtual ResponseInfo handleResponse(QNetworkReply &response);

  private:
    PythonScriptController &pythonScriptController = PythonScriptControllerFactory::getInstance();
    QElapsedTimer responseTimer;
};

#endif // REQUESTSCONTROLLER_H
