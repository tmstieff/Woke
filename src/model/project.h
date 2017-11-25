#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QObject>
#include <QString>
#include <qdjango/db/QDjangoModel.h>

class Request;

class Project : public QDjangoModel {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)

    Q_CLASSINFO("name", "null=false")

  public:
    explicit Project(QObject *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

  private:
    QString name;
};


#endif // PROJECT_H
