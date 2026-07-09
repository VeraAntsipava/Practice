#pragma once
#include "interfaces.h"
#include <memory>

class ExpressionPresenter {
private:
    ICalcView* view;
    std::unique_ptr<IValidator> validator;
    std::unique_ptr<ICalculator> calculator;

public:
    ExpressionPresenter(ICalcView* view);
    void onProcessExpression(const std::string& expression);
};