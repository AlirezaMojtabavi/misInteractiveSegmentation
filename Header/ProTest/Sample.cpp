/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <algorithm>
#include <cctype>
#include <functional>
#include <sstream>

// Include the test framework header.
#include "AccTest.h"

// All framework elements are isolated inside ProTest namespace.
using namespace ProTest;

// Abstract interface for the UI connected to our application under test.

class ICalcUserInterface {
public:
    virtual void SetStatusBar(const std::string& msg) = 0;
    virtual void SetResultContents(const std::string& msg) = 0;
    virtual void SetTitleBar(const std::string& msg) = 0;
    virtual void SetAddButtonCallBack(std::function<void () > callBack) = 0;
    virtual void SetSubtractButtonCallBack(std::function<void () > callBack) = 0;
    virtual std::string GetTextBoxContents() = 0;
    virtual void Close() = 0;
};

// This is the main application to be tested. A pointer to the UI is passed to it during construction. We shall take advantage 
// of this to pass in our own (fake, stub, mock, whatever) version of the UI. This is the only requirement for the application 
// test. Database connections, IO, network, etc could be replaced with simulators or stubs might be used for them as well.

class MyCalcApplication {
public:

    MyCalcApplication(ICalcUserInterface* ui)
    : m_UI(ui) {
        m_UI->SetAddButtonCallBack([this]() {
            Add(); });
        m_UI->SetSubtractButtonCallBack([this]() {
            Subtract(); });
    }

    void StartUp() {
        m_UI->SetTitleBar("My Calculator");
        m_UI->SetStatusBar("Ready");
        m_UI->SetResultContents("0");
    }

    void Exit() {
        m_UI->Close();
    }

private:

    void Add() {
        int value;
        if (!ParseTextBox(value))
            return;

        std::ostringstream output;
        m_CurrentResult += value;
        output << m_CurrentResult;
        m_UI->SetResultContents(output.str());
        m_UI->SetStatusBar("Ready");
    }

    void Subtract() {
        int value;
        if (!ParseTextBox(value))
            return;

        std::ostringstream output;
        m_CurrentResult -= value;
        output << m_CurrentResult;
        m_UI->SetResultContents(output.str());
        m_UI->SetStatusBar("Ready");
    }

    bool ParseTextBox(int& value) {
        auto text = m_UI->GetTextBoxContents();
        if (std::find_if(text.cbegin(), text.cend(), [](char ch) {
                return !std::isdigit(ch); }) != text.cend()) {
        m_UI->SetStatusBar("Error");
        return false;
    }
        std::istringstream input(text);
        input >> value;
        return true;
    }

    int m_CurrentResult = 0;
    ICalcUserInterface* m_UI;
};

// Our fake version of the user interface implementing the same abstract interface but only used in test.

class FakeCaclUserInterface : public ICalcUserInterface {
public:

    void SetAddButtonCallBack(std::function<void () > callBack) override {
        m_AddButtonCallBack = callBack;
    }

    void SetSubtractButtonCallBack(std::function<void () > callBack) override {
        m_SubtractButtonCallBack = callBack;
    }

    std::string GetTextBoxContents() override {
        return m_TextBoxContents;
    }

    void SetStatusBar(const std::string& msg) override {
        m_StatusBar = msg;
    }

    void SetResultContents(const std::string& msg) override {
        m_ResultContents = msg;
    }

    void SetTitleBar(const std::string& msg) override {
        m_TitleBar = msg;
    }

    void Close() override {
        if (m_ExpectedCallsToClose > 0)
            --m_ExpectedCallsToClose;
        else
            throw "Unexpected call to Close()";
    }

    void ExpectClose(int cardinality) {
        m_ExpectedCallsToClose += cardinality;
    }

    bool VerifyExpectedClose() {
        return m_ExpectedCallsToClose == 0;
    }

    std::string m_TitleBar, m_ResultContents, m_StatusBar, m_TextBoxContents;
    std::function<void() > m_AddButtonCallBack, m_SubtractButtonCallBack;

private:
    int m_ExpectedCallsToClose = 0;
};

// The test context is required to hold state of the application, test stubs, and other test related data. It is initialized
// within the test scenario Setup, used and affected by each step, passed on to the next step, and the disposed within the test
// test scenario Teardown.

