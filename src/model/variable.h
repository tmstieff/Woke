#ifndef VARIABLE_H
#define VARIABLE_H

#include <QObject>
#include <QString>
#include <qdjango/db/QDjangoModel.h>

class Variable : public QDjangoModel {
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString value READ getValue WRITE setValue)
    Q_PROPERTY(QString type READ getType WRITE setType)
    Q_PROPERTY(QString scope READ getScope WRITE setScope)
    Q_PROPERTY(int scopeId READ getScopeId WRITE setScopeId)

    Q_CLASSINFO("name", "null=false")
    Q_CLASSINFO("scope", "null=false")

  public:
    Variable(QObject *parent = 0);

    QString getName() const;
    void setName(const QString &value);

    QString getValue() const;
    void setValue(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QString getScope() const;
    void setScope(const QString &value);

    int getScopeId() const;
    void setScopeId(int value);

  private:
    QString name;
    QString value;
    QString type;
    QString scope;
    int scopeId;
};

Q_DECLARE_METATYPE(Variable *)

#endif // VARIABLE_H
