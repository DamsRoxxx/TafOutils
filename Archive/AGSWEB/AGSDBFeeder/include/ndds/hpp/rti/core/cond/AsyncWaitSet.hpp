/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_UTIL_ASYNC_WAIT_SET_HPP_
#define RTI_DDS_UTIL_ASYNC_WAIT_SET_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"
#include "dds_c/dds_c_asyncwaitset.h"

#include <dds/core/Value.hpp>
#include <dds/core/Duration.hpp>
#include <dds/core/cond/Condition.hpp>
#include <dds/core/cond/WaitSet.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/ThreadSettings.hpp>
#include <rti/core/cond/AsyncWaitSetListener.hpp>
#include <rti/core/FunctorHolder.hpp>

/**
 * @defgroup DDSAsyncWaitSetModule AsyncWaitSet
 * @ingroup DDSConditionsModule
 * 
 * @details \idref_AsyncWaitSetModuleDocs
 */


namespace rti { namespace core { namespace cond {

class AsyncWaitSetProperty;

class AsyncWaitSetPropertyAdapter {
public:
    typedef struct DDS_AsyncWaitSetProperty_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_AsyncWaitSetProperty_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_AsyncWaitSetProperty_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_AsyncWaitSetProperty_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_AsyncWaitSetProperty_is_equal(
                &first,
                &second) == RTI_TRUE);
    }
};

} // close namespace cond

template <>
struct native_type_traits<rti::core::cond::AsyncWaitSetProperty> {
    typedef rti::core::cond::AsyncWaitSetPropertyAdapter adapter_type;
    typedef DDS_AsyncWaitSetProperty_t native_type;
};


namespace cond {

/**
 * @ingroup DDSAsyncWaitSetModule
 * @RTI_class_definition class AsyncWaitSetProperty
 * @headerfile rti/core/cond/AsyncWaitSet.hpp
 * 
 * \dref_AsyncWaitSetProperty_t
 */
class OMG_DDS_API AsyncWaitSetProperty :
public rti::core::NativeValueType<AsyncWaitSetProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(AsyncWaitSetProperty)

    typedef NativeValueType<AsyncWaitSetProperty> Base;
public:
    /**
     * @brief Creates the default property
     */
    AsyncWaitSetProperty() 
        : Base(DDS_ASYNC_WAITSET_PROPERTY_DEFAULT)
    {
    }

    /**
     * @brief Creates an instance with all the specified parameters
     */
    AsyncWaitSetProperty(
            rti::core::cond::WaitSetProperty& the_waitset_property,
            dds::core::Duration& the_wait_timeout,
            int32_t the_level,
            const std::string& the_thread_name_prefix,
            rti::core::ThreadSettings& the_thread_settings,            
            int32_t the_thread_pool_size);

    AsyncWaitSetProperty(
            const DDS_AsyncWaitSetProperty_t& native_wsr_property)
    : Base(native_wsr_property) {
    }

public:
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::cond::WaitSetProperty waitset_property() const;
    /**
     * \dref_AsyncWaitSetProperty_t_waitset_property
     */
    AsyncWaitSetProperty& waitset_property(
            rti::core::cond::WaitSetProperty& the_waitset_property);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration wait_timeout() const;
    /**
     * \dref_AsyncWaitSetProperty_t_wait_timeout
     */
    AsyncWaitSetProperty& wait_timeout(
            dds::core::Duration& the_wait_timeout);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t level() const;
    /**
     * \dref_AsyncWaitSetProperty_t_level
     */
    AsyncWaitSetProperty& level(int32_t the_level);

    /**
     * @brief Getter (see setter with the same name)
     */
    const std::string thread_name_prefix() const;
    /**
     * \dref_AsyncWaitSetProperty_t_thread_name_prefix
     */
    AsyncWaitSetProperty& thread_name_prefix(
            const std::string& thr_thread_name_prefix);

    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::ThreadSettings thread_settings() const;
    /**
     * \dref_AsyncWaitSetProperty_t_thread_settings
     */
    AsyncWaitSetProperty& thread_settings(
            rti::core::ThreadSettings& the_thread_settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t thread_pool_size() const;
    /**
     * \dref_AsyncWaitSetProperty_t_thread_pool_size
     */
    AsyncWaitSetProperty& thread_pool_size(int32_t the_level);
   
};

class AsyncWaitSet;
class AsyncWaitSetImpl;
class AsyncWaitSetCompletionToken;


class OMG_DDS_API AsyncWaitSetCompletionTokenImpl {       
    
public:
    
