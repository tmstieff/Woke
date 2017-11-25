#ifndef MOCKNETWORKREPLY_H
#define MOCKNETWORKREPLY_H

#include <QByteArray>
#include <QNetworkReply>

class MockNetworkReply : public QNetworkReply {
  public:
    MockNetworkReply();
    void setResponseStatus(int status);
    QString responseData;

  protected:
    qint64 readData(char *data, qint64 maxlen) override;

  public Q_SLOTS:
    void abort() override;
};

#endif // MOCKNETWORKREPLY_H
