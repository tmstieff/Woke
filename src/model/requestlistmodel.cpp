#include "requestlistmodel.h"

RequestListModel::RequestListModel(QSharedPointer<QList<QSharedPointer<Request>>> requests, QObject *parent)
    : QAbstractListModel(parent) {
    this->requests = requests;
}

int RequestListModel::rowCount(const QModelIndex &parent) const {
    // Supress unused
    (void) parent;

    return this->requests.data()->size();
}

QVariant RequestListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= this->requests.data()->length()) {
        return QVariant();
    }

    Request *request = this->requests.data()->at(index.row()).data();
    if (role == Qt::DisplayRole) {
        return QVariant(request->getVerb() + " " + request->getUri());
    }

    return QVariant();
}
