/* $Id$

 (c) Copyright, Real-Time Innovations, 2014-2016. 
 All rights reserved.
 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
-------------------- 
5.0.2.x,10feb14,acr CPPPSM-70 Moved test infrastructure from impl files
============================================================================= */


/*i @file

   This file implements the framework for unit tests in dds_cpp.2.0. It's built
   on top of test.1.0.

   ---------------------------------------------
   1) Create a new Tester class MyTester
   ---------------------------------------------

   * Declare MyTester and inherit from rti::test::Tester and
     rti::test::Singleton<MyTester>.
   * Declare test functions:
      * Declare a void, no-arg test function
      * call RTI_TEST_FUNCTION_ADD from the constructor.
   * Implement those functions (outside or inside the class).

   For example:

   class MyTester : Tester, Singleton<MyTester> {
   private:
       void my_test1();
       void my_test2();
       ...

   private:
       MyTester() : Tester("MyTester"), Singleton<MyTester>()
       {
           RTI_TEST_FUNCTION_ADD(MyTester, my_test1);
           RTI_TEST_FUNCTION_ADD(MyTester, my_test2);
           ...
       }
   };

   void MyTester::my_test1()
   {
        RTI_TEST_ASSERT(expression1);
        RTI_TEST_ASSERT(expression2);
        ...

        // Test passes when it returns with no exception
   }

   void MyTester::my_test2() { ... }

   ---------------------------------------------
   2) Implement the top-level tester
   ---------------------------------------------

   To implement the module's top-level tester that contains all the actual
   testers do the following (let's call it MyModuleTester):

   * Declare MyModuleTester and inherit from rti::test::TesterContainer
   * Simply implement a no-argument constructor that adds all the testers.
   * In the main function, call MyModuleTester().run_tests(argc, argv).

   For example:

   class MyModuleTester : public TesterContainer {
   public:
       MyModuleTester() : TesterContainer("MyModuleTester")
       {
           add_tester<MyTester>();
           add_tester<MyTester2>();
           // ...
       }
    };

    int main(int argc, char **argv)
    {
        return rti::test::MyModuleTester().run_tests(argc, argv);
    }

*/

#ifndef RTI_TEST_TESTER_HPP_
#define RTI_TEST_TESTER_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <functional> // for std::mem_fun
#include <vector>

#include <dds/core/detail/inttypes.hpp>

#include <rti/test/assertions.hpp>

