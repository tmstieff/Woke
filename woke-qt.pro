#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08T16:02:22
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = woke-qt
TEMPLATE = app

SUBDIRS += src
include(src/include.pri)

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lqdjango-db
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lqdjango-db
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lqdjango-db

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
