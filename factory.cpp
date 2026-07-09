#include "factory.h"
#include "core_logic.h"

std::unique_ptr<IValidator> MathServiceFactory::createValidator() {
    return std::make_unique<BracketValidator>();
}

std::unique_ptr<ICalculator> MathServiceFactory::createCalculator() {
    // Фабрика сама знает, как собрать пирог: берем простой калькулятор и декорируем его логгером!
    auto baseCalc = std::make_unique<SimpleCalculator>();
    return std::make_unique<LoggingCalculator>(std::move(baseCalc));
}