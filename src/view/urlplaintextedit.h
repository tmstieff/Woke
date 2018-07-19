#ifndef URLPLAINTEXTEDIT_H
#define URLPLAINTEXTEDIT_H

#include <QKeyEvent>
#include <QPlainTextEdit>

class UrlPlainTextEdit : public QPlainTextEdit {
    Q_OBJECT

  public:
    explicit UrlPlainTextEdit(QWidget *parent);

    void keyPressEvent(QKeyEvent *event) override;
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

  public Q_SLOTS:
  Q_SIGNALS:
    void returnPressed();
    void tabPressed();
    void focusIn();
    void focusOut();
};

#endif // URLPLAINTEXTEDIT_H
