#-------------------------------------------------
#
# Project created by QtCreator 2017-07-31T17:37:35
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        glwidget.cpp \
        parser/parser.cc \
        parser/print.cc \
        parser/simplify.cc \
        expression/expression.cc \
        renderable.cpp \
    expression/linearspan.cpp \
    expression/evaluator.cpp

HEADERS  += mainwindow.h \
         glwidget.h \
         parser/parser.h \
         parser/print.h \
         parser/simplify.h \
         renderable.h \
         expression/expression.h \
         renderable.h \
    expression/linearspan.h \
    expression/evaluator.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc


CONFIG   += c++14
