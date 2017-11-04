#ifndef RESPONSETABBEDEDITOR_H
#define RESPONSETABBEDEDITOR_H

#include "tabbededitor.h"
#include <QObject>

class ResponseTabbedEditor : public TabbedEditor {
  public:
    explicit ResponseTabbedEditor(QWidget *parent);

    void setHeadersData(QSharedPointer<QString> data);
    QSharedPointer<QString> getHeaderData();

    void setBodyData(QSharedPointer<QString> data);
    QSharedPointer<QString> getBodyData();

    void setPostResponseScriptData(QSharedPointer<QString> data);
    QSharedPointer<QString> getPostResponseScriptData();
};

#endif // RESPONSETABBEDEDITOR_H
