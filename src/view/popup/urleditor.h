#ifndef URLEDITOR_H
#define URLEDITOR_H

#include <QWidget>


namespace Ui {
class UrlEditor;
}

class UrlEditor : public QWidget {
  Q_OBJECT

  public:
    explicit UrlEditor(QWidget *parent = 0);
    ~UrlEditor();

  private:
    Ui::UrlEditor *ui;
};

#endif // URLEDITOR_H
