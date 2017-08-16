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

SOURCES += src/main.cpp \
    src/controller/historycontroller.cpp \
    src/urlutil.cpp \
    src/model/request.cpp \
    src/model/requestlistmodel.cpp \
    src/view/mainwindow.cpp \
    src/view/jsonsyntaxhighlighter.cpp \
    src/view/requestitem.cpp \
    src/controller/requestscontroller.cpp

HEADERS += \
    src/controller/historycontroller.h \
    src/urlutil.h \
    src/model/request.h \
    src/model/requestlistmodel.h \
    src/view/mainwindow.h \
    src/view/jsonsyntaxhighlighter.h \
    src/view/requestitem.h \
    src/controller/requestscontroller.h

#include(src/include.pri)

FORMS    += mainwindow.ui \
    requestitem.ui

unix|win32: LIBS += -lqdjango-db

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

test {
    message(Test build)

    QT += testlib
    TARGET = woke-qt-test

    SOURCES -= src/main.cpp

    HEADERS += \
        test/urlutil_test.h \
        test/mainwindow_test.h \
        test/view/requestitem_test.h \
        test/controller/mockrequestscontroller.h \
        test/qt/mocknetworkreply.h

    SOURCES += \
        test/test_main.cpp \
        test/urlutil_test.cpp \
        test/view/requestitem_test.cpp \
        test/mainwindow_test.cpp \
        test/controller/mockrequestscontroller.cpp \
        test/qt/mocknetworkreply.cpp

} else  {
    message(Normal build)
}
