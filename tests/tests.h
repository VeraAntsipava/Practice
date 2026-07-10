#pragma once
#include <QtTest/QtTest>
#include "interfaces.h"
#include "presenter.h"
#include "core_logic.h"

//Ручной MOCK-объект
class MockView : public ICalcView {
public:
    bool showResultCalled = false;
    bool showErrorCalled = false;
    std::string lastResult = "";
    std::string lastError = "";
    std::string lastSuggestion = "";

    void showResult(const std::string& result) override {
        showResultCalled = true;
        lastResult = result;
    }
    void showError(const std::string& error, const std::string& suggestion) override {
        showErrorCalled = true;
        lastError = error;
        lastSuggestion = suggestion;
    }

    void reset() {
        showResultCalled = false;
        showErrorCalled = false;
        lastResult = "";
        lastError = "";
        lastSuggestion = "";
    }
};


class AppUnitTest : public QObject {
    Q_OBJECT

private slots:
    //Тест валидатора
    void testValidBrackets() {
        BracketValidator validator;
        QVERIFY(validator.validate("(2+3)*[5-2]").isValid == true);

        auto res = validator.validate("(2+3");
        QVERIFY(res.isValid == false);
        QCOMPARE(res.errorField.c_str(), "Не все скобки закрыты");
    }

    //Тест связки
    void testPresenterWithMock() {
        MockView mockView;
        ExpressionPresenter presenter(&mockView);

        //Правильное выражение
        presenter.onProcessExpression("(10+5)-2");
        QVERIFY(mockView.showResultCalled == true);
        QCOMPARE(mockView.lastResult.c_str(), "13");

        mockView.reset();

        //Ошибка в скобках
        presenter.onProcessExpression("((1+2)");
        QVERIFY(mockView.showErrorCalled == true);
       // QVERIFY(mockView.showResultCalled == false);
    }
};