namespace rti { namespace test {

// This adapter function takes a member function of a C++ Tester and runs it as
// the C test framework expects: it catches exceptions, reports errors as
// return codes and prints log info.
template <typename Tester>
int run_test_function(
    const struct RTITestSetting* setting,
    const std::string& function_name,
    Tester& tester,
    std::mem_fun_t<void, Tester> test_function)
{
    // Log the test that is running
    RTITestLog_warn(function_name.c_str(), &RTI_LOG_ANY_s, "?");

    try {
        tester.set_settings(setting);

        if (tester.should_ignore_tests()) {
            return tester.ignore_test();
        }

        // Run the actual test
        test_function(&tester);
    } catch (const TestFailure& ex) {
        // Test fails because an assertion failed
        RTITestLog_freeForm(RTI_LOG_BIT_EXCEPTION)
            ("%s (%s)\n", ex.what(), function_name.c_str());
        return 0;
    } catch (const std::exception& ex) {
        // Test fails because some operation failed (not an assertion)
        RTITestLog_exception(function_name.c_str(),
                             &RTI_LOG_ANY_FAILURE_ss,
                             "unhandled exception in test:",
                             ex.what());
        return 0;
    } catch (...) {
        // Test fails because of an unknown exception
        RTITestLog_exception(function_name.c_str(),
                             &RTI_LOG_ANY_FAILURE_s,
                             "unknown exception in test");
        return 0;
    }

    return 1; // test passes
}

// This macro generates and registers a function that the C test framework can
// run. This macro must be called in a Tester constructor.
#define RTI_TEST_FUNCTION_ADD(CLASS_NAME, TEST_FUNCTION)                      \
    struct runner_ ## TEST_FUNCTION {                                         \
        static int run(const struct RTITestSetting* setting)                  \
        {                                                                     \
            return run_test_function(                                         \
                setting,                                                      \
                CLASS_NAME::get_instance().get_name() + "::" #TEST_FUNCTION, \
                CLASS_NAME::get_instance(),                                   \
                std::mem_fun(&CLASS_NAME::TEST_FUNCTION));                    \
        }                                                                     \
    };                                                                        \
                                                                              \
    add_test_function((RTITestFunction) runner_ ## TEST_FUNCTION::run);       \


/*
   Inherit from this class to get a singleton behavior:

   class MyClass : public Singleton<MyClass> {
       private:
           MyClass();
           friend Singleton<MyClass>;
   };
 */
template <class T> class Singleton {
public:
    static T& get_instance()  {
        static T instance;
        return instance;
    }
};

/* Provides basic functionality all Testers can benefit from:
     * Registration of test functions
     * Running those test functions using the underlying test framework
     * Accessing the test settings
     * Indicating that a test requires file system--that will ignore all tests
       if the current platform doesn't have one.
 */
class Tester {
public:

    Tester(
        const std::string& name,
        RTITestLevel test_level = RTI_TEST_LEVEL_UNIT,
        bool tests_require_file_system = false)
        : _settings(NULL),
          _name(name),
          _test_level(test_level),
          _tests_require_file_system(tests_require_file_system)
    {
    }

    virtual ~Tester()
    {
    }

    const std::string& get_name() const
    {
        return _name;
    }

    // Methods to register and run tests:
    int get_test_count() const
    {
        return static_cast<int>(_test_functions.size());
    }

    const RTITestFunction* get_test_functions() const
    {
        return &_test_functions[0];
    }

    void add_test_function(RTITestFunction fnc)
    {
        _test_functions.push_back(fnc);
    }

    template <typename SingletonTester>
    void merge_tester()
    {
        merge_tester(SingletonTester::get_instance());
    }

    void set_settings(const RTITestSetting * settings)
    {
        _settings = settings;
    }

    const RTITestSetting * get_settings() const
    {
        if (_settings == NULL) {
            throw std::logic_error("test settings not specified");
        }
        return _settings;
    }

    std::string get_resource_path(const std::string& file) const
    {
        char resourcePath[RTI_OSAPI_STRING_SEQ_STRING_MAX_SIZE] = {0};
        RTI_TEST_ASSERT(
            RTITestSetting_getFullResourcePathFileName(
                get_settings(),resourcePath,
                file.c_str()));

        return std::string(resourcePath);
    }

    int32_t domain_id() const
    {
        return get_settings()->id;
    }

    bool file_system_support() const
    {
        return (RTITestSetting_fileTestIsSupport(get_settings()) != 0);
    }

    bool should_ignore_tests() const
    {
        return _tests_require_file_system && !file_system_support();
    }

    // Return the result of this function when you need to ignore a test
    int ignore_test(const std::string& reason = "") const
    {
        RTITestLog_freeForm(RTI_LOG_BIT_WARN)("[test ignored");
        if (reason != "") {
            RTITestLog_freeForm(RTI_LOG_BIT_WARN)((": " + reason).c_str());
        }
        RTITestLog_freeForm(RTI_LOG_BIT_WARN)("]\n");
        return 1;
    }

    virtual RTIBool run_tests(const RTITestSetting * settings)
    {
        int begin, end;

        RTITestSetting_getRange(settings, &begin, &end, _test_level);
        DDSLog_setBitmaps(
                settings->submoduleMask, 
                settings->instrumentationMask);
        return RTITestSetting_runTests(settings,
                                       _name.c_str(),
                                       get_test_functions(),
                                       get_test_count(),
                                       begin, end);
    }


private:

    // Adds the test functions from src_tester into dest_tester.
    // Useful to combine smaller Testers into a larger one
    void merge_tester(Tester& src_tester)
    {
        const RTITestFunction * src_functions = src_tester.get_test_functions();
        const int test_count = src_tester.get_test_count();
        for (int i = 0; i < test_count; i++) {
            add_test_function(src_functions[i]);
        }
    }

    const RTITestSetting * _settings;
    enum { MAX_TEST_COUNT = 64 };
    std::vector<RTITestFunction> _test_functions;

    const std::string _name;
    RTITestLevel _test_level;
    bool _tests_require_file_system;
};

// Generic function to run all the test functions in a Tester.
// When instantiated for a concrete Tester it has the
// signature that the C test framework expects.
template <typename SingletonTester>
int run_tester(const struct RTITestSetting* setting)
{
    return SingletonTester::get_instance().run_tests(setting); // does not throw
}

// A container of Testers. This is usually the top level tester
class TesterContainer {
public:

    TesterContainer(const std::string& name)
        : tester_(name, RTI_TEST_LEVEL_SUBMODULE)
    {
    }

    template <typename Tester>
    void add_tester()
    {
        tester_.add_test_function(run_tester<Tester>);
    }

    int run_tests(const RTITestSetting& setting)
    {
        int ok = tester_.run_tests(&setting);
        RTITestSetting_printComplete(tester_.get_name().c_str());
        return ok ? 0 : 1; // return 0 on success as expected by main()
    }

    int run_tests(int argc, char ** argv)
    {
        RTITestSetting setting;
        RTITestSetting_init(&setting);
        if (!RTITestSetting_parseArgument(&setting, argc, argv)) {
            return RTI_FALSE;
        }

        return run_tests(setting);
    }

private:
    Tester tester_; // does most of the work
};

} } // namespace rti::test

#endif // RTI_TEST_TESTER_HPP_

/* End $Id$ */
