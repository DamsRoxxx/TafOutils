/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,22jan13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_COND_WAITSET_HPP_
#define RTI_DDS_CORE_COND_WAITSET_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>
#include <dds/core/corefwd.hpp>
#include <rti/core/detail/SelfReference.hpp>

#include <map>
#include <vector>

namespace rti { namespace core { namespace cond {

class WaitSetProperty;

class WaitSetPropertyAdapter
    : public rti::core::PODNativeAdapter<DDS_WaitSetProperty_t> {
public:
    static void initialize(native_type& native_value)
    {
        static const native_type DEFAULT
            = DDS_WaitSetProperty_t_INITIALIZER;
        rti::core::PODNativeAdapter<DDS_WaitSetProperty_t>::initialize(
            native_value); // this sets all to zero
        native_value = DEFAULT;
    }
};

} // close namespace cond

template<>
struct native_type_traits<cond::WaitSetProperty> {
    typedef cond::WaitSetPropertyAdapter adapter_type;
    typedef cond::WaitSetPropertyAdapter::native_type native_type;
};

namespace cond {

/**
 * @ingroup DDSConditionsModule
 * @brief @extension @st_value_type Specifies the dds::core::cond::WaitSet
 * behavior for multiple trigger events
 *
 * @details \dref_details_WaitSetProperty_t
 */
class OMG_DDS_API WaitSetProperty : public rti::core::NativeValueType<WaitSetProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(WaitSetProperty)

    /**
     * @brief Creates the default WaitSetProperty
     */
    WaitSetProperty();

    /**
     * @brief Creates a WaitSetProperty with the given parameters
     */
    WaitSetProperty(
        int32_t the_max_event_count,
        const dds::core::Duration& the_max_event_delay);

    /**
     * @brief Gets the max_event_count
     * @see max_event_count(int32_t)
     */
    int32_t max_event_count() const;

    /**
     * @brief Sets the maximum number of trigger events to cause a WaitSet to
     * wake up.
     *
     * @details \dref_details_WaitSetProperty_t_max_event_count
     */
    WaitSetProperty& max_event_count(int32_t value);

    /**
     * @brief Gets the max_event_delay
     * @see max_event_delay(const dds::core::Duration&)
     */
    dds::core::Duration max_event_delay() const;

    /**
     * @brief Sets the maximum delay from occurrence of first trigger event to
     * cause a WaitSet to wake up.
     *
     * @details \dref_details_WaitSetProperty_t_max_event_delay
     */
    WaitSetProperty& max_event_delay(const dds::core::Duration& value);
};

/**
 * @RTI_class_definition NA
 */
class OMG_DDS_API WaitSetImpl {
public:
    typedef std::vector<dds::core::cond::Condition> ConditionSeq;

    WaitSetImpl();

    // Note: this is documented in the standard header
    WaitSetImpl(const WaitSetProperty& property);

    ~WaitSetImpl();

    const ConditionSeq wait(const dds::core::Duration& timeout);
    const ConditionSeq wait();
    ConditionSeq& wait(ConditionSeq& triggered,
      const dds::core::Duration& timeout);
    ConditionSeq& wait(ConditionSeq& triggered);

    void dispatch();
    void dispatch(const dds::core::Duration& timeout);
    void dispatch_simple(const dds::core::Duration& timeout); // Extension

    WaitSetImpl& attach_condition(dds::core::cond::Condition cond);
    bool detach_condition(dds::core::cond::Condition cond);

    /**
     * @memberof dds::core::cond::WaitSet
     *
     * @brief @extension Detaches all the conditions.
     */
    void detach_all(); // Extension

    ConditionSeq conditions() const;
    ConditionSeq& conditions(ConditionSeq& conds) const;

    /**
     * @memberof dds::core::cond::WaitSet
     *
     * @brief @extension Gets the WaitSetProperty
     */
    rti::core::cond::WaitSetProperty property() const;

    /**
     * @memberof dds::core::cond::WaitSet
     *
     * @brief @extension Sets the property to configure the WaitSet to return after one
     * or more trigger events have occurred.
     */
    void property(const rti::core::cond::WaitSetProperty& property);

private:
    DDS_WaitSet * native_waitset_;
};

} } } // namespace rti::core::cond

#endif // RTI_DDS_CORE_COND_WAITSET_HPP_

