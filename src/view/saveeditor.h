#ifndef SAVEEDITOR_H
#define SAVEEDITOR_H

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
    explicit SaveEditor(QWidget *parent = 0);
    ~SaveEditor();

    void clearFields();

    QPushButton *confirmSaveButton;
    QPushButton *cancelSaveButton;

    QComboBox *projectComboBox;
    QLineEdit *nameEdit;

  private:
    Ui::SaveEditor *ui;
};

#endif // SAVEEDITOR_H
