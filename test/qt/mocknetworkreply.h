#ifndef MOCKNETWORKREPLY_H
#define MOCKNETWORKREPLY_H

#include <QNetworkReply>
#include <QByteArray>

class MockNetworkReply : public QNetworkReply {
  public:
    MockNetworkReply();
    void setResponseStatus(int status);
    QString responseData;

  protected:
    qint64 readData(char *data, qint64 maxlen) override;

  public slots:
    void abort() override;
};

#endif // MOCKNETWORKREPLY_H
