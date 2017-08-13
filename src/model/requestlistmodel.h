#ifndef REQUESTLISTMODEL_H
#define REQUESTLISTMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QDebug>
#include "request.h"

class RequestListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit RequestListModel(QSharedPointer<QList<QSharedPointer<Request>>> model, QObject *parent);

  int rowCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  QSharedPointer<QList<QSharedPointer<Request>>> requests;
};

#endif // REQUESTLISTMODEL_H
