#ifndef REQUESTTABBEDEDITOR_H
#define REQUESTTABBEDEDITOR_H

#include "tabbededitor.h"
#include <QObject>

class RequestTabbedEditor : public TabbedEditor {
  public:
    explicit RequestTabbedEditor(QWidget *parent);

    void setHeadersData(QSharedPointer<QString> data);
    QSharedPointer<QString> getHeaderData();

    void setPreRequestScriptData(QSharedPointer<QString> data);
    QSharedPointer<QString> getPreRequestScriptData();
};

#endif // REQUESTTABBEDEDITOR_H
