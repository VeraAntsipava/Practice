#pragma once
#include <string>

struct ValidationResult {
    bool isValid;
    std::string errorField;
    std::string suggestion;
};

class IValidator {
public:
    virtual ~IValidator() = default;
    virtual ValidationResult validate(const std::string& expression) = 0;
};

class ICalculator {
public:
    virtual ~ICalculator() = default;
    virtual double calculate(const std::string& expression) = 0;
};

class ICalcView {
public:
    virtual ~ICalcView() = default;
    virtual void showResult(const std::string& result) = 0;
    virtual void showError(const std::string& error, const std::string& suggestion) = 0;
};