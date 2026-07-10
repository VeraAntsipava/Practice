#include "mainwindow.h"
#include "tests.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "ТЕСТЫ" << std::endl;
    AppUnitTest testObject;
    QTest::qExec(&testObject);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
