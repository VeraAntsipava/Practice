#include "core_logic.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <cctype>
#include <cmath>

// ============================================================================
// 1. РЕАЛИЗАЦИЯ ВАЛИДАТОРА (Умное автоисправление скобок на лету)
// ============================================================================
ValidationResult BracketValidator::validate(const std::string& expression) {
    std::vector<char> temp;
    std::vector<int> openBracketIndices;
    bool isValid = true;
    std::string errorMsg = "";

    for (int i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            openBracketIndices.push_back(temp.size());
            temp.push_back(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (openBracketIndices.empty()) {
                // СЛУЧАЙ 12+3): Обнаружена лишняя закрывающая скобка
                isValid = false;
                if (errorMsg.empty()) errorMsg = "Лишняя закрывающая скобка";

                // Вместо удаления, балансируем выражение: вставляем открывающую пару в начало строки
                char expectedOpen = (ch == ')') ? '(' : (ch == ']' ? '[' : '{');
                temp.insert(temp.begin(), expectedOpen);

                // КРИТИЧЕСКИ ВАЖНО: Так как мы вставили символ в начало,
                // все сохраненные индексы открытых скобок в векторе сдвинулись на +1
                for (size_t k = 0; k < openBracketIndices.size(); ++k) {
                    openBracketIndices[k]++;
                }

                // Теперь спокойно добавляем саму закрывающую скобку в текущую позицию
                temp.push_back(ch);
            } else {
                int lastOpenIdx = openBracketIndices.back();
                char open = temp[lastOpenIdx];
                openBracketIndices.pop_back();

                char expectedClose = (open == '(') ? ')' : (open == '[' ? ']' : '}');

                if (ch != expectedClose) {
                    isValid = false;
                    if (errorMsg.empty()) errorMsg = "Несовпадение типов скобок";
                    temp.push_back(expectedClose); // Заменяем на правильную пару
                } else {
                    temp.push_back(ch);
                }
            }
        } else {
            temp.push_back(ch);
        }
    }

    // Обработка незакрытых скобок в конце строки (например, 12+3( или (12+3 )
    if (!openBracketIndices.empty()) {
        isValid = false;
        if (errorMsg.empty()) errorMsg = "Не все скобки закрыты";

        // Идем с конца вектора индексов, чтобы безопасно удалять/добавлять элементы
        for (int i = openBracketIndices.size() - 1; i >= 0; --i) {
            int idx = openBracketIndices[i];
            bool hasContent = false;

            // Проверяем, есть ли какой-то полезный текст/числа после этой скобки
            for (size_t k = idx + 1; k < temp.size(); ++k) {
                if (temp[k] != '(' && temp[k] != '[' && temp[k] != '{') {
                    hasContent = true;
                    break;
                }
            }

            if (hasContent) {
                // Если внутри что-то есть (например, "(12+3"), добавляем закрывающую в конец
                char open = temp[idx];
                temp.push_back((open == '(') ? ')' : (open == '[' ? ']' : '}'));
            } else {
                // Если она пустая на самом конце (например, "12+3("), просто стираем её
                temp.erase(temp.begin() + idx);
            }
        }
    }

    std::string corrected(temp.begin(), temp.end());

    if (isValid) {
        return {true, "", ""};
    }
    return {false, errorMsg, corrected};
}

// ============================================================================
// 2. РЕАЛИЗАЦИЯ КАЛЬКУЛЯТОРА (Алгоритм Дейкстры / ОПЗ)
// ============================================================================

static int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

static double applyOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return (b != 0) ? a / b : 0; // Защита от деления на 0
    }
    return 0;
}

double SimpleCalculator::calculate(const std::string& expression) {
    // Нормализация строки (приводим все скобки к круглым, убираем пробелы)
    std::string expr = "";
    for (char c : expression) {
        if (c == '[' || c == '{') expr += '(';
        else if (c == ']' || c == '}') expr += ')';
        else if (!isspace(c)) expr += c;
    }

    std::stack<double> values;
    std::stack<char> ops;

    for (size_t i = 0; i < expr.length(); i++) {
        if (isdigit(expr[i]) || expr[i] == '.') {
            std::string valStr = "";
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                valStr += expr[i];
                i++;
            }
            i--;
            try {
                values.push(std::stod(valStr));
            } catch (...) {
                values.push(0);
            }
        }
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                if (values.size() < 2) break;
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            if (!ops.empty() && ops.top() == '(') ops.pop();
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            // Проверка на унарный плюс/минус
            if (expr[i] == '-' || expr[i] == '+') {
                bool isUnary = false;
                if (i == 0) isUnary = true;
                else {
                    char prev = expr[i - 1];
                    if (prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '(') {
                        isUnary = true;
                    }
                }
                if (isUnary) {
                    if (expr[i] == '-') {
                        values.push(0); // Превращаем "-X" в "0 - X"
                    } else {
                        continue;
                    }
                }
            }

            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expr[i])) {
                if (values.size() < 2) break;
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) {
        if (ops.top() == '(') {
            ops.pop();
            continue;
        }
        if (values.size() < 2) break;
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperation(val1, val2, op));
    }

    return values.empty() ? 0 : values.top();
}

// ============================================================================
// 3. РЕАЛИЗАЦИЯ ДЕКОРАТОРА (Логирование)
// ============================================================================
double LoggingCalculator::calculate(const std::string& expression) {
    std::cout << "[LOG]: Начинаем вычисление выражения: " << expression << std::endl;
    double res = CalculatorDecorator::calculate(expression);
    std::cout << "[LOG]: Результат: " << res << std::endl;
    return res;
}