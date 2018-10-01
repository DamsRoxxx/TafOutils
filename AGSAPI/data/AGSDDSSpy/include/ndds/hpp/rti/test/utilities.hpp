/* $Id$

 (c) Copyright, Real-Time Innovations, 2014-2016. 
 All rights reserved.
 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
-------------------- 
5.0.2,12jun14,eam Created
============================================================================= */

/*i @file
   Defines utilities that can be used in the testers
*/
#ifndef RTI_TEST_UTILITIES_HPP_
#define RTI_TEST_UTILITIES_HPP_

#include <dds/core/QosProvider.hpp>
#include <dds/domain/DomainParticipant.hpp>

namespace rti { namespace test {

//
// Base class for defining threads by implementing the run() method with
// auto-join capability.
//
Package
class Thread {
private:
    std::string _name;
    bool _auto_join;
    bool _running;
    RTIOsapiThread * _thread;
    RTIOsapiSemaphore * _exit_sem;
    bool _exception;
    std::string _exception_message;
public:

    Thread(const std::string& name = std::string("Thread"),
              bool auto_join = true)
        : _name(name),
          _auto_join(auto_join),
          _running(false),
          _thread(NULL),
          _exit_sem(NULL),
          _exception(false)
    {
        RTIOsapiSemaphoreProperty sem_prop =
                RTI_OSAPI_SEMAPHORE_PROPERTY_DEFAULT;
        _exit_sem = RTIOsapiSemaphore_new(
                RTI_OSAPI_SEMAPHORE_KIND_BINARY, &sem_prop);
        RTI_TEST_ASSERT(_exit_sem != NULL);
    }

    virtual ~Thread()
    {
        if (_auto_join && _running) {
            try {
                join();
            } catch(...) {
                return;
            }
        }
        RTIOsapiSemaphore_delete(_exit_sem); // Can't be NULL
        if(_thread != NULL) {
            RTIOsapiThread_delete(_thread);
        }
    }

    void join(int max_wait_sec = 10) {

        if (_running) {
            RTINtpTime  max_wait = {0, 0};
            max_wait.sec = max_wait_sec;
            if (RTIOsapiSemaphore_take(_exit_sem, &max_wait) !=
                    RTI_OSAPI_SEMAPHORE_STATUS_OK) {
                RTI_TEST_FAIL(_name + " join timed out");
            }
        }

        if (_exception) {
            RTI_TEST_FAIL(
                ("Thread finished with exception: " + _exception_message).c_str());
        }
    }

    void start() {
        _running = true;
        _thread = RTIOsapiThread_new(
            _name.c_str(),
            RTI_OSAPI_THREAD_PRIORITY_NORMAL,
            RTI_OSAPI_THREAD_OPTION_DEFAULT,
            RTI_OSAPI_THREAD_STACK_SIZE_DEFAULT, NULL,
            run_wrapper, this);

        if (_thread == NULL) {
            _running = false;
            RTI_TEST_FAIL("Failed to create RTIOsapiThread");
        }
    }

    virtual void run() = 0;

private:
    static void * run_wrapper(void * args)
    {
        const char * METHOD_NAME =
            "Thread::run_wrapper";
        Thread * thread = (Thread *) args;
        thread->_exception = false;
        try {
            thread->run();
        } catch (const std::exception& ex) {
            thread->_exception = true;
            thread->_exception_message = ex.what();
            RTITestLog_exception(METHOD_NAME, &RTI_LOG_ANY_FAILURE_s,
                                 ex.what());
        } catch (...) {
            thread->_exception = true;
            thread->_exception_message = "Unknown exception";
            RTITestLog_exception(METHOD_NAME, &RTI_LOG_ANY_FAILURE_s,
                                "Unknown exception");
        }

        thread->_running = false;
        RTIOsapiSemaphore_give(thread->_exit_sem);
        return NULL;
    }

};


// --- AutoEnableCreatedEntitiesGuard: ----------------------------------------

/*
 * A guard which sets the DPF's EntityFactoryQos false on creation and true on 
 * deletion 
 */
class AutoEnableCreatedEntitiesGuard {

public:
    AutoEnableCreatedEntitiesGuard()
    {
        // Create participants disabled 
        dds::domain::qos::DomainParticipantFactoryQos qos = 
            dds::domain::DomainParticipant::participant_factory_qos();
        qos << dds::core::policy::EntityFactory(false);
        dds::domain::DomainParticipant::participant_factory_qos(qos);
    }

    AutoEnableCreatedEntitiesGuard(
        dds::domain::qos::DomainParticipantFactoryQos& qos)
    {
        // Create participants disabled 
        qos << dds::core::policy::EntityFactory(false);
        dds::domain::DomainParticipant::participant_factory_qos(qos);
    }

    ~AutoEnableCreatedEntitiesGuard()
    {
        // Reset the DPF qos to create entities enabled for the next tests 
        dds::domain::qos::DomainParticipantFactoryQos qos  = 
            dds::domain::DomainParticipant::participant_factory_qos();
        qos << dds::core::policy::EntityFactory(true);
        dds::domain::DomainParticipant::participant_factory_qos(qos);
    }
}; 

// --- AutoEnableCreatedEntitiesGuard: ----------------------------------------

/*
 * A guard which resets the default QosProvider in case a unit test changes 
 * the default library or profile, those changes will not affect following tests 
 */
class DefaultQosProviderGuard {

public:
    DefaultQosProviderGuard() { }

    ~DefaultQosProviderGuard()
    {
        // Reset the Default QosProvider 
        dds::core::QosProvider::reset_default();
    }
}; 

} } // namespace rti::test


#endif // RTI_TEST_UTILITIES_HPP_

/* End $Id$ */
