#include "presenter.h"
#include "factory.h"
#include <sstream> // Для форматирования чисел без лишних нулей

ExpressionPresenter::ExpressionPresenter(ICalcView* view) : view(view) {
    validator = MathServiceFactory::createValidator();
    calculator = MathServiceFactory::createCalculator();
}

void ExpressionPresenter::onProcessExpression(const std::string& expression) {
    if (expression.empty()) {
        view->showError("Пустая строка", "Введите математическое выражение");
        return;
    }

    // 1 & 2: Считаем в любом случае и форматируем (убираем нули)
    double result = calculator->calculate(expression);
    std::ostringstream oss;
    oss << result;
    std::string resStr = oss.str(); // "15.000000" превращается в "15"

    ValidationResult vRes = validator->validate(expression);

    // Показываем результат в любом случае
    view->showResult(resStr);

    if (!vRes.isValid) {
        // Если есть ошибка в скобках, показываем её и автоисправление
        view->showError(vRes.errorField, vRes.suggestion);
    } else {
        // Если всё чисто, очищаем поле ошибок
        view->showError("", "");
    }
}