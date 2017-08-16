#ifndef REQUESTITEM_H
#define REQUESTITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class RequestItem;
}

class RequestItem : public QWidget
{
    Q_OBJECT

public:
    explicit RequestItem(QWidget *parent = 0);
    void setInformation(QString verb, QString uri, QString url);
    QString getVerb();
    QString getUri();
    QString getUrl();
    ~RequestItem();

private:
    QLabel *urlLabel;
    QLabel *uriLabel;
    QLabel *verbLabel;

    Ui::RequestItem *ui;
};

#endif // REQUESTITEM_H
