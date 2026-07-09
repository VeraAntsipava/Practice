#include "presenter.h"
#include "factory.h"

ExpressionPresenter::ExpressionPresenter(ICalcView* view) : view(view) {
    // Пересекаем границы модулей через фабрику! Напрямую классы логики тут не упоминаются
    validator = MathServiceFactory::createValidator();
    calculator = MathServiceFactory::createCalculator();
}

void ExpressionPresenter::onProcessExpression(const std::string& expression) {
    if (expression.empty()) {
        view->showError("Пустая строка", "Введите математическое выражение");
        return;
    }

    ValidationResult vRes = validator->validate(expression);
    if (!vRes.isValid) {
        view->showError(vRes.errorField, vRes.suggestion);
    } else {
        double result = calculator->calculate(expression);
        view->showResult(std::to_string(result));
    }
}