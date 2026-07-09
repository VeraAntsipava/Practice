#include "mainwindow.h"
#include "tests.h"
#include <QApplication>
#include <iostream> // <- ДОБАВЬ ЭТУ СТРОКУ

int main(int argc, char *argv[]) {
    // 1. Запуск Юнит-тестов QT перед стартом UI
    std::cout << "--- ЗАПУСК ЮНИТ ТЕСТОВ ---" << std::endl;
    AppUnitTest testObject;
    QTest::qExec(&testObject);
    std::cout << "--------------------------\n" << std::endl;

    // 2. Запуск основного кроссплатформенного UI приложения
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
