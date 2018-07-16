cmake_minimum_required(VERSION 3.8)

project(woke_qt)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)
find_library(qdjango-db REQUIRED
        NAMES qdjango-db libqdjango-db)

find_package(PythonInterp 3.6 REQUIRED)
find_package(PythonLibs 3.6 REQUIRED)

find_library(pybind11 REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DQT_NO_KEYWORDS")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/controller/currentdatacontroller.cpp
        src/controller/currentdatacontroller.h
        src/controller/historycontroller.cpp
        src/controller/historycontroller.h
        src/controller/projectcontroller.cpp
        src/controller/projectcontroller.h
        src/controller/pythonscriptcontroller.cpp
        src/controller/pythonscriptcontroller.h
        src/controller/requestscontroller.cpp
        src/controller/requestscontroller.h
        src/controller/variablecontroller.cpp
        src/controller/variablecontroller.h
        src/extension/pybind/qstring_typecaster.h
        src/model/request.cpp
        src/model/request.h
        src/model/requestlistmodel.cpp
        src/model/requestlistmodel.h
        src/model/project.cpp
        src/model/project.h
        src/model/variable.cpp
        src/model/variable.h
        src/view/syntax/jsonsyntaxhighlighter.cpp
        src/view/syntax/jsonsyntaxhighlighter.h
        src/view/syntax/urlsyntaxhighlighter.cpp
        src/view/syntax/urlsyntaxhighlighter.h
        src/view/mainwindow.cpp
        src/view/mainwindow.h
        src/view/requestitem.cpp
        src/view/requestitem.h
        src/view/urlplaintextedit.cpp
        src/view/urlplaintextedit.h
        src/view/tabbededitor.cpp
        src/view/tabbededitor.h
        src/view/requesttabbededitor.cpp
        src/view/requesttabbededitor.h
        src/view/responsetabbededitor.cpp
        src/view/responsetabbededitor.h
        src/view/syntax/kickpythonsyntaxhighlighter.cpp
        src/view/syntax/kickpythonsyntaxhighlighter.h
        src/view/popup/saveeditor.cpp
        src/view/popup/saveeditor.h
        src/view/syntax/headersyntaxhighlighter.cpp
        src/view/syntax/headersyntaxhighlighter.h
        src/view/popup/urleditor.cpp
        src/view/popup/urleditor.h
        src/main.cpp
        src/urlutil.cpp
        src/urlutil.h
        test/view/mainwindow_test.cpp
        test/view/mainwindow_test.h
        test/urlutil_test.cpp
        test/urlutil_test.h
        test/controller/mockrequestscontroller.cpp
        test/controller/mockrequestscontroller.h
        test/controller/pythonscriptcontroller_test.cpp
        test/controller/pythonscriptcontroller_test.h
        test/controller/projectcontroller_test.cpp
        test/controller/projectcontroller_test.h
        test/qt/mocknetworkreply.cpp
        test/qt/mocknetworkreply.h
        test/view/requestitem_test.cpp
        test/view/requestitem_test.h
        mainwindow.ui
        requestitem.ui
        tabbededitor.ui
        saveeditor.ui
        urleditor.ui)

include_directories(build/. build-test/.)
include_directories(/usr/local/include /usr/include/python3.6m)

add_custom_target(qtMakeFile COMMAND make all)

add_executable(woke_qt ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Test Qt5::Sql qdjango-db)