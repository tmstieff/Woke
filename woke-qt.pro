#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08T16:02:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = woke-qt
TEMPLATE = app

SUBDIRS += src
include(src/include.pri)

FORMS    += mainwindow.ui
