#ifndef MAINWINDOW_TEST_H
#define MAINWINDOW_TEST_H

#include <QObject>
#include <QTest>
#include <qdjango/db/QDjango.h>

#include "../src/view/mainwindow.h"

class MainWindow_Test : public MainWindow
{
    Q_OBJECT
private slots:
    void initTestCase();
    void test_sendRequest_valid();
};

#endif // MAINWINDOW_TEST_H
