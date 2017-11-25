#ifndef SAVEEDITOR_H
#define SAVEEDITOR_H

#include "../model/request.h"
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

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

    QPushButton *confirmSaveButton;
    QPushButton *cancelSaveButton;
    QPushButton *confirmSaveAsButton;

    QComboBox *projectComboBox;
    QLineEdit *nameEdit;

  private:
    Ui::SaveEditor *ui;
};

#endif // SAVEEDITOR_H
