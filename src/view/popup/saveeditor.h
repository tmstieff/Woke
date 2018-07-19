#ifndef SAVEEDITOR_H
#define SAVEEDITOR_H

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSharedPointer>
#include <QWidget>
#include "../../model/request.h"

namespace Ui {
class SaveEditor;
}

class SaveEditor : public QWidget {
    Q_OBJECT

  public:
    explicit SaveEditor(QWidget *parent = nullptr);
    ~SaveEditor() override;

    void clearFields();
    void updateFields(Request &request);
    void refreshProjects(QList<QSharedPointer<Project>> &projects);

    QPushButton *confirmSaveButton;
    QPushButton *cancelSaveButton;
    QPushButton *confirmSaveAsButton;

    QLineEdit *nameEdit;
    int getSelectedProject();

    QComboBox *projectComboBox;

  private:
    Ui::SaveEditor *ui;

};

#endif // SAVEEDITOR_H
