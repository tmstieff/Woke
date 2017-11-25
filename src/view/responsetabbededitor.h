#ifndef RESPONSETABBEDEDITOR_H
#define RESPONSETABBEDEDITOR_H

#include "headersyntaxhighlighter.h"
#include "jsonsyntaxhighlighter.h"
#include "kickpythonsyntaxhighlighter.h"
#include "tabbededitor.h"

#include <QObject>
#include <QSyntaxHighlighter>

class ResponseTabbedEditor : public TabbedEditor {
  public:
    explicit ResponseTabbedEditor(QWidget *parent);

    virtual void resetTabData();

    void setHeadersData(QSharedPointer<QString> data);
    QSharedPointer<QString> getHeaderData();

    void setBodyData(QSharedPointer<QString> data);
    QSharedPointer<QString> getBodyData();

    void setPostResponseScriptData(QSharedPointer<QString> data);
    QSharedPointer<QString> getPostResponseScriptData();
};

#endif // RESPONSETABBEDEDITOR_H
