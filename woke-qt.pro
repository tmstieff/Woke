#-------------------------------------------------
#
# Woke project file
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
    src/view/syntax/jsonsyntaxhighlighter.cpp \
    src/view/syntax/urlsyntaxhighlighter.cpp \
    src/view/requestitem.cpp \
    src/view/projectitem.cpp \
    src/controller/requestscontroller.cpp \
    src/view/urlplaintextedit.cpp \
    src/view/popup/urleditor.cpp \
    src/view/tabbededitor.cpp \
    src/view/requesttabbededitor.cpp \
    src/view/responsetabbededitor.cpp \
    src/view/syntax/headersyntaxhighlighter.cpp \
    src/view/popup/saveeditor.cpp \
    src/model/project.cpp \
    src/controller/projectcontroller.cpp \
    src/model/variable.cpp \
    src/controller/variablecontroller.cpp \
    src/controller/pythonscriptcontroller.cpp \
    src/view/syntax/pythonsyntaxhighlighter.cpp \
    src/controller/currentdatacontroller.cpp \
    src/view/syntax/kickpythonsyntaxhighlighter.cpp \
    src/view/popup/projecteditor.cpp \
    src/view/labelutil.cpp

HEADERS += \
    src/controller/historycontroller.h \
    src/urlutil.h \
    src/model/request.h \
    src/model/requestlistmodel.h \
    src/view/mainwindow.h \
    src/view/syntax/jsonsyntaxhighlighter.h \
    src/view/syntax/urlsyntaxhighlighter.h \
    src/view/requestitem.h \
    src/view/projectitem.h \
    src/controller/requestscontroller.h \
    src/view/urlplaintextedit.h \
    src/view/popup/urleditor.h \
    src/view/tabbededitor.h \
    src/view/requesttabbededitor.h \
    src/view/responsetabbededitor.h \
    src/view/syntax/headersyntaxhighlighter.h \
    src/view/popup/saveeditor.h \
    src/model/project.h \
    src/controller/projectcontroller.h \
    src/model/variable.h \
    src/controller/variablecontroller.h \
    src/controller/pythonscriptcontroller.h \
    src/view/syntax/pythonsyntaxhighlighter.h \
    src/extension/pybind/qstring_typecaster.h \
    src/controller/currentdatacontroller.h \
    src/view/syntax/kickpythonsyntaxhighlighter.h \
    src/view/popup/projecteditor.h \
    src/view/labelutil.h

FORMS += mainwindow.ui \
    requestitem.ui \
    urleditor.ui \
    tabbededitor.ui \
    saveeditor.ui \
    projecteditor.ui \
    projectitem.ui

DISTFILES += misc/woke.desktop

win32: LIBS += "$$PWD/qdjango-db0.lib"
win32: LIBS += "$$PWD/Python3.lib"
win32: LIBS += "$$PWD/Python36.lib"

unix: LIBS += -Wl,-rpath,'$ORIGIN'
unix: LIBS += -L/usr/lib/python3.8/config-3.7-x86_64-linux-gnu
unix: LIBS += -lqdjango-db -lpython3.7 -L/usr/lib/python3.7/config-3.7-x86_64-linux-gnu -L/usr/local/lib

unix: INCLUDEPATH += /usr/local/include
unix: INCLUDEPATH += /usr/include/python3.7/

win32: INCLUDEPATH += "C:/Program Files (x86)/pybind11/include/"
win32: INCLUDEPATH += "C:/Program Files (x86)/qdjango/include/"
win32: INCLUDEPATH += "C:/Python36/Include/"

DEPENDPATH += /usr/local/include

CONFIG += c++14
CONFIG += sanitizer address_sanitizer

QMAKE_CXXFLAGS += -fvisibility=hidden -pthread

DEFINES += QDJANGO_SHARED

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

    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"
}

INSTALLS += target

RESOURCES += \
    static_res.qrc

