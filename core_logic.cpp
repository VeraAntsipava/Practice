#include "core_logic.h"
#include <iostream>
#include <sstream>

ValidationResult BracketValidator::validate(const std::string& expression) {
    std::stack<std::pair<char, int>> s;

    for (int i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push({ch, i});
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.empty()) {
                return {false, "Лишняя закрывающая скобка", "Удалите скобку '" + std::string(1, ch) + "' на позиции " + std::to_string(i+1)};
            }
            char open = s.top().first;
            if ((ch == ')' && open != '(') || (ch == ']' && open != '[') || (ch == '}' && open != '{')) {
                return {false, "Несовпадение типов скобок", "Замените '" + std::string(1, ch) + "' на позиции " + std::to_string(i+1) + " на подходящую закрывающую"};
            }
            s.pop();
        }
    }

    if (!s.empty()) {
        return {false, "Не все скобки закрыты", "Добавьте закрывающую скобку для '" + std::string(1, s.top().first) + "' с позиции " + std::to_string(s.top().second + 1)};
    }

    return {true, "", ""};
}

// Упрощенный парсер для демонстрации архитектуры (считает только простые + и -)
double SimpleCalculator::calculate(const std::string& expression) {
    std::string cleanExpr = "";
    for(char c : expression) {
        if(c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}') cleanExpr += c;
    }
    std::stringstream ss(cleanExpr);
    double total = 0;
    double num;
    if (ss >> total) {
        char op;
        while (ss >> op >> num) {
            if (op == '+') total += num;
            if (op == '-') total -= num;
        }
    }
    return total;
}

double LoggingCalculator::calculate(const std::string& expression) {
    std::cout << "[LOG]: Начинаем вычисление выражения: " << expression << std::endl;
    double res = CalculatorDecorator::calculate(expression);
    std::cout << "[LOG]: Результат: " << res << std::endl;
    return res;
}