#ifndef URLPLAINTEXTEDIT_H
#define URLPLAINTEXTEDIT_H

#include <QKeyEvent>
#include <QPlainTextEdit>

class UrlPlainTextEdit : public QPlainTextEdit {
    Q_OBJECT

  public:
    UrlPlainTextEdit(QWidget *parent);

    void keyPressEvent(QKeyEvent *event);

  public slots:
  Q_SIGNALS:
    void returnPressed();
};

#endif // URLPLAINTEXTEDIT_H
