#pragma once
#include "interfaces.h"
#include <memory>

class MathServiceFactory {
public:
    static std::unique_ptr<IValidator> createValidator();
    static std::unique_ptr<ICalculator> createCalculator();
};