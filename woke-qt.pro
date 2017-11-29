#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08T16:02:22
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += no_keywords

TARGET = woke
TEMPLATE = app

SUBDIRS += src

SOURCES += src/main.cpp \
    src/controller/historycontroller.cpp \
    src/urlutil.cpp \
    src/model/request.cpp \
    src/model/requestlistmodel.cpp \
    src/view/mainwindow.cpp \
    src/view/jsonsyntaxhighlighter.cpp \
    src/view/urlsyntaxhighlighter.cpp \
    src/view/requestitem.cpp \
    src/controller/requestscontroller.cpp \
    src/view/urlplaintextedit.cpp \
    src/view/urleditor.cpp \
    src/view/tabbededitor.cpp \
    src/view/requesttabbededitor.cpp \
    src/view/responsetabbededitor.cpp \
    src/view/headersyntaxhighlighter.cpp \
    src/view/saveeditor.cpp \
    src/model/project.cpp \
    src/controller/projectcontroller.cpp \
    src/model/variable.cpp \
    src/controller/variablecontroller.cpp \
    src/controller/pythonscriptcontroller.cpp \
    src/view/pythonsyntaxhighlighter.cpp \
    src/controller/currentdatacontroller.cpp \
    src/view/kickpythonsyntaxhighlighter.cpp

HEADERS += \
    src/controller/historycontroller.h \
    src/urlutil.h \
    src/model/request.h \
    src/model/requestlistmodel.h \
    src/view/mainwindow.h \
    src/view/jsonsyntaxhighlighter.h \
    src/view/urlsyntaxhighlighter.h \
    src/view/requestitem.h \
    src/controller/requestscontroller.h \
    src/view/urlplaintextedit.h \
    src/view/urleditor.h \
    src/view/tabbededitor.h \
    src/view/requesttabbededitor.h \
    src/view/responsetabbededitor.h \
    src/view/headersyntaxhighlighter.h \
    src/view/saveeditor.h \
    src/model/project.h \
    src/controller/projectcontroller.h \
    src/model/variable.h \
    src/controller/variablecontroller.h \
    src/controller/pythonscriptcontroller.h \
    src/view/pythonsyntaxhighlighter.h \
    src/extension/pybind/qstring_typecaster.h \
    src/controller/currentdatacontroller.h \
    src/view/kickpythonsyntaxhighlighter.h

FORMS += mainwindow.ui \
    requestitem.ui \
    urleditor.ui \
    tabbededitor.ui \
    saveeditor.ui

DISTFILES += misc/woke.desktop

win32: LIBS += "$$PWD/qdjango-db0.dll"
win32: LIBS += "$$PWD/python.dll"
unix: LIBS += -lqdjango-db -lpython3.5m

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/include/python3.5m/

win32: INCLUDEPATH += "C:/Program Files (x86)/pybind11/include/"
win32: INCLUDEPATH += "C:/Python36/Include/"

DEPENDPATH += /usr/local/include

test {
    message(Test build)

    QT += testlib
    TARGET = woke-test

    SOURCES -= src/main.cpp

    HEADERS += \
        test/urlutil_test.h \
        test/view/mainwindow_test.h \
        test/view/requestitem_test.h \
        test/controller/mockrequestscontroller.h \
        test/qt/mocknetworkreply.h \
        test/testutils.h \
        test/view/tabbededitor_test.h \
        test/controller/historycontroller_test.h \
        test/controller/projectcontroller_test.h \
        test/controller/pythonscriptcontroller_test.h \
        test/controller/variablecontroller_test.h

    SOURCES += \
        test/test_main.cpp \
        test/urlutil_test.cpp \
        test/view/requestitem_test.cpp \
        test/view/mainwindow_test.cpp \
        test/controller/mockrequestscontroller.cpp \
        test/qt/mocknetworkreply.cpp \
        test/testutils.cpp \
        test/view/tabbededitor_test.cpp \
        test/controller/historycontroller_test.cpp \
        test/controller/projectcontroller_test.cpp \
        test/controller/pythonscriptcontroller_test.cpp \
        test/controller/variablecontroller_test.cpp

} else  {
    message(Normal build)
}

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    target.path = $$PREFIX/bin

    shortcutfiles.files = misc/woke.desktop
    shortcutfiles.path = $$PREFIX/share/applications/

    INSTALLS += shortcutfiles
}

INSTALLS += target

RESOURCES += \
    static_res.qrc

