/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,14mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_PUB_FLOWCONTROLLER_HPP_
#define RTI_DDS_PUB_FLOWCONTROLLER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <rti/core/Cookie.hpp>
#include <rti/core/Exception.hpp>
#include <dds/domain/DomainParticipant.hpp>

namespace rti { namespace pub {

/**
 * @ingroup DDSFlowControllerModule
 * @brief @extension Kinds of flow controller shceduling policy
 * @details \dref_details_FlowControllerSchedulingPolicy
 * @see \ref rti::pub::FlowControllerSchedulingPolicy The safe enumeration for
 * this type
 */
struct FlowControllerSchedulingPolicy_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * @brief Indicates to flow control in a round-robin fashion
         *
         * @details \dref_details_FlowControllerSchedulingPolicy_RR_FLOW_CONTROLLER_SCHED_POLICY
         */
        ROUND_ROBIN,

        /**
         * @brief Indicates to flow control in an earliest-deadline-first fashion
         *
         * @details \dref_details_FlowControllerSchedulingPolicy_EDF_FLOW_CONTROLLER_SCHED_POLICY
         */
        EARLIEST_DEADLINE_FIRST,
        /**
         * @brief Indicates to flow control in a highest-priority-first fashion.
         *
         * @details \dref_details_FlowControllerSchedulingPolicy_HPF_FLOW_CONTROLLER_SCHED_POLICY
         */
        HIGHEST_PRIORITY_FIRST
    };
};

/**
 * @ingroup DDSFlowControllerModule
 * @brief @extension The safe enumeration for
 * FlowControllerSchedulingPolicy_def::type
 *
 * @see FlowControllerSchedulingPolicy_def
 */
typedef dds::core::safe_enum<FlowControllerSchedulingPolicy_def>
    FlowControllerSchedulingPolicy;

class FlowControllerTokenBucketProperty;
class FlowControllerProperty;

class FlowControllerTokenBucketPropertyAdapter
    : public rti::core::PODNativeAdapter<DDS_FlowControllerTokenBucketProperty_t> {
public:
    static void initialize(native_type& native_value)
    {
        static const native_type DEFAULT
            = DDS_FlowControllerTokenBucketProperty_t_INITIALIZER;
        rti::core::PODNativeAdapter<DDS_FlowControllerTokenBucketProperty_t>::initialize(
            native_value); // this sets all to zero
        native_value = DEFAULT;
    }
};

class FlowControllerPropertyAdapter
    : public rti::core::PODNativeAdapter<DDS_FlowControllerProperty_t> {
public:
    static void initialize(native_type& native_value)
    {
        static const native_type DEFAULT
            = DDS_FlowControllerProperty_t_INITIALIZER;
        rti::core::PODNativeAdapter<DDS_FlowControllerProperty_t>::initialize(
            native_value); // this sets all to zero
        native_value = DEFAULT;
    }
};

} // namespace pub

namespace core {

template<>
struct native_type_traits<rti::pub::FlowControllerTokenBucketProperty> {
    typedef rti::pub::FlowControllerTokenBucketPropertyAdapter adapter_type;
    typedef rti::pub::FlowControllerTokenBucketPropertyAdapter::native_type native_type;
};

template<>
struct native_type_traits<rti::pub::FlowControllerProperty> {
    typedef rti::pub::FlowControllerPropertyAdapter adapter_type;
    typedef rti::pub::FlowControllerPropertyAdapter::native_type native_type;
};

} // namespace core

namespace pub {

/**
 * @ingroup DDSFlowControllerModule
 * @brief @extension @st_value_type Configures a FlowController based on a
 * tocken-bucket mechanism
 *
 * \dref_FlowControllerTokenBucketProperty_t
 */
class OMG_DDS_API FlowControllerTokenBucketProperty
    : public rti::core::NativeValueType<FlowControllerTokenBucketProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(FlowControllerTokenBucketProperty)

    /**
     * @brief Initializes the properties
     */
    FlowControllerTokenBucketProperty(
        int32_t max_tokens = dds::core::LENGTH_UNLIMITED,
        int32_t tokens_added_per_period = dds::core::LENGTH_UNLIMITED,
        int32_t tokens_leaked_per_period = 0,
        const dds::core::Duration& period = dds::core::Duration(1, 0),
        int32_t bytes_per_token = dds::core::LENGTH_UNLIMITED);

    /**
     * @brief Gets the max_tokens
     * @see max_tokens(int32_t)
     */
    int32_t max_tokens() const;
    /**
     * @brief Sets the maximum number of tokens that can accumulate in the token bucket.
     * @details \dref_details_FlowControllerTokenBucketProperty_t_max_tokens
     * @return *this
     */
    FlowControllerTokenBucketProperty& max_tokens(int32_t value);

