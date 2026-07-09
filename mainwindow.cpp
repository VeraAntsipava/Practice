// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Проверка скобок и Расчёт");
    presenter = std::make_unique<ExpressionPresenter>(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_calculateButton_clicked() {
    std::string expr = ui->inputLineEdit->text().toStdString();
    presenter->onProcessExpression(expr); // Передаем событие Презентеру
}

void MainWindow::showResult(const std::string& result) {
    ui->resultLabel->setStyleSheet("color: green; font-weight: bold;");
    ui->resultLabel->setText(QString::fromStdString("Успех! Результат: " + result));
    ui->suggestionLabel->clear();
}

void MainWindow::showError(const std::string& error, const std::string& suggestion) {
    ui->resultLabel->setStyleSheet("color: red; font-weight: bold;");
    ui->resultLabel->setText(QString::fromStdString("Ошибка: " + error));
    ui->suggestionLabel->setText(QString::fromStdString("Совет: " + suggestion));
}