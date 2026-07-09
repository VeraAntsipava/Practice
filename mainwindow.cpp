// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Фиксируем размер для идеальной верстки
    this->setWindowTitle("MathEngine Ultra");
    this->setFixedSize(460, 340);

    presenter = std::make_unique<ExpressionPresenter>(this);

    // Применяем ультра-премиальный QSS-стиль с оранжевым Ambient Glow
    // Применяем ультра-премиальный QSS-стиль с оранжевым Ambient Glow и матовыми кнопками
    // Применяем полностью матовый премиальный QSS-стиль (БЕЗ синих обводок)
    this->setStyleSheet(
        /* 1. Фон окна: глубокий синий + размытая четверть оранжевого круга в углу */
        "#centralwidget {"
        "   background: qradialgradient(cx: 1.0, cy: 0.0, radius: 1.2, fx: 1.0, fy: 0.0, "
        "                               stop: 0.0 rgba(255, 100, 0, 0.25), "
        "                               stop: 0.35 rgba(255, 100, 0, 0.04), "
        "                               stop: 0.65 #0D1326, "
        "                               stop: 1.0 #0A0E1A);"
        "}"

        /* 2. Поле ввода: матовое стекло (БЕЗ синей рамки при клике) */
        "QLineEdit {"
        "   background-color: rgba(255, 255, 255, 0.03);"
        "   border: 1px solid rgba(255, 255, 255, 0.08);" // Тонкая матовая грань по умолчанию
        "   border-radius: 12px;"
        "   padding: 14px 16px;"
        "   color: #FFFFFF;"
        "   font-size: 16px;"
        "   font-family: '-apple-system', 'SF Pro Display', 'Helvetica Neue', sans-serif;"
        "}"
        /* Эффект при клике на поле ввода: мягкое белое свечение вместо синего */
        "QLineEdit:focus {"
        "   border: 1px solid rgba(255, 255, 255, 0.25);" // Граница становится четче и светлее
        "   background-color: rgba(255, 255, 255, 0.06);"  // Стекло внутри слегка светлеет
        "}"

        /* 3. Кнопка: Эффект матового стекла (БЕЗ синей обводки) */
        "QPushButton {"
        "   background-color: rgba(255, 255, 255, 0.06);" // Полупрозрачная матовая дымка
        "   border: 1px solid rgba(255, 255, 255, 0.12);" // Имитация тонкого ребра стекла
        "   border-radius: 12px;"
        "   color: #FFFFFF;"
        "   font-size: 15px;"
        "   font-weight: 600;"
        "   font-family: '-apple-system', 'SF Pro Text', sans-serif;"
        "   padding: 12px;"
        "}"
        /* Эффект при наведении на кнопку */
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 0.12);"  // Матовое стекло наполняется светом
        "   border: 1px solid rgba(255, 255, 255, 0.25);"  // Ребро подсвечивается ярче
        "}"
        /* Эффект при клике на кнопку */
        "QPushButton:pressed {"
        "   background-color: rgba(255, 255, 255, 0.03);"  // Плавное затухание при нажатии
        "   border: 1px solid rgba(255, 255, 255, 0.08);"
        "}"

        /* 4. Общие настройки текста */
        "QLabel {"
        "   font-family: '-apple-system', 'SF Pro Text', sans-serif;"
        "   color: #FFFFFF;"
        "}"

        /* 5. Подложки для вывода результатов и ошибок */
        "#resultLabel, #suggestionLabel {"
        "   background-color: rgba(255, 255, 255, 0.02);"
        "   border: 1px solid rgba(255, 255, 255, 0.04);"
        "   border-radius: 12px;"
        "   padding: 14px;"
        "}"
        );

    // Скрываем виджеты при старте
    ui->resultLabel->hide();
    ui->suggestionLabel->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_calculateButton_clicked() {
    std::string expr = ui->inputLineEdit->text().toStdString();
    presenter->onProcessExpression(expr); // Отправляем в презентер
}

void MainWindow::showResult(const std::string& result) {
    ui->resultLabel->show();

    // Результат крупно и чисто белым цветом
    ui->resultLabel->setText(QString::fromStdString(
        "<div>"
        "  <span style='color: rgba(255, 255, 255, 0.4); font-size: 11px; text-transform: uppercase; letter-spacing: 1px;'>Результат вычислений</span><br>"
        "  <span style='font-size: 24px; font-weight: 700; color: #FFFFFF; font-family: monospace;'> " + result + "</span>"
                   "</div>"
        ));

    ui->suggestionLabel->hide();
}

void MainWindow::showError(const std::string& error, const std::string& suggestion) {
    if (suggestion.empty()) {
        ui->suggestionLabel->hide();
        return;
    }

    ui->suggestionLabel->show();

    // Никакого красного цвета, только минималистичное "Исправлено: " белыми буквами
    ui->suggestionLabel->setText(QString::fromStdString(
        "<div style='font-size: 13px; color: #FFFFFF; font-family: sans-serif;'>"
        "   <span>Исправлено: </span>"
        "   <b style='font-family: monospace; font-size: 14px;'> " + suggestion + "</b>"
                       "</div>"
        ));
}