    /**
     * @brief Gets the tokens_added_per_period
     * @see tokens_added_per_period(int32_t)
     */
    int32_t tokens_added_per_period() const;
    /**
     * @brief Sets the number of tokens added to the token bucket per specified period.
     * @details \dref_details_FlowControllerTokenBucketProperty_t_tokens_added_per_period
     * @return *this
     */
    FlowControllerTokenBucketProperty& tokens_added_per_period(int32_t value);

    /**
     * @brief Gets the tokens_leaked_per_period
     * @see tokens_leaked_per_period(int32_t)
     */
    int32_t tokens_leaked_per_period() const;
    /**
     * @brief Sets the number of tokens removed from the token bucket per specified period.
     * @details \dref_details_FlowControllerTokenBucketProperty_t_tokens_leaked_per_period
     * @return *this
     */
    FlowControllerTokenBucketProperty& tokens_leaked_per_period(int32_t value);

    /**
     * @brief Gets the period
     * @see period(const dds::core::Duration&)
     */
    dds::core::Duration period() const;
    /**
     * @brief Sets the period for adding tokens to and removing tokens from the bucket.
     * @details \dref_details_FlowControllerTokenBucketProperty_t_period
     * @return *this
     */
    FlowControllerTokenBucketProperty& period(
        const dds::core::Duration& value);

    /**
     * @brief Gets the bytes_per_token
     * @see bytes_per_token(int32_t)
     */
    int32_t bytes_per_token() const;
    /**
     * @brief Sets the maximum number of bytes allowed to send for each token available.
     * @details \dref_details_FlowControllerTokenBucketProperty_t_bytes_per_token
     * @return *this
     */
    FlowControllerTokenBucketProperty& bytes_per_token(int32_t value);
};

/**
 * @ingroup DDSFlowControllerModule
 * @brief @extension @st_value_type Configures a FlowController
 *
 * @details \dref_details_FlowControllerProperty_t
 *
 */
class OMG_DDS_API FlowControllerProperty
    : public rti::core::NativeValueType<FlowControllerProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(FlowControllerProperty)

    /**
     * @brief Creates a FlowControllerProperty with earliest-deadline-first
     * scheduling policy and default token-bucket configuration
     */
    FlowControllerProperty() {}

    /**
     * @brief Creates a FlowControllerProperty with the specified scheduling
     * policy and token-bucket configuration
     *
     * @param scheduling_policy The scheduling policy
     * @param token_bucket The token-bucket configuration
     */
    FlowControllerProperty(
        FlowControllerSchedulingPolicy::type scheduling_policy,
        const FlowControllerTokenBucketProperty& token_bucket
            = FlowControllerTokenBucketProperty());

    /**
     * @brief Gets the scheduling policy
     */
    FlowControllerSchedulingPolicy::type scheduling_policy() const;

    /**
     * @brief Sets the scheduling policy
     * @return *this
     */
    FlowControllerProperty& scheduling_policy(
        FlowControllerSchedulingPolicy::type value);

    /**
     * @brief Gets the token-bucket configuration by reference
     */
    FlowControllerTokenBucketProperty& token_bucket();

    /**
     * @brief Gets the token-bucket configuration by const-reference
     */
    const FlowControllerTokenBucketProperty& token_bucket() const;

    /**
     * @brief Creates a FlowControllerProperty with round-robin scheduling policy
     * and default token-bucket configuration
     *
     * @see FlowControllerSchedulingPolicy_def::ROUND_ROBIN
     */
    static FlowControllerProperty RoundRobin()
    {
        return FlowControllerProperty(
            FlowControllerSchedulingPolicy::ROUND_ROBIN);
    }

    /**
     * @brief Creates a FlowControllerProperty with earliest-deadline-first scheduling policy
     * and default token-bucket configuration
     *
     * @see FlowControllerSchedulingPolicy_def::EARLIEST_DEADLINE_FIRST
     */
    static FlowControllerProperty EarliestDeadlineFirst()
    {
        return FlowControllerProperty(
            FlowControllerSchedulingPolicy::EARLIEST_DEADLINE_FIRST);
    }

    /**
     * @brief Creates a FlowControllerProperty with highest-priority-first scheduling policy
     * and default token-bucket configuration
     *
     * @see FlowControllerSchedulingPolicy_def::HIGHEST_PRIORITY_FIRST
     */
    static FlowControllerProperty HighestPriorityFirst()
    {
        return FlowControllerProperty(
            FlowControllerSchedulingPolicy::HIGHEST_PRIORITY_FIRST);
    }
};

class OMG_DDS_API FlowControllerImpl
    : public rti::core::detail::RetainableType<FlowControllerImpl> {
public:
    FlowControllerImpl(
        dds::domain::DomainParticipant participant,
        const std::string& name,
        const FlowControllerProperty& property);

    FlowControllerImpl(DDS_FlowController * native_fc);

    ~FlowControllerImpl();
    void close();
    bool closed() const;

    std::string name() const;
    dds::domain::DomainParticipant participant() const;
    FlowControllerProperty property() const;
    void property(const FlowControllerProperty& value);
    void trigger_flow();
    bool is_builtin() const;


    void remember_reference(ref_type reference);

private:
    void assert_not_closed() const
    {
        if (closed()) {
            throw dds::core::AlreadyClosedError("FlowController already closed");
        }
    }

    dds::domain::DomainParticipant participant_;
    DDS_FlowController * native_;
};

