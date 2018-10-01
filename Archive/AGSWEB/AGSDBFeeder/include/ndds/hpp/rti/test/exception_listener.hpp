/* $Id$

 (c) Copyright, Real-Time Innovations, 2014-2016. 
 All rights reserved.
 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
-------------------- 
1.7a,12may14,eam Created
============================================================================= */

/*i @file
   Defines a generic DataReaderListener that catches exceptions that allows
   them to be thrown in the main thread
*/

#ifndef RTI_TEST_EXCEPTION_LISTENER_HPP_
#define RTI_TEST_EXCEPTION_LISTENER_HPP_

#include <rti/test/assertions.hpp>
#include <dds/sub/DataReaderListener.hpp>

// --- Exception Handling listeners: ----------------------------------------

namespace rti { namespace test {

enum TestFailureKind {
    TEST_FAILURE_KIND_SUCCESS =             0,
    TEST_FAILURE_KIND_TEST_EXCEPTION =      1,
    TEST_FAILURE_KIND_STD_EXCEPTION =       2
};

// A class allowing us to store the relevant details of the thrown exception
// so that we can recreate it when we need to actually throw
class TestFailureDetails
{
public:
    TestFailureDetails() {}

    TestFailureDetails(
       std::string the_file, std::string the_line, std::string the_msg)
    : file_(the_file),
      line_(the_line),
      msg_(the_msg)
    {
    }

    TestFailureDetails& operator=(const TestFailure& failure)
    {
        file_ = failure.file();
        line_ = failure.line();
        msg_ = failure.what();
        return *this;
    }

    std::string file() const { return file_; }
    void file(const std::string& the_file) { file_ = the_file; }

    std::string line() const { return line_; }
    void line(const std::string& the_line) { line_ = the_line; }

