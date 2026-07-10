
QT += core gui testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 testcase

INCLUDEPATH += \
    src/common \
    src/core \
    src/factory \
    src/presentation \
    src/ui \
    tests

SOURCES += \
    src/main.cpp \
    src/core/core_logic.cpp \
    src/factory/factory.cpp \
    src/presentation/presenter.cpp \
    src/ui/mainwindow.cpp

HEADERS += \
    src/common/interfaces.h \
    src/core/core_logic.h \
    src/factory/factory.h \
    src/presentation/presenter.h \
    src/ui/mainwindow.h \
    tests/tests.h

FORMS += \
    src/ui/mainwindow.ui