/**
 * @ingroup DDSFlowControllerModule
 *
 * @brief @extension @st_ref_type A flow controller is the object responsible for
 * shaping the network traffic by determining when attached asynchronous
 * dds::pub::DataWriter instances are allowed to write data.
 *
 */
class OMG_DDS_API FlowController : public dds::core::Reference<FlowControllerImpl> {
public:
    typedef dds::core::Reference<FlowControllerImpl> Base;

    OMG_DDS_REF_TYPE_NOTYPENAME(FlowController, dds::core::Reference, FlowControllerImpl)

    /**
     * @brief Name that identifies the built-in default FlowController
     *
     * @details \dref_details_DEFAULT_FLOW_CONTROLLER_NAME
     */
    static OMG_DDS_API_CLASS_VARIABLE const std::string DEFAULT_NAME;

    /**
     * @brief Name that identifies the built-in fixed-rate FlowController
     *
     * @details \dref_details_FIXED_RATE_FLOW_CONTROLLER_NAME
     */
    static OMG_DDS_API_CLASS_VARIABLE const std::string FIXED_RATE_NAME;

    /**
     * @brief Name that identifies the built-in on-demand FlowController
     *
     * @details \dref_details_ON_DEMAND_FLOW_CONTROLLER_NAME
     */
    static OMG_DDS_API_CLASS_VARIABLE const std::string ON_DEMAND_NAME;

    /**
     * @brief Creates a FlowController with specific properties
     *
     * @param the_participant The DomainParticipant where this FlowController exists
     * @param the_name Name to refer to this FlowController
     * @param the_property Determines how to shape the network traffic
     *
     * @details \dref_details_DomainParticipant_create_flowcontroller
     */
    FlowController(
        dds::domain::DomainParticipant the_participant,
        const std::string& the_name,
        const FlowControllerProperty& the_property = FlowControllerProperty())
        : Base(new FlowControllerImpl(the_participant, the_name, the_property))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    explicit FlowController(Base::DELEGATE_REF_T reference) : Base(reference)
    {
        if (this->delegate()) {
            this->delegate()->remember_reference(this->delegate());
        }
    }

    /**
     * @brief Gets the name of this FlowController
     */
    std::string name() const
    {
        return this->delegate()->name();
    }

    /**
     * @brief Gets the participant associated to this FlowController
     */
    dds::domain::DomainParticipant participant() const
    {
        return this->delegate()->participant();
    }

    /**
     * @brief Gets the configuration of this FlowController
     */
    FlowControllerProperty property() const
    {
        return this->delegate()->property();
    }

    /**
     * @brief Gets the configuration of this FlowController
     *
     * @details \dref_details_FlowController_set_property
     */
    void property(const FlowControllerProperty& prop) const
    {
        this->delegate()->property(prop);
    }

    /**
     * @brief Provides an external way to trigger a FlowController
     *
     * @details \dref_details_FlowController_trigger_flow
     */
    void trigger_flow()
    {
        this->delegate()->trigger_flow();
    }

    /**
     * @brief Disables the automatic destruction of this object
     *
     * Disables the automatic destruction of the underlying FlowController when
     * when there are no more references to it. After that it can be looked up
     * using rti::pub::lookup_flow_controller
     *
     * To delete a retained object, manually call close()
     *
     */
    void retain()
    {
        this->delegate()->retain();
    }

    /**
     * @brief Manually destroys this object
     *
     * Destroys the object referenced by this FlowController reference.
     *
     * After closing it, any calls to this object through this or other
     * references throw dds::core::AlreadyClosedError.
     *
     * @see retain()
     */
    void close()
    {
        this->delegate()->close();
    }

    /**
     * @brief Returns true if this FlowController has been closed
     *
     * The FlowController may have been closed either by calling close() or
     * by closing the related DomainParticipant.
     */
    bool closed() const
    {
        return this->delegate()->closed();
    }
};

/**
 * @relatesalso rti::pub::FlowController
 * @brief Retrieves an existing FlowController
 *
 * @param participant The DomainParticipant associated to the FlowController
 * @param name The name used to create the FlowController or the name of one
 * of the built-in FlowControllers (FlowController::DEFAULT_NAME,
 * FlowController::FIXED_RATE_NAME, FlowController::ON_DEMAND_NAME)
 *
 * @return The flow controller with that name in that participant or
 *         an empty reference (equals to dds::core::null) if it doesn't exist
 * @see FlowController::retain()
 */
OMG_DDS_API
FlowController find_flow_controller(
    dds::domain::DomainParticipant participant,
    const std::string& name);

} } // namespace rti::pub

#endif // RTI_DDS_PUB_FLOWCONTROLLER_HPP_