    std::string msg() const { return msg_; }
    void msg(const std::string& the_msg) { msg_ = the_msg; }

private: 
    std::string file_;
    std::string line_;
    std::string msg_;
};

// Listener
template<typename T>
class ExceptionHandlerDataReaderListener
    : public dds::sub::NoOpDataReaderListener<T> {
public:
    ExceptionHandlerDataReaderListener()
        : failed_(TEST_FAILURE_KIND_SUCCESS),
          failure_details_("","","")
    {
    }

    virtual ~ExceptionHandlerDataReaderListener()
    {
    }

    const dds::core::status::StatusMask& finished() const
    {
        return finished_;
    }

    bool failed()
    {
        return failed_;
    }

    const rti::test::TestFailure failure()
    {
        return rti::test::TestFailure(
           failure_details_.file(),
           failure_details_.line(),
           failure_details_.msg());
    }

public:
    void on_data_available(dds::sub::DataReader<T> &reader)
    {
        try {
            process_on_data_available(reader);
        } catch (const rti::test::TestFailure& ex) {
            failure_details_ = ex;
            failed_ = TEST_FAILURE_KIND_TEST_EXCEPTION;
        } catch (std::exception &ex) {
            exception_ = ex;
            failed_ = TEST_FAILURE_KIND_STD_EXCEPTION;
        }

        finished_ |= dds::core::status::StatusMask::data_available();
    }

    virtual void process_on_data_available(dds::sub::DataReader<T>&)
    {
    }

    virtual void on_requested_deadline_missed(
        dds::sub::DataReader<T>& reader,
        const dds::core::status::RequestedDeadlineMissedStatus& status)
    {
        try {
            process_on_requested_deadline_missed(reader, status);
        } catch (const rti::test::TestFailure& ex) {
            failure_details_ = ex;
            failed_ = TEST_FAILURE_KIND_TEST_EXCEPTION;
        } catch (std::exception &ex) {
            exception_ = ex;
            failed_ = TEST_FAILURE_KIND_STD_EXCEPTION;
        }

        finished_ |= dds::core::status::StatusMask::requested_deadline_missed();
    }
    virtual void process_on_requested_deadline_missed(
        dds::sub::DataReader<T>&,
        const dds::core::status::RequestedDeadlineMissedStatus&)
    {
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::DataReader<T>& reader,
        const dds::core::status::RequestedIncompatibleQosStatus& status)
    {
        try {
            process_on_requested_incompatible_qos(reader, status);
        } catch (const rti::test::TestFailure& ex) {
            failure_details_ = ex;
            failed_ = TEST_FAILURE_KIND_TEST_EXCEPTION;
        } catch (std::exception &ex) {
            exception_ = ex;
            failed_ = TEST_FAILURE_KIND_STD_EXCEPTION;
        }

        finished_ |= dds::core::status::StatusMask::requested_incompatible_qos();
    }

    virtual void process_on_requested_incompatible_qos(
        dds::sub::DataReader<T>&,
        const dds::core::status::RequestedIncompatibleQosStatus&)
    {
    }

    virtual void on_sample_rejected(
        dds::sub::DataReader<T>& reader,
        const dds::core::status::SampleRejectedStatus& status)
    {
        try {
            process_on_sample_rejected(reader, status);
        } catch (const rti::test::TestFailure& ex) {
            failure_details_ = ex;
            failed_ = TEST_FAILURE_KIND_TEST_EXCEPTION;
        } catch (std::exception &ex) {
            exception_ = ex;
            failed_ = TEST_FAILURE_KIND_STD_EXCEPTION;
        }

        finished_ |= dds::core::status::StatusMask::sample_rejected();
    }
    virtual void process_on_sample_rejected(
        dds::sub::DataReader<T>&,
        const dds::core::status::SampleRejectedStatus&) { }


    virtual void on_liveliness_changed(
        dds::sub::DataReader<T>& reader,
        const dds::core::status::LivelinessChangedStatus& status)
    {
        try {
            process_on_liveliness_changed(reader, status);
        } catch (const rti::test::TestFailure& ex) {
            failure_details_ = ex;
            failed_ = TEST_FAILURE_KIND_TEST_EXCEPTION;
        } catch (std::exception &ex) {
            exception_ = ex;
            failed_ = TEST_FAILURE_KIND_STD_EXCEPTION;
        }

        finished_ |= dds::core::status::StatusMask::liveliness_changed();
    }

    virtual void process_on_liveliness_changed(
        dds::sub::DataReader<T>&,
        const dds::core::status::LivelinessChangedStatus&)
    {
    }


    virtual void on_subscription_matched(
        dds::sub::DataReader<T>& reader,
        const dds::core::status::SubscriptionMatchedStatus& status)
    {
        try {
            process_on_subscription_matched(reader, status);
        } catch (const rti::test::TestFailure& ex) {
            failure_details_ = ex;
            failed_ = TEST_FAILURE_KIND_TEST_EXCEPTION;
        } catch (std::exception &ex) {
            exception_ = ex;
            failed_ = TEST_FAILURE_KIND_STD_EXCEPTION;
        }

        finished_ |= dds::core::status::StatusMask::subscription_matched();
    }

    virtual void process_on_subscription_matched(
        dds::sub::DataReader<T>&,
        const dds::core::status::SubscriptionMatchedStatus&) { }


    virtual void on_sample_lost(
        dds::sub::DataReader<T>& reader,
        const dds::core::status::SampleLostStatus& status)
    {
        try {
            process_on_sample_lost(reader, status);
        } catch (const rti::test::TestFailure& ex) {
            failure_details_ = ex;
            failed_ = TEST_FAILURE_KIND_TEST_EXCEPTION;
        } catch (std::exception &ex) {
            exception_ = ex;
            failed_ = TEST_FAILURE_KIND_STD_EXCEPTION;
        }

        finished_ |= dds::core::status::StatusMask::sample_lost();
    }
    virtual void process_on_sample_lost(
        dds::sub::DataReader<T>&,
        const dds::core::status::SampleLostStatus&) { }

    void wait(const dds::core::status::StatusMask& mask)
    {
        RTI_TEST_WAIT_FOR((mask & finished_).any(), 10);

        if (failed_ == TEST_FAILURE_KIND_TEST_EXCEPTION) {
            throw failure();
        } else if (failed_ == TEST_FAILURE_KIND_STD_EXCEPTION){
            throw exception_;
        }
        // else, success
    }

private:
    TestFailureKind failed_;
    TestFailureDetails failure_details_;
    std::exception exception_;
    dds::core::status::StatusMask finished_;
};

} } // namespace rti / namespace test

#endif // RTI_TEST_EXCEPTION_LISTENER_HPP_

/* End $Id$ */
