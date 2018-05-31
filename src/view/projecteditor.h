#ifndef PROJECTEDITOR_H
#define PROJECTEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QSharedPointer>
#include "../model/project.h"

namespace Ui {
class ProjectEditor;
}

class ProjectEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectEditor(QList<QSharedPointer<Project>> &projects, QWidget *parent = 0);
    ~ProjectEditor();

    QPushButton *cancelProjectButton;

private:
    Ui::ProjectEditor *ui;

    QList<QSharedPointer<Project>> projects;
};

#endif // PROJECTEDITOR_H
