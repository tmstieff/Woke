#include "urlplaintextedit.h"

UrlPlainTextEdit::UrlPlainTextEdit(QWidget *parent) : QPlainTextEdit(parent) {
}

void UrlPlainTextEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        this->returnPressed();
    } else {
        QPlainTextEdit::keyPressEvent(event);
    }
}
