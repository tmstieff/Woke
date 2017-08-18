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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/controller/historycontroller.cpp
        src/controller/historycontroller.h
        src/controller/requestscontroller.cpp
        src/controller/requestscontroller.h
        src/model/request.cpp
        src/model/request.h
        src/model/requestlistmodel.cpp
        src/model/requestlistmodel.h
        src/view/jsonsyntaxhighlighter.cpp
        src/view/jsonsyntaxhighlighter.h
        src/view/urlsyntaxhighlighter.cpp
        src/view/urlsyntaxhighlighter.h
        src/view/mainwindow.cpp
        src/view/mainwindow.h
        src/view/requestitem.cpp
        src/view/requestitem.h
        src/view/urlplaintextedit.cpp
        src/view/urlplaintextedit.h
        src/main.cpp
        src/urlutil.cpp
        src/urlutil.h
        test/mainwindow_test.cpp
        test/mainwindow_test.h
        test/urlutil_test.cpp
        test/urlutil_test.h
        test/controller/mockrequestscontroller.cpp
        test/controller/mockrequestscontroller.h
        test/qt/mocknetworkreply.cpp
        test/qt/mocknetworkreply.h
        test/view/requestitem_test.cpp
        test/view/requestitem_test.h
        mainwindow.ui
        requestitem.ui)

include_directories(build-debug/. build-test/.)

add_custom_target(qtMakeFile COMMAND make all)

add_executable(woke_qt ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Test Qt5::Sql qdjango-db)