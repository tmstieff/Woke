#ifndef PROJECTEDITOR_H
#define PROJECTEDITOR_H

#include <QWidget>

namespace Ui {
class ProjectEditor;
}

class ProjectEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectEditor(QWidget *parent = 0);
    ~ProjectEditor();

private:
    Ui::ProjectEditor *ui;
};

#endif // PROJECTEDITOR_H