struct CalcTestContext {
    FakeCaclUserInterface* UI;
    std::shared_ptr<MyCalcApplication> App;
};

// Each step of the test scenario inherits AccTestStep<T> where T is the type serving as our text context.
// Apart from that, every step class will probably need to override the Act() and Verify() methods. Some test steps might also
// need to override Setup(), Expect(), and Teardown(). See AccTestStep for more info.

class TestStepInitAppSetsCorrectUIState : public AccTestStep<CalcTestContext> {
public:

    TestStepInitAppSetsCorrectUIState(const std::string& name)
    : AccTestStep<CalcTestContext>(
    name, "When the app is initialized title bar, status bar, and contents must be set correctly.", false, false) {
    }

    void Act() override {
        auto ctx = GetTestContext();
        ctx->App = std::make_shared<MyCalcApplication>(ctx->UI);
        ctx->App->StartUp();
    }

    void Verify() override {
        auto ui = GetTestContext()->UI;
        ACC_TEST_CHECK_EQUAL(ui->m_TitleBar, "My Calculator");
        ACC_TEST_CHECK_EQUAL(ui->m_StatusBar, "Ready");
        ACC_TEST_CHECK_EQUAL(ui->m_ResultContents, "0");
    }
};

// A parameterized test step: the parameters are passed in through constructor and determined when adding the instance to the 
// scenario. 

class TestStepInput_PressAdd_Status_Result : public AccTestStep<CalcTestContext> {
public:

    TestStepInput_PressAdd_Status_Result(const std::string& testName,
            const std::string& input, const std::string& status, const std::string& result)
    : AccTestStep<CalcTestContext>(testName, CreateDescription(input, status, result), false, false),
    m_Input(input), m_Status(status), m_Result(result) {
    }

    void Act() override {
        auto ui = GetTestContext()->UI;
        ui->m_TextBoxContents = m_Input;
        ui->m_AddButtonCallBack();
    }

    void Verify() override {
        auto ui = GetTestContext()->UI;
        ACC_TEST_CHECK_EQUAL(ui->m_StatusBar, m_Status);
        ACC_TEST_CHECK_EQUAL(ui->m_ResultContents, m_Result);
    }

private:

    static std::string CreateDescription(const std::string& input, const std::string& status, const std::string& result) {
        std::ostringstream desc;
        desc << "When the string \"" << input << "\" is put in and the Add button pressed, status bar must show \"" <<
                status << "\" and the result must show \"" << result << "\".";
        return desc.str();
    }

    std::string m_Input, m_Status, m_Result;
};

// Another test step

class TestStepInput_PressSubtract_Status_Result : public AccTestStep<CalcTestContext> {
public:

    TestStepInput_PressSubtract_Status_Result(const std::string& testName,
            const std::string& input, const std::string& status, const std::string& result)
    : AccTestStep<CalcTestContext>(testName, CreateDescription(input, status, result), false, false),
    m_Input(input), m_Status(status), m_Result(result) {
    }

    void Act() override {
        auto ui = GetTestContext()->UI;
        ui->m_TextBoxContents = m_Input;
        ui->m_SubtractButtonCallBack();
    }

    void Verify() override {
        auto ui = GetTestContext()->UI;
        bool success = ui->m_StatusBar == m_Status && ui->m_ResultContents == m_Result;
        ACC_TEST_CHECK_EQUAL(ui->m_StatusBar, m_Status);
        ACC_TEST_CHECK_EQUAL(ui->m_ResultContents, m_Result);
    }

    static std::string CreateDescription(const std::string& input, const std::string& status, const std::string& result) {
        std::ostringstream desc;
        desc << "When the string \"" << input << "\" is put in and the Subtract button pressed, status bar must show \"" <<
                status << "\" and the result must show \"" << result << "\".";
        return desc.str();
    }

    std::string m_Input, m_Status, m_Result;
};

// Another test step

class TestStepExitingAppMustCloseTheUI : public AccTestStep<CalcTestContext> {
public:

    TestStepExitingAppMustCloseTheUI(const std::string& name)
    : AccTestStep<CalcTestContext>(name, "When close request is sent to the app, "
    "the Close() from user interface must be called once.", false, false) {
    }

    void Expect() override {
        auto ui = GetTestContext()->UI;
        ui->ExpectClose(1);
    }

