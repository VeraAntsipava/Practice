#include "presenter.h"
#include "factory.h"
#include <sstream>

ExpressionPresenter::ExpressionPresenter(ICalcView* view) : view(view) {
    validator = MathServiceFactory::createValidator();
    calculator = MathServiceFactory::createCalculator();
}

void ExpressionPresenter::onProcessExpression(const std::string& expression) {
    if (expression.empty()) {
        view->showError("Пустая строка", "Введите математическое выражение");
        return;
    }


    double result = calculator->calculate(expression);
    std::ostringstream oss;
    oss << result;
    std::string resStr = oss.str(); //нули
    ValidationResult vRes = validator->validate(expression);


    view->showResult(resStr);

    if (!vRes.isValid) {
        view->showError(vRes.errorField, vRes.suggestion);
    } else {
        view->showError("", "");
    }
}