#ifndef REQUESTTABBEDEDITOR_H
#define REQUESTTABBEDEDITOR_H

#include "headersyntaxhighlighter.h"
#include "kickpythonsyntaxhighlighter.h"
#include "tabbededitor.h"
#include <QCompleter>
#include <QObject>
#include <QSyntaxHighlighter>
#include <QStringListModel>

class RequestTabbedEditor : public TabbedEditor {
  public:
    explicit RequestTabbedEditor(QWidget *parent);

    void setHeadersData(QSharedPointer<QString> data);
    QSharedPointer<QString> getHeaderData();

    void setPreRequestScriptData(QSharedPointer<QString> data);
    QSharedPointer<QString> getPreRequestScriptData();
};

#endif // REQUESTTABBEDEDITOR_H
