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
   Defines the macros that testers use to check and wait for conditions.
*/

#ifndef RTI_TEST_ASSERTIONS_HPP_
#define RTI_TEST_ASSERTIONS_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <string>

#include "dds_c/dds_c_log.h"
#include "osapi/osapi_utility.h"
#include "test/test_setting.h"

namespace rti { namespace test {

// --- TestFailure exception: -------------------------------------------------

/*
 * The exception that assertions throw
 */
class TestFailure : public std::logic_error {
public:
    
    TestFailure(
        const std::string& the_file,
        const std::string& the_line,
        const std::string& the_msg) 
    : std::logic_error(the_file + ":" + the_line + ": " + the_msg),
      _file(the_file),
      _line(the_line),
      _msg(the_msg)
    {
    }

    TestFailure(
        const std::string& the_file,
        const std::string& the_line,
        const std::string& the_msg,
        const std::exception& nested_ex)
    : std::logic_error(
        the_file + ":" + the_line + ": " + the_msg + " - caused by:\n    " + nested_ex.what()),
      _file(the_file),
      _line(the_line),
      _msg(the_msg)
    {
    }

    // Need to defined the constructor with no-throw exception specification
    // because ~std::logic_error is no-throw. Compilation will fail otherwise
    ~TestFailure() throw()
    {
    }

    const std::string& file() const { return _file; }
    const std::string& line() const { return _line; }
    const std::string& msg() const { return _msg; }

private:
    std::string _file;
    std::string _line;
    std::string _msg;
};

} } // namespace rti / namespace test

// --- Assertion macros: ------------------------------------------------------

/*
 * If EXPRESSION returns false throws a TestFailure
 */
#define RTI_TEST_ASSERT(EXPRESSION)                              \
    if(!(EXPRESSION)) {                                          \
        throw rti::test::TestFailure(                            \
            "" __FILE__,                                         \
            "" RTI_TEST_TOSTRING(__LINE__),                      \
            "assertion failed: " #EXPRESSION);                   \
    }

#define RTI_TEST_FAIL(msg)                                       \
        throw rti::test::TestFailure(                            \
            "" __FILE__,                                         \
            "" RTI_TEST_TOSTRING(__LINE__),                      \
            msg);

/*
 * Waits for a number of seconds for EXPRESSION to become true
 * or throws if it doesn't.
 */
#define RTI_TEST_WAIT_FOR(EXPRESSION, MAX_SECONDS)               \
{                                                                \
    const struct RTINtpTime sleepTime = {0,429496730};           \
    int sleeps = 0;                                              \
    bool result = (EXPRESSION);                                  \
    while(!result && sleeps < MAX_SECONDS * 10) {                \
        RTIOsapiThread_sleep(&sleepTime);                        \
        ++sleeps;                                                \
        result = (EXPRESSION);                                   \
    }                                                            \
    if (!result) {                                               \
        throw rti::test::TestFailure(                            \
            "" __FILE__,                                         \
            "" RTI_TEST_TOSTRING(__LINE__),                      \
            "wait for condition failed: " #EXPRESSION);          \
    }                                                            \
}

/*i
 * Verifies that executing STATEMENT throws EXCEPTION_CLASS
 */
#define RTI_TEST_ASSERT_EXCEPTION(STATEMENT, EXCEPTION_CLASS)    \
    try {                                                        \
        RTITestLog_freeForm(RTI_LOG_BIT_EXCEPTION)(              \
            "vvvvv Error message(s) expected ahead vvvvv\n");    \
        STATEMENT;                                               \
        RTI_TEST_FAIL("Expected exception not thrown");          \
    } catch (const EXCEPTION_CLASS&) {                           \
        RTITestLog_freeForm(RTI_LOG_BIT_EXCEPTION)(              \
            "^^^^^ End of expected error message(s) ^^^^^\n");   \
    }

#define RTI_TEST_ASSERT_EXCEPTION_NO_WARN(STATEMENT, EXCEPTION_CLASS) \
    try {                                                             \
        STATEMENT;                                                    \
        RTI_TEST_FAIL("Expected exception not thrown");               \
    } catch (const EXCEPTION_CLASS&) {                                \
    }

#define RTI_TEST_TRACE_W_MSG(STATEMENT, MSG)                     \
    try {                                                        \
        (STATEMENT);                                             \
    } catch (const std::exception& ex) {                         \
        throw rti::test::TestFailure(                            \
            "" __FILE__,                                         \
            "" RTI_TEST_TOSTRING(__LINE__),                      \
            MSG,                                                 \
            ex);                                                 \
    }

/*i
 * If an assertion fails within a function call in STATEMENT
 * this macro adds this STATEMENT as a reason of the failure.
 *
 * This is a way to build an exception stack to log more than
 * just the line where the exception originated.
 */
#define RTI_TEST_TRACE(STATEMENT)                                \
    RTI_TEST_TRACE_W_MSG(STATEMENT, "test failure: " #STATEMENT)

#endif // RTI_TEST_ASSERTIONS_HPP_

/* End $Id$ */