    AsyncWaitSetCompletionTokenImpl(AsyncWaitSet& aws);
    
    AsyncWaitSetCompletionTokenImpl();

    ~AsyncWaitSetCompletionTokenImpl();      
    
    void wait(const dds::core::Duration& max_wait); 
    
    DDS_AsyncWaitSetCompletionToken * native_completion_token()
    {
        return native_completion_token_;
    }        
    

    DDS_AsyncWaitSetCompletionToken *native_completion_token_;
    dds::core::smart_ptr_traits<AsyncWaitSetImpl>::ref_type aws_;
};

/**
 * @ingroup DDSAsyncWaitSetModule
 * 
 * \dref_AsyncWaitSetCompletionToken
 */
class OMG_DDS_API AsyncWaitSetCompletionToken 
        : public dds::core::Reference<AsyncWaitSetCompletionTokenImpl> {
public:
    typedef dds::core::Reference<AsyncWaitSetCompletionTokenImpl> Base;

    
public:
    /**     
     * \dref_AsyncWaitSet_create_completion_token
     */
    AsyncWaitSetCompletionToken(AsyncWaitSet& aws)
        : Base(new AsyncWaitSetCompletionTokenImpl(aws))
    {
    }
    

    explicit AsyncWaitSetCompletionToken(Base::DELEGATE_REF_T reference) 
        : Base(reference)
    {
    }
    
    /**     
     * \dref_AsyncWaitSetCompletionToken_wait
     */
    void wait(const dds::core::Duration& max_wait 
            = dds::core::Duration::infinite()) 
    {
        this->delegate()->wait(max_wait);
    }
    
    /**
     * @brief Internal use only
     */
    DDS_AsyncWaitSetCompletionToken * native_completion_token()
    {
        return this->delegate()->native_completion_token();
    }
    
    /**     
     * \dref_ASYNC_WAITSET_COMPLETION_TOKEN_IGNORE
     */   
    static AsyncWaitSetCompletionToken Ignore();
    
private:
 
    AsyncWaitSetCompletionToken()
        : Base(new AsyncWaitSetCompletionTokenImpl())
    {
    }        
    
};


class OMG_DDS_API AsyncWaitSetImpl {
public:

    typedef std::vector<dds::core::cond::Condition> ConditionSeq;
    
    AsyncWaitSetImpl();    

    AsyncWaitSetImpl(
            const AsyncWaitSetProperty& property,
            AsyncWaitSetListener *listener);

    ~AsyncWaitSetImpl();

    void start();
    void start(AsyncWaitSetCompletionToken completion_token);
    void stop();   
    void stop(AsyncWaitSetCompletionToken completion_token);   
    
    
    void attach_condition(
            dds::core::cond::Condition condition);
    void attach_condition(
            dds::core::cond::Condition condition,
            AsyncWaitSetCompletionToken completion_token);
    
    void detach_condition(
            dds::core::cond::Condition cond);  
    
    void detach_condition(
            dds::core::cond::Condition cond,
            AsyncWaitSetCompletionToken completion_token); 
    
    void unlock_condition(dds::core::cond::Condition cond);

    /**
     * @memberof dds::core::cond::AsyncWaitSet
     *
     * @brief Gets the AsyncWaitSetProperty
     */
    AsyncWaitSetProperty property() const;
    
