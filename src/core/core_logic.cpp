#include "core_logic.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <cctype>
#include <cmath>


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
                isValid = false;
                if (errorMsg.empty()) errorMsg = "Лишняя закрывающая скобка";
                char expectedOpen = (ch == ')') ? '(' : (ch == ']' ? '[' : '{');
                temp.insert(temp.begin(), expectedOpen);

                for (size_t k = 0; k < openBracketIndices.size(); ++k) {
                    openBracketIndices[k]++;
                }


                temp.push_back(ch);
            } else {
                int lastOpenIdx = openBracketIndices.back();
                char open = temp[lastOpenIdx];
                openBracketIndices.pop_back();

                char expectedClose = (open == '(') ? ')' : (open == '[' ? ']' : '}');

                if (ch != expectedClose) {
                    isValid = false;
                    if (errorMsg.empty()) errorMsg = "Несовпадение типов скобок";
                    temp.push_back(expectedClose);
                } else {
                    temp.push_back(ch);
                }
            }
        } else {
            temp.push_back(ch);
        }
    }


    if (!openBracketIndices.empty()) {
        isValid = false;
        if (errorMsg.empty()) errorMsg = "Не все скобки закрыты";

        for (int i = openBracketIndices.size() - 1; i >= 0; --i) {
            int idx = openBracketIndices[i];
            bool hasContent = false;

            for (size_t k = idx + 1; k < temp.size(); ++k) {
                if (temp[k] != '(' && temp[k] != '[' && temp[k] != '{') {
                    hasContent = true;
                    break;
                }
            }

            if (hasContent) {
                char open = temp[idx];
                temp.push_back((open == '(') ? ')' : (open == '[' ? ']' : '}'));
            } else {
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
    case '/': return (b != 0) ? a / b : 0;
    }
    return 0;
}

double SimpleCalculator::calculate(const std::string& expression) {
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
                        values.push(0);
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

double LoggingCalculator::calculate(const std::string& expression) {
    std::cout << "[LOG]: Начинаем вычисление выражения: " << expression << std::endl;
    double res = CalculatorDecorator::calculate(expression);
    std::cout << "[LOG]: Результат: " << res << std::endl;
    return res;
}