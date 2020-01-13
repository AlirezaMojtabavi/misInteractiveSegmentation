//    MIT License
//
//    Copyright (c) 2017 Muhammad Ismail Soboute
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the "Software"), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//    SOFTWARE.

#ifndef __ACC_TEST_H__
#define __ACC_TEST_H__

#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ProTest {

    template <class T> class AccTestStep;
    template <class T> class AccTestScenario;

    // The abstract interface for observing status and progress of the test execution through scenarios and steps. During 
    // execution of the test suite, an instance of this class is passed to the test suite and each scenario and they use 
    // the instance to log test execution events.

    class AccTestObserverIface {
    public:
        virtual void StartingTestSuite(std::size_t numberOfTestScenarios) = 0;
        virtual void StartingScenario(const std::string& name, const std::string& description, std::size_t numberOfSteps) = 0;
        virtual void ExceptionInScenario() = 0;
        virtual void StartingScenarioSetup() = 0;
        virtual void ScenarioTerminated() = 0;
        virtual void RunningScenarioTeardown() = 0;
        virtual void StartingScenarioStep(const std::string& name, const std::string& description) = 0;
        virtual void ExecutingStepSetup() = 0;
        virtual void RunningStepExpectations() = 0;
        virtual void StartingStepAct() = 0;
        virtual void StepExceptionExpectationNotMet(bool didThrow) = 0;
        virtual void StartingStepVerification() = 0;
        virtual void FinishedStepVerification(bool passed) = 0;
        virtual void StepVerificationFailed(const std::map<int, std::string>& failedCheckOutputs) = 0;
        virtual void ExecutingStepTeardown() = 0;
        virtual void FinishedScenario() = 0;
        virtual void FinishedTestSuite() = 0;
    };

    // Each test step must inherit AccTestStep and override one or more of the virtual methods. Your derived constructor must 
    // the base constructor and give it the name, description, and the flags isRequired and mustThrow. Turning isRequired on for 
    // test step means that its success is essential for proceeding to subsequent steps. If a required test step fails, all 
    // subsequent steps will be omitted. Turning on the mustThrow flag means that the executing the step Action must throw an 
    // exception. If this flag is raised but the action doesn't throw, the step fails. 
    // You will almost certainly want to override the Act() method. This is where the action happens - some 
    // message is sent to the application, an event is raised, etc. Just make that your implementation of Act() calls SetActed() 
    // at the end.
    // If you are using mock objects in your test, you should override Expect() and put your expectations there. But don't forget
    // to verify them in Verify().
    // You will also, almost very certainly, want to override Verify() to see if the action has had the expected effect on the 
    // context - otherwise, what's the point of testing! If you are using mock objects in your context, make sure to verify all the
    // expectations or reset them before the context is handed over to the unsuspecting next step. Use the protected Check() 
    // method within your Verify() implementation to check if a certain condition is met. If the condition is true the test step is 
    // considered passed. If one of the Check invocations within the test step is given a false value, the whole step is considered
    // failed. You can pass data to the return value from the Check() calls. This data will be sent to the output if the check 
    // should fail.
    // If you need somewhere to initialize the context before running the step, you will need to override Setup(). The finalizing
    // counterpart is, of course, Teardown().

    template <typename T>
    class AccTestStep {
    public:
        typedef T TestContextType;

        AccTestStep(const std::string& name, const std::string& description, bool isRequired = false, bool mustThrow = false)
        : m_Name(name), m_Description(description), m_IsRequired(isRequired), m_MustThrow(mustThrow) {
        }

        virtual void Setup() {
        }

        virtual void Expect() {
        }

        virtual void Act() {
        }

        virtual void Verify() {
            Check(true);
        }

        virtual void Teardown() {
        }

        void SetContext(TestContextType* context) {
            m_Context = context;
        }

        bool Passed() {
            return m_Passed;
        }

        bool IsVerified() {
            return m_IsVerified;
        }

        bool MustThrow() {
            return m_MustThrow;
        }

        bool IsRequired() {
            return m_IsRequired;
        }

        std::string GetName() {
            return m_Name;
        }

        std::string GetDescription() {
            return m_Description;
        }

        std::map<int, std::string> GetCheckOutputs() {
            std::map<int, std::string> outputs;
            for (const auto& strm : m_CheckOutputs)
                outputs[strm.first] = strm.second.str();
            return outputs;
        }

    protected:

        TestContextType* GetTestContext() {
            return m_Context;
        }

        std::ostream& Check(bool predicate) {
            m_Passed = m_CheckCounter > 0 ? m_Passed && predicate : predicate;
            m_IsVerified = true;
            m_CheckCounter++;
            return predicate ? m_SuccessCheckOutput : m_CheckOutputs[m_CheckCounter];
        }

    private:
        bool m_IsVerified = false;
        bool m_IsRequired = false;
        bool m_MustThrow = false;
        bool m_Passed = false;
        std::string m_Name = "NOT SET";
        std::string m_Description = "NOT SET";
        TestContextType* m_Context = nullptr;
        std::map<int, std::ostringstream> m_CheckOutputs;
        std::ostringstream m_SuccessCheckOutput;
        int m_CheckCounter = 0;
    };

    // Provides a base for all scenario classes so they can be aggregated within the test suite and run polymorphically.

    class AccTestScenarioBase {
    public:

        AccTestScenarioBase(const std::string& name, const std::string& description)
        : m_Name(name), m_Description(description) {
        }

        virtual void Run(const std::shared_ptr<AccTestObserverIface>& testObserver) = 0;

        std::string GetName() {
            return m_Name;
        }

        std::string GetDescription() {
            return m_Description;
        }

    private:
        std::string m_Name = "NOT SET";
        std::string m_Description = "NOT SET";
    };

    // A test scenario which is composed of multiple steps must inherit AccTestScenario. You should create your test steps 
    // within the constructor of your derived class and add them in the same order as you want them to be executed. Use AddStep() 
    // to add the next test step.
    // The test context is created and is accessible within you derived class as GetTestContext.
    // Override Setup and Teardown to provide code for test context initialization and finalization before and after serial 
    // execution of the steps. This is probably where you will want to create you application object and related test stubs, etc. 
    // Don't forget to get rid of everything in Teardown. 
    // When the scenario is run (by a call to Run), first the Setup() method is called once, then all the test steps are executed 
    // in the order they were added, and finally the Teardown() method is called to wrap up the test. Executing each step 
    // involves calling its Setup, Expect, Act, Verify, and Teardown methods in the same order.
    // After executing Run(), you can retrieve the test results using GetReport(). You can use a AccTestReportFormatter to format 
    // the report as text and send it to an output stream.
    // When subclassing, pass the name and description of the test scenario to the base constructor. These information will 
    // subsequently be available using GetName and GetDescription.

    template <class T>
    class AccTestScenario : public AccTestScenarioBase {
    public:
        typedef T TestContextType;

        AccTestScenario(const std::string& name, const std::string& description)
        : AccTestScenarioBase(name, description) {
        }

        void Run(const std::shared_ptr<AccTestObserverIface>& testObserver) override {
            testObserver->StartingScenario(GetName(), GetDescription(), m_Steps.size());
            try {
                RunUnprotected(testObserver);
            } catch (...) {
                testObserver->ExceptionInScenario();
            }
            testObserver->FinishedScenario();
        }

    protected:

        template <class StepType, class... Args>
        void CreateStep(Args... constructionArgs) {
            m_Steps.push_back(std::make_shared<StepType>(constructionArgs...));
        }

        TestContextType* GetTestContext() {
            return &m_TestContext;
        }

    private:

        class ScenarioSetup {
        public:

            ScenarioSetup(AccTestScenario* scenario)
            : m_Scenario(scenario) {
                m_Scenario->Setup();
            }

            ~ScenarioSetup() {
                m_Scenario->Teardown();
            }

        private:
            AccTestScenario<TestContextType>* m_Scenario;
        };

        class StepSetup {
        public:

            StepSetup(AccTestStep<TestContextType>* step)
            : m_Step(step) {
                m_Step->Setup();
            }

            ~StepSetup() {
                if (!m_Step->IsVerified())
                    m_Step->Verify();
                m_Step->Teardown();
            }

        private:
            AccTestStep<TestContextType>* m_Step;
        };

        virtual void Setup() {
        }

        virtual void Teardown() {
        }

        void RunUnprotected(const std::shared_ptr<AccTestObserverIface>& testObserver) {
            testObserver->StartingScenarioSetup();
            ScenarioSetup scenSetup(this);
            for (const auto& step : m_Steps) {
                auto requiredStepFailed = !RunStepUnprotected(step, testObserver) && step->IsRequired();
                if (requiredStepFailed) {
                    testObserver->ScenarioTerminated();
                    break;
                }
            }
            testObserver->RunningScenarioTeardown();
        }

        bool RunStepUnprotected(const std::shared_ptr< AccTestStep<TestContextType> >& step,
                const std::shared_ptr<AccTestObserverIface>& testObserver) {
            testObserver->StartingScenarioStep(step->GetName(), step->GetDescription());
            step->SetContext(&m_TestContext);
            testObserver->ExecutingStepSetup();
            StepSetup stepSetup(step.get());
            testObserver->RunningStepExpectations();
            step->Expect();
            testObserver->StartingStepAct();
            bool didThrow = false;
            try {
                step->Act();
            } catch (...) {
                didThrow = true;
            }
            bool passedThrowReq = didThrow == step->MustThrow();
            if (!passedThrowReq)
                testObserver->StepExceptionExpectationNotMet(didThrow);
            else {
                testObserver->StartingStepVerification();
                step->Verify();
                testObserver->FinishedStepVerification(step->Passed());
                if (!step->Passed())
                    testObserver->StepVerificationFailed(step->GetCheckOutputs());
            }
            testObserver->ExecutingStepTeardown();
            return step->Passed();
        }

        std::vector< std::shared_ptr< AccTestStep<TestContextType> > > m_Steps;
        TestContextType m_TestContext;
    };

    // Default implementation of the test observer that a test suite uses by default. The default observer can be replaced by
    // a custom implementation using the other overload of the AccTestSuite class or afterwards using the SetTestObserver method.
    // This default implementation logs all the events, progress, and stats to the output stream provided. 
    // It has also additional methods not inherited from the interface that are used to retrieve test stats after the execution.

    class AccTestObserver : public AccTestObserverIface {
    public:

        AccTestObserver(std::ostream& outputStream)
        : m_OutputStream(outputStream) {
        }

        void StartingTestSuite(std::size_t numberOfTestScenarios) override {
            m_OutputStream << "Starting execution of test suite" << std::endl;
            m_NumberOfScenarios = numberOfTestScenarios;
            m_CurrentScenarioIndex = 0;
        }

        void StartingScenario(const std::string& name, const std::string& description, std::size_t numberOfSteps) override {
            m_NumberOfStepsInScenario = numberOfSteps;
            ++m_CurrentScenarioIndex;
            m_CurrentStepIndex = 0;
            m_OutputStream << std::endl << "  Starting execution of test scenario \"" << name << "\" - " <<
                    m_CurrentScenarioIndex << " of " << m_NumberOfScenarios <<
                    " (" << std::setprecision(3) << GetProgressPercentage() << "%)" << std::endl <<
                    "    Description: " << description << std::endl << "    Total number of steps: " << numberOfSteps << std::endl;
        }

        void StartingScenarioSetup() override {
            m_OutputStream << "    Starting scenario setup..." << std::endl;
        }

        void ScenarioTerminated() override {
            m_OutputStream << "    A required scenario step failed; scenario execution terminated!" << std::endl;
            ++m_NumberOfScenariosTerminated;
        }

        void RunningScenarioTeardown() override {
            m_OutputStream << "    Running scenario tear-down..." << std::endl;
        }

        void StartingScenarioStep(const std::string& name, const std::string& description) override {
            ++m_CurrentStepIndex;
            m_OutputStream << "      Starting execution of scenario step \"" << name << "\" - " <<
                    m_CurrentStepIndex << " of " << m_NumberOfStepsInScenario <<
                    " (" << std::setprecision(3) << GetProgressPercentage() << "%)" << "\"" << std::endl <<
                    "      Description: " << description << std::endl;
            m_StepPassed = true;
        }

        void ExecutingStepSetup() override {
            m_OutputStream << "        Running scenario step setup..." << std::endl;
        }

        void RunningStepExpectations() override {
            m_OutputStream << "        Running scenario step expectations..." << std::endl;
        }

        void StartingStepAct() override {
            m_OutputStream << "        Starting scenario step act..." << std::endl;
        }

        void ExceptionInScenario() override {
            m_OutputStream << "      Exception thrown during execution of scenario; terminated!" << std::endl;
            ++m_NumberOfScenariosTerminated;
        }

        void StepExceptionExpectationNotMet(bool didThrow) override {
            m_OutputStream << "        " <<
                    (didThrow ? "Unexpected exception was thrown!" : "Expected exception was not thrown!") << std::endl;
            m_StepPassed = m_StepPassed && false;
        }

        void StartingStepVerification() override {
            m_OutputStream << "        Starting scenario step verification..." << std::endl;
        }

        void FinishedStepVerification(bool passed) override {
            m_OutputStream << "        Scenario step verification " << (passed ? "passed." : "failed!") << std::endl;
            m_StepPassed = m_StepPassed && passed;
        }

        void StepVerificationFailed(const std::map<int, std::string>& failedCheckOutputs) override {
            m_OutputStream << "        Failed step checks:" << std::endl;
            for (const auto& checkOutput : failedCheckOutputs)
                m_OutputStream << "          Check #" << checkOutput.first << " => " << checkOutput.second << std::endl;
        }

        void ExecutingStepTeardown() override {
            m_OutputStream << "        Running scenario step tear-down..." << std::endl << std::endl;
            if (m_StepPassed)
                ++m_NumberOfStepsPassed;
            else
                ++m_NumberOfStepsFailed;
        }

        void FinishedScenario() override {
            m_OutputStream << "  Finished execution of test scenario." << std::endl;
            if (m_NumberOfStepsPassed == m_NumberOfStepsInScenario)
                m_OutputStream << "    All steps passed successfully. Total: " << m_NumberOfStepsInScenario << std::endl;
            else {
                m_OutputStream << "    Number of failed steps: " << m_NumberOfStepsFailed <<
                        " out of " << m_NumberOfStepsInScenario << std::endl;
                auto omittedSteps = m_NumberOfStepsInScenario - m_NumberOfStepsPassed - m_NumberOfStepsFailed;
                if (omittedSteps > 0) {
                    m_OutputStream << "    Number of omitted steps: " << omittedSteps <<
                            " out of " << m_NumberOfStepsInScenario << std::endl;
                } else
                    ++m_NumberOfScenariosFailed;
            }
            m_OutputStream << std::endl;
            m_CurrentStepIndex = m_NumberOfStepsInScenario = m_NumberOfStepsPassed = m_NumberOfStepsFailed = 0;
        }

        void FinishedTestSuite() override {
            m_OutputStream << "Finished execution of test suite." << std::endl;
            if (m_NumberOfScenariosFailed == 0 && m_NumberOfScenariosTerminated == 0)
                m_OutputStream << "  All scenarios completed successfully." << std::endl;
            else {
                if (m_NumberOfScenariosFailed > 0)
                    m_OutputStream << "  Number of failed scenarios: " << m_NumberOfScenariosFailed <<
                        " out of " << m_NumberOfScenarios << std::endl;
                if (m_NumberOfScenariosTerminated > 0)
                    m_OutputStream << "  Number of terminated scenarios: " << m_NumberOfScenariosTerminated <<
                        " out of " << m_NumberOfScenarios << std::endl;
            }
            m_CurrentScenarioIndex = m_NumberOfScenarios = m_NumberOfScenariosFailed = m_NumberOfScenariosTerminated = 0;
        }

        std::size_t GetNumberOfScenariosPassed() {
            return m_NumberOfScenarios - m_NumberOfScenariosFailed - m_NumberOfScenariosTerminated;
        }

        std::size_t GetNumberOfScenarios() {
            return m_NumberOfScenarios;
        }

        double GetProgressPercentage() {
            if (m_NumberOfScenarios == 0 || m_NumberOfStepsInScenario == 0)
                return 0;
            auto currentStepIndexNonZero = std::max(m_CurrentStepIndex, static_cast<std::size_t> (1));
            auto currentScenarioProgress = static_cast<double> (currentStepIndexNonZero - 1) / m_NumberOfStepsInScenario;
            return (m_CurrentScenarioIndex - 1 + currentScenarioProgress) / m_NumberOfScenarios * 100;
        }
    private:
        std::ostream& m_OutputStream;
        std::size_t m_CurrentScenarioIndex = 0;
        std::size_t m_NumberOfScenarios = 0;
        std::size_t m_NumberOfScenariosFailed = 0;
        std::size_t m_NumberOfScenariosTerminated = 0;
        std::size_t m_CurrentStepIndex = 0;
        std::size_t m_NumberOfStepsInScenario = 0;
        std::size_t m_NumberOfStepsPassed = 0;
        std::size_t m_NumberOfStepsFailed = 0;
        bool m_StepPassed = true;
    };

    // In most cases you have more than one test scenario with sequential steps that has its own starting point, steps, and cleanup.
    // To accommodate these situations you can use a test suite which is basically a collection of unrelated test scenarios. Simply
    // inherit AccTestSuite and, within your constructor, create and add your test scenarios using calls to AddScenario. Afterwards,
    // you can run all the scenarios in the test suite by a call to the Run method. This executes all the scenarios in the same 
    // order as they were added. The order shouldn't matter as the test scenarios are supposed to be unrelated, i.e., each scenario
    // has its own Setup which is supposed to set the preconditions regardless of anything else that might have happened before.
    // The Run method returns the complete report for all the test scenarios within the suite.

    class AccTestSuite {
    public:

        AccTestSuite()
        : m_TestObs(std::make_shared<AccTestObserver>(std::cout)) {
        }

        void SetTestObserver(std::shared_ptr<AccTestObserverIface> testObs) {
            m_TestObs = testObs;
        }

        void Run() {
            m_TestObs->StartingTestSuite(m_Scenarios.size());
            for (auto test : m_Scenarios)
                test->Run(m_TestObs);
            m_TestObs->FinishedTestSuite();
        }

    protected:

        template <class ScenType, class... Args>
        void CreateScenario(Args... constructionArgs) {
            m_Scenarios.push_back(std::make_shared<ScenType>(constructionArgs...));
        }

    private:
        std::vector< std::shared_ptr<AccTestScenarioBase> > m_Scenarios;
        std::shared_ptr<AccTestObserverIface> m_TestObs;
    };

    // In the main() function of your test executable you will probably have an instance of AccTestRunner specialized with your 
    // test suite class. AccTestRunner is supposed to take care of you argc and argv. Currently it simply throws them away!
    // You main() function will then call the Run() method and everything else taken care of: like all the test suite is run, and
    // the report passed to the report formatter and printed out to standard output.

    template <class T = AccTestSuite>
    class AccTestRunner {
    public:
        typedef T TestSuiteType;

        AccTestRunner(int argc, char** argv) {
        }

        int Run() {
            auto testObserver = std::make_shared<AccTestObserver>(std::cout);
            TestSuiteType testSuite;
            testSuite.SetTestObserver(testObserver);
            testSuite.Run();
            return testObserver->GetNumberOfScenarios() - testObserver->GetNumberOfScenariosPassed();
        }
    };

} // namespace ProTest

// Use this macro to insert the default main() function for the test program. You can clone the code from here and write your 
// customized main() function as the default is rather limited in options.
#define ACC_TEST_DEFAULT_MAIN_FUNC(TEST_SUITE_NAME)  \
int main (int argc, char** argv)  \
{   \
    return ProTest::AccTestRunner<TEST_SUITE_NAME>(argc, argv).Run();    \
}

#endif // __ACC_TEST_H__

// Use this macro in your implementation of Verify() within the test steps to check for equality of two values with suitable 
// failure output.
#define ACC_TEST_CHECK_EQUAL(LEFT, RIGHT) \
Check((LEFT) == (RIGHT)) << "NOT EQUAL: "#LEFT" = " << (LEFT) << ", "#RIGHT" = " << (RIGHT)

#define ACC_TEST_CHECK_CUST_EQUAL(LEFT, RIGHT, EQUALITY) \
Check((EQUALITY)((LEFT), (RIGHT))) << "NOT EQUAL: "#LEFT" = " << (LEFT) << ", "#RIGHT" = " << (RIGHT)

#define ACC_TEST_CHECK(PREDICATE) \
Check(PREDICATE) << "Check failed (not true): "#PREDICATE;
