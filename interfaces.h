#pragma once
#include <string>

// Структура для результата проверки скобок
struct ValidationResult {
    bool isValid;
    std::string errorField; // Где ошибка
    std::string suggestion; // Как исправить
};

// Интерфейс Валидатора (Модуль проверки)
class IValidator {
public:
    virtual ~IValidator() = default;
    virtual ValidationResult validate(const std::string& expression) = 0;
};

// Интерфейс Калькулятора (Модуль вычислений)
class ICalculator {
public:
    virtual ~ICalculator() = default;
    virtual double calculate(const std::string& expression) = 0;
};

// Интерфейс для View (UI DP: MVP)
class ICalcView {
public:
    virtual ~ICalcView() = default;
    virtual void showResult(const std::string& result) = 0;
    virtual void showError(const std::string& error, const std::string& suggestion) = 0;
};