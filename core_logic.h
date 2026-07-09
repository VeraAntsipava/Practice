#pragma once
#include "interfaces.h"
#include <stack>
#include <memory>

class BracketValidator : public IValidator {
public:
    ValidationResult validate(const std::string& expression) override;
};

// Базовый калькулятор (очень простой, для демонстрации)
class SimpleCalculator : public ICalculator {
public:
    double calculate(const std::string& expression) override;
};

// Паттерн DECORATOR: оборачивает калькулятор и добавляет "логирование/модификацию"
class CalculatorDecorator : public ICalculator {
protected:
    std::unique_ptr<ICalculator> wrappedCalc;
public:
    CalculatorDecorator(std::unique_ptr<ICalculator> calc) : wrappedCalc(std::move(calc)) {}
    double calculate(const std::string& expression) override {
        return wrappedCalc->calculate(expression);
    }
};

// Конкретный декоратор, который выводит информацию в консоль (или можно логировать в файл)
class LoggingCalculator : public CalculatorDecorator {
public:
    LoggingCalculator(std::unique_ptr<ICalculator> calc) : CalculatorDecorator(std::move(calc)) {}
    double calculate(const std::string& expression) override;
};