#ifndef REQUEST_H
#define REQUEST_H

#include <QDebug>
#include <qdjango/db/QDjangoModel.h>

class Request : public QDjangoModel {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString proto READ getProto WRITE setProto)
    Q_PROPERTY(QString host READ getHost WRITE setHost)
    Q_PROPERTY(QString uri READ getUri WRITE setUri)
    Q_PROPERTY(QString statusCode READ getStatusCode WRITE setStatusCode)
    Q_PROPERTY(int time READ getTime WRITE setTime)
    Q_PROPERTY(QString requestHeaders READ getRequestHeaders WRITE setRequestHeaders)
    Q_PROPERTY(QString requestBody READ getRequestBody WRITE setRequestBody)
    Q_PROPERTY(QString requestScript READ getRequestScript WRITE setRequestScript)
    Q_PROPERTY(QString verb READ getVerb WRITE setVerb)
    Q_PROPERTY(QString responseHeaders READ getResponseHeaders WRITE setResponseHeaders)
    Q_PROPERTY(QString responseContentType READ getResponseContentType WRITE setResponseContentType)
    Q_PROPERTY(QString responseBody READ getResponseBody WRITE setResponseBody)
    Q_PROPERTY(QString responseScript READ getResponseScript WRITE setResponseScript)

  public:
    Request();

    QString getName() const;
    void setName(const QString &name);

    QString getHost() const;
    void setHost(const QString &host);

    QString getProto() const;
    void setProto(const QString &proto);

    QString getUri() const;
    void setUri(const QString &value);

    QString getStatusCode() const;
    void setStatusCode(const QString &value);

    int getTime() const;
    void setTime(int value);

    QString getRequestHeaders() const;
    void setRequestHeaders(const QString &value);

    QString getRequestBody() const;
    void setRequestBody(const QString &value);

    QString getVerb() const;
    void setVerb(const QString &value);

    QString getResponseHeaders() const;
    void setResponseHeaders(const QString &value);

    QString getResponseBody() const;
    void setResponseBody(const QString &value);

  private:
    QString name;
    QString proto;
    QString host;
    QString uri;
    QString statusCode;
    int time;
    QString requestHeaders;
    QString requestBody;
    QString requestScript;
  public:
    const QString &getRequestScript() const;
    void setRequestScript(const QString &requestScript);
    const QString &getResponseScript() const;
    void setResponseScript(const QString &responseScript);
  private:
    QString verb;
    QString responseHeaders;
    QString responseBody;
    QString responseScript;
    QString responseContentType;
  public:
    const QString &getResponseContentType() const;
    void setResponseContentType(const QString &responseContentType);
};

#endif // REQUEST_H