    /**
     * 
     * @return The list of attached conditions
     */
    ConditionSeq conditions() const;
    ConditionSeq& conditions(ConditionSeq& conds) const;
    
    
    /**
     * @brief Internal use only
     */
     DDS_AsyncWaitSet * native_aws();
              
private:
    DDS_AsyncWaitSet *native_aws_;
};


/**
 * @ingroup DDSAsyncWaitSetModule
 * @headerfile rti/core/cond/AsyncWaitSet.hpp
 * 
 * \dref_AsyncWaitSet
 */
class OMG_DDS_API AsyncWaitSet
    : public dds::core::Reference<AsyncWaitSetImpl> {
    
    typedef dds::core::Reference<AsyncWaitSetImpl> Base;
    typedef std::vector<dds::core::cond::Condition> ConditionSeq;    
    
public:
    
    static OMG_DDS_API_CLASS_VARIABLE const AsyncWaitSetProperty 
            PROPERTY_DEFAULT;

    /**     
     * @ingroup DDSAsyncWaitSetModule
     * 
     * @brief Constructor without arguments that create an \idref_AsyncWaitSet
     * with default property.
     * 
     * @see \idref_ASYNC_WAITSET_PROPERTY_DEFAULT
     */
    AsyncWaitSet()
        : Base(new AsyncWaitSetImpl())
    {
    }
    
    /**     
     * \dref_AsyncWaitSet_new
     */
    AsyncWaitSet(
            const AsyncWaitSetProperty& the_property)
        : Base(new AsyncWaitSetImpl(the_property, NULL))
    {
    }
    
    /**     
     * \dref_AsyncWaitSet_new_with_listener
     */
    AsyncWaitSet(
            const AsyncWaitSetProperty& the_property,
            AsyncWaitSetListener *listener)
        : Base(new AsyncWaitSetImpl(the_property, listener))
    {
    }
    
    AsyncWaitSet(const dds::core::null_type&)
      : Base(static_cast<AsyncWaitSetImpl*>(NULL))
    {
    }

    ~AsyncWaitSet()
    {
    }

    /** 
     * \dref_AsyncWaitSet_start
     */
    void start()
    {
        this->delegate()->start();
    }
    
    /**
     * \dref_AsyncWaitSet_start_with_completion_token 
     */
    void start(AsyncWaitSetCompletionToken completion_token)
    {
        this->delegate()->start(completion_token);
    }
    
    /** 
     * \dref_AsyncWaitSet_stop 
     */
    void stop() 
    {
        this->delegate()->stop();
    }
    
    /**
     * \dref_AsyncWaitSet_stop_with_completion_token 
     */
    void stop(AsyncWaitSetCompletionToken completion_token) 
    {
        this->delegate()->stop(completion_token);
    }
        
    
    /** 
     * \dref_AsyncWaitSet_attach_condition 
     */
    AsyncWaitSet& attach_condition(
            dds::core::cond::Condition condition)
    {
        this->delegate()->attach_condition(condition);
        return *this;
    }

    /**
     * \dref_AsyncWaitSet_attach_condition_with_completion_token 
     */
    AsyncWaitSet& attach_condition(
            dds::core::cond::Condition condition,
            AsyncWaitSetCompletionToken completion_token)
    {
        this->delegate()->attach_condition(condition, completion_token);
        return *this;
    }
    
    /**
     * \dref_AsyncWaitSet_detach_condition 
     */
    AsyncWaitSet& detach_condition(
            dds::core::cond::Condition condition) 
    {
        this->delegate()->detach_condition(condition);
        return *this;
    }
    
    /**
     * \dref_AsyncWaitSet_detach_condition_with_completion_token 
     */
    AsyncWaitSet& detach_condition(
            dds::core::cond::Condition condition,
            AsyncWaitSetCompletionToken completion_token)
    {
        this->delegate()->detach_condition(condition, completion_token);
        return *this;
    }
    
    /** 
     * \dref_AsyncWaitSet_attach_condition 
     */
    AsyncWaitSet& operator +=(dds::core::cond::Condition condition)
    {
        return this->attach_condition(condition);        
    }
    
    /** 
     * \dref_AsyncWaitSet_detach_condition 
     */
    AsyncWaitSet& operator -=(dds::core::cond::Condition condition)
    {
        return this->detach_condition(condition);        
    }
    
    /**
     *  \dref_AsyncWaitSet_unlock_condition 
     */
    void unlock_condition(dds::core::cond::Condition condition)
    {
        return this->delegate()->unlock_condition(condition);
    }

    /**
     * \dref_AsyncWaitSet_get_property 
     */
    AsyncWaitSetProperty property() 
    {
        return this->delegate()->property();
    }   
    
    /**
     *  @brief Returns the list of attached \idref_Condition (s). 
     */
    ConditionSeq conditions() const
    {
        return this->delegate()->conditions();
    }
    
    /**
     *  \dref_AsyncWaitSet_get_conditions 
     */
    ConditionSeq& conditions(ConditionSeq& attached_conditions) const
    {
        return this->delegate()->conditions(attached_conditions);
    }

};

class AsyncWaitSetListenerForwarder;

} } } // close namespace rti::core::cond


#endif // RTI_DDS_UTIL_ASYNC_WAIT_SET_HPP_
