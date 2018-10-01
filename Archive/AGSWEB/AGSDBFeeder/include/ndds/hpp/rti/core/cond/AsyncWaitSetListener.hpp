/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

============================================================================= */
#ifndef RTI_DDS_UTIL_ASYNC_WAIT_SET_LISTENER_HPP_
#define RTI_DDS_UTIL_ASYNC_WAIT_SET_LISTENER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/corefwd.hpp>


namespace rti { namespace core { namespace cond {

/**
 * @ingroup DDSAsyncWaitSetModule
 * 
 * \dref_AsyncWaitSetListener
 */
class AsyncWaitSetListener {
public:
    
    typedef uint64_t ThreadId;
    
    virtual ~AsyncWaitSetListener()
    {
    }

    /**    
     * @details \dref_AsyncWaitSetListener_on_thread_spawned
     */
    virtual void on_thread_spawned(
            ThreadId thread_id) = 0;


    /**    
     * @details \dref_AsyncWaitSetListener_on_thread_deleted
     */
    virtual void on_thread_deleted(
            ThreadId thread_id) = 0;

    /**    
     * @details \dref_AsyncWaitSetListener_on_wait_timeout
     */
    virtual void on_wait_timeout(
            ThreadId thread_id) = 0;

};

/**
 * @ingroup DDSAsyncWaitSetModule
 * @brief A convenience implementation of AsyncWaitSetListener where all 
 * methods are overridden to do nothing.
 *
 * Most of the types you can derive your listener from this class so you don't
 * have to implement the methods you don't need.
 */
class NoOpAsyncWaitSetListener: public AsyncWaitSetListener {
public:  
    
    virtual ~NoOpAsyncWaitSetListener()
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_thread_spawned(ThreadId)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_thread_deleted(ThreadId)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_wait_timeout(ThreadId)
    {
    }
};

} } } //rti::core::cond


#endif /* RTI_DDS_UTIL_ASYNC_WAIT_SET_LISTENER_HPP_ */
