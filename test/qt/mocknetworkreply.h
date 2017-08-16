#ifndef MOCKNETWORKREPLY_H
#define MOCKNETWORKREPLY_H

#include <QNetworkReply>


class MockNetworkReply : public QNetworkReply
{
public:
    MockNetworkReply();

protected:
    qint64 readData(char *data, qint64 maxlen);

public slots:
    void abort();
};

#endif // MOCKNETWORKREPLY_H
