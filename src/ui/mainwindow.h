#pragma once
#include <QMainWindow>
#include "interfaces.h"
#include "presenter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public ICalcView {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showResult(const std::string& result) override;
    void showError(const std::string& error, const std::string& suggestion) override;

private slots:
    void on_calculateButton_clicked(); //Паттерн Observer

private:
    Ui::MainWindow *ui;
    std::unique_ptr<ExpressionPresenter> presenter;
};