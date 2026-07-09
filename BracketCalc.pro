QT       += core gui widgets testlib

CONFIG += c++17

# Имя исполняемого файла
TARGET = BracketCalc
TEMPLATE = app

# Все файлы лежат в одной папке
SOURCES += main.cpp \
           core_logic.cpp \
           factory.cpp \
           presenter.cpp \
           mainwindow.cpp

HEADERS += interfaces.h \
           core_logic.h \
           factory.h \
           interfaces.h \
           presenter.h \
           mainwindow.h \
           tests.h

FORMS   += mainwindow.ui