    void Act() override {
        GetTestContext()->App->Exit();
        GetTestContext()->App = nullptr;
    }

    void Verify() override {
        auto ui = GetTestContext()->UI;
        Check(ui->VerifyExpectedClose()) << "Close not called on the GUI!";
    }
};

// Each test scenario, which is usually composed of many steps, must inherit AccTestScenario. During construction, it must add 
// its respective test steps using AddStep in the same order which they must be run. The test scenario creates the context for you,
// but you need to create the application object and other test stubs. This can be done by overriding Setup(). Make sure to perform
// any clean-ups required within Teardown() by overriding it.

class MyTestScenario : public AccTestScenario<CalcTestContext> {
public:

    MyTestScenario()
    : AccTestScenario<CalcTestContext>("MyTestScenario", "This is the only scenario, at least until now!") {
        CreateStep<TestStepInitAppSetsCorrectUIState>("1_InitApp_MustSet_Status_Result_Title");
        CreateStep<TestStepInput_PressAdd_Status_Result>(
                "2_Input10_Add_Result10_Status_Ready", "10", "Ready", "10");
        CreateStep<TestStepInput_PressAdd_Status_Result>(
                "3_Input20_Add_Result30_Status_Ready", "20", "Ready", "30");
        CreateStep<TestStepInput_PressSubtract_Status_Result>(
                "4_Input15_Subtract_Result15_Status_Ready", "15", "Ready", "15");
        CreateStep<TestStepInput_PressSubtract_Status_Result>(
                "5_Input7_Subtract_Result8_Status_Ready", "7", "Ready", "8");
        CreateStep<TestStepInput_PressAdd_Status_Result>(
                "6_Input52_Add_Result60_Status_Ready", "52", "Ready", "60");
        CreateStep<TestStepInput_PressAdd_Status_Result>(
                "7_Input\"3gsg\"_Add_Result60_Status_Error", "3gsg", "Error", "60");
        CreateStep<TestStepInput_PressSubtract_Status_Result>(
                "8_Input23_Subtract_Result37_Status_Ready", "23", "Ready", "37");
        CreateStep<TestStepInput_PressSubtract_Status_Result>(
                "9_Input\"sdvn8e\"_Subtract_Result8_Status_Ready", "sdvn8e", "Error", "37");
        CreateStep<TestStepInput_PressAdd_Status_Result>(
                "10_Input32_Add_Result69_Status_Ready", "32", "Ready", "69");
        CreateStep<TestStepExitingAppMustCloseTheUI>("11_ExitApp_UIMustBeClosed");
        CreateStep<TestStepInitAppSetsCorrectUIState>("12_InitApp_MustSet_Status_Result_Title");
        // Yes, we can start the app again after exiting! Sure some scenarios work like that; like when you're testing persistence 
        // of app state, you definitely need to exit the app and start it again to see if things stay the same after restarting.
        CreateStep<TestStepInput_PressSubtract_Status_Result>(
                "13_Input-25_Subtract_Result25_Status_Ready", "-25", "Ready", "25");
        // Step 13 will fail because our calculator doesn't accommodate for negative numbers and treats them as non-numerical
        // strings. Therefore, our subsequent steps that count on current app state will probably fail.
        CreateStep<TestStepInput_PressAdd_Status_Result>(
                "14_Input20_Add_Result45_Status_Ready", "20", "Ready", "45");
        CreateStep<TestStepExitingAppMustCloseTheUI>("15_ExitApp_UIMustBeClosed");
    }

    void Setup() override {
        auto ctx = GetTestContext();
        ctx->UI = new FakeCaclUserInterface();
    }

    void Teardown() override {
        auto ctx = GetTestContext();
        delete ctx->UI;
    }

};

// Each test executable must have exactly one test suite. Ours has only one scenario (start to finish).
class MyTestSuite : public AccTestSuite {
public:
    MyTestSuite() {
        CreateScenario<MyTestScenario>();
    }
};

// Use the default main() function. You could also clone macro contents and create your own main() function to customize your test
// application. But why would you want to do that, I don't get it! Anyway, essentially, this inserts a main function that creates 
// an instance of MyTestSuite and passes it to an instance of AccTestRunner. AccTestRunner will take care of your argc and argv.
ACC_TEST_DEFAULT_MAIN_FUNC(MyTestSuite)