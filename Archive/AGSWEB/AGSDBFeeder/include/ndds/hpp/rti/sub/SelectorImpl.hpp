/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.7a,25ap14,eam Created
===================================================================== */

#ifndef RTI_DDS_SUB_SELECTOR_IMPL_HPP_
#define RTI_DDS_SUB_SELECTOR_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/sub/cond/ReadCondition.hpp>
#include <dds/sub/Query.hpp>
#include <dds/sub/LoanedSamples.hpp>

namespace rti { namespace sub {

// This type is used to force the template constructor of the SelectorState to 
// to be used. Otherwise, compilation fails with msg like "no acceptable default
// constructor for SelectorState"
template<typename T>
struct emptySelectorType {};

class SelectorState {
public:
    template<typename T>
    SelectorState(const emptySelectorType<T>&)
    : instance_handle(dds::core::InstanceHandle::nil()),
      next_instance(false),
      query(dds::sub::DataReader<T>(dds::core::null_type()), ""),
      max_samples(dds::core::LENGTH_UNLIMITED),
      read_mode(false)
    {
    }

    dds::core::InstanceHandle instance_handle;
    bool next_instance;
    dds::sub::status::DataState data_state;
    dds::sub::Query query;
    dds::core::smart_ptr_traits<rti::sub::cond::ReadConditionImpl>::ref_type condition;
    int32_t max_samples;
    bool read_mode;
};

// A selector without a reference to a DataReader
template <typename T>
class DefaultSelector {
public:
    DefaultSelector()
      : state_(emptySelectorType<T>())
    {
    }

    const SelectorState& get_selector_state() const
    {
        return state_;
    }

    // These is the only setter defined because it's the only one we need 
    // (at the moment) for the DefaultSelector
    DefaultSelector& max_samples(int32_t the_max_samples)
    {
        state_.max_samples = the_max_samples;
        return *this;
    }

    DefaultSelector& state(const dds::sub::status::DataState& data_state)
    {
        state_.data_state = data_state;
        return *this;
    }

private:
    SelectorState state_;
};

// A Selector with a reference to a DataReader
template <typename T>
class Selector : public DefaultSelector<T> {

    typedef typename dds::core::smart_ptr_traits<rti::sub::DataReaderImpl<T> >::ref_type DATA_READER_PTR;
public:
    Selector(DATA_READER_PTR reader)
      : reader_(reader),
        state_(emptySelectorType<T>())
    {
    }

    Selector& instance(const dds::core::InstanceHandle& instance_handle)
    {
        state_.next_instance = false;
        state_.instance_handle = instance_handle;
        return *this;
    }

    Selector& next_instance(const dds::core::InstanceHandle& instance_handle)
    {
        state_.next_instance = true;
        state_.instance_handle = instance_handle;
        return *this;
    }

    Selector& state(const dds::sub::status::DataState& data_state)
    {
        state_.data_state = data_state;
        return *this;
    }

    Selector& content(const dds::sub::Query& content_query)
    {
        state_.query = content_query;

        // Don't use any previously set conditions
        state_.condition.reset();
        return *this;
    }

    Selector& condition(const dds::sub::cond::ReadCondition& the_condition)
    {
        state_.condition = the_condition.delegate();

        // Clear the Query and State information
        state_.query = dds::sub::Query(
           dds::sub::DataReader<T>(dds::core::null_type()), "");
        state_.data_state = dds::sub::status::DataState();

        return *this;
    }

    Selector& max_samples(int32_t the_max_samples)
    {
        state_.max_samples = the_max_samples;
        return *this;
    }

    dds::sub::LoanedSamples<T> read()
    {
        return reader_->read_or_take(state_, false);
    }

    dds::sub::LoanedSamples<T> take()
    {
        return reader_->read_or_take(state_, true);
    }

    // --- Forward Iterators: --- //
    template<typename SamplesFWIterator>
    uint32_t read(SamplesFWIterator sfit, int32_t the_max_samples)
    {
        SelectorState tmp_state(state_);
        tmp_state.max_samples = the_max_samples;

        return reader_->read_or_take(sfit, tmp_state, false);
    }

    template<typename SamplesFWIterator>
    uint32_t take(SamplesFWIterator sfit, int32_t the_max_samples)
    {
        SelectorState tmp_state(state_);
        tmp_state.max_samples = the_max_samples;

        return reader_->read_or_take(sfit, tmp_state, true);
    }

    // --- Back-Inserting Iterators: --- //
    template<typename SamplesBIIterator>
    uint32_t read(SamplesBIIterator sbit)
    {
        return reader_->read_or_take(sbit, state_, false);
    }

    template<typename SamplesBIIterator>
    uint32_t take(SamplesBIIterator sbit)
    {
        return reader_->read_or_take(sbit, state_, true);
    }

private:
    // Store a smart pointer so that if the DataReader goes out of scope
    // the selector will keep it around and will not be left in an
    // inconsistent state
    DATA_READER_PTR reader_;
    SelectorState state_;
};

/**
 * Selector class enabling the streaming API.
 */
template <typename T>
class ManipulatorSelector : public DefaultSelector<T> {
    typedef typename dds::core::smart_ptr_traits<rti::sub::DataReaderImpl<T> >::ref_type DATA_READER_PTR;
public:
    ManipulatorSelector(DATA_READER_PTR dr)
    : reader_(dr),
      state_(emptySelectorType<T>())
    {
    }

    bool read_mode()
    {
        return state_.read_mode;
    }

    void read_mode(bool b)
    {
        state_.read_mode = b;
    }

    ManipulatorSelector& max_samples(int32_t n)
    {
        state_.max_samples = n;
        return *this;
    }

    ManipulatorSelector& instance(const dds::core::InstanceHandle& h)
    {
        state_.next_instance = false;
        state_.instance_handle = h;
        return *this;
    }

    ManipulatorSelector& next_instance(const dds::core::InstanceHandle& h)
    {
        state_.next_instance = true;
        state_.instance_handle = h;
        return *this;
    }

    ManipulatorSelector& state(const dds::sub::status::DataState& s)
    {
        state_.data_state = s;
        return *this;
    }

    ManipulatorSelector& content(const dds::sub::Query& query)
    {
        state_.query = query;

        // Don't use any previously set conditions
        state_.condition.reset();
        return *this;
    }

    ManipulatorSelector& condition(
       const dds::sub::cond::ReadCondition& the_condition)
    {
        state_.condition = the_condition.delegate();

        // Clear the Query and State information
        state_.query = dds::sub::Query(
           dds::sub::DataReader<T>(dds::core::null_type()), "");
        state_.data_state = dds::sub::status::DataState();

        return *this;
    }

    dds::sub::LoanedSamples<T> read()
    {
        return reader_->read_or_take(state_, false);
    }

    dds::sub::LoanedSamples<T> take()
    {
        return reader_->read_or_take(state_, true);
    }

private:
    DATA_READER_PTR reader_;
    SelectorState state_;
};

namespace functors {

class MaxSamplesManipulatorFunctor {
public:
    MaxSamplesManipulatorFunctor(uint32_t n)
    : max_samples_(n)
    {
    }

    template<typename T>
    void operator()(rti::sub::ManipulatorSelector<T>& ms)
    {
        ms.max_samples(max_samples_);
    }
private:
    int32_t max_samples_;
};

class ContentFilterManipulatorFunctor {
public:
    ContentFilterManipulatorFunctor(const dds::sub::Query& query)
    : query_(query)
    {
    }

    template<typename T>
    void operator()(rti::sub::ManipulatorSelector<T>& ms)
    {
        ms.content(query_);
    }
private:
    const dds::sub::Query& query_;
};

class ConditionManipulatorFunctor {
public:
    ConditionManipulatorFunctor(
       const dds::sub::cond::ReadCondition& condition)
    : condition_(condition)
    {
    }

    template<typename T>
    void operator()(rti::sub::ManipulatorSelector<T>& ms)
    {
        ms.condition(condition_);
    }
private:
    const dds::sub::cond::ReadCondition& condition_;
};

class StateFilterManipulatorFunctor {
public:
    StateFilterManipulatorFunctor(const dds::sub::status::DataState& s)
    : state_(s)
    {
    }

    template<typename T>
    void operator()(rti::sub::ManipulatorSelector<T>& ms)
    {
        ms.state(state_);
    }
private:
    const dds::sub::status::DataState& state_;
};

class InstanceManipulatorFunctor {
public:
    InstanceManipulatorFunctor(const dds::core::InstanceHandle& h)
    : instance_(h)
    {
    }

    template<typename T>
    void operator()(rti::sub::ManipulatorSelector<T>& ms)
    {
        ms.instance(instance_);
    }
private:
    const dds::core::InstanceHandle& instance_;
};

class NextInstanceManipulatorFunctor {
public:
    NextInstanceManipulatorFunctor(const dds::core::InstanceHandle& h)
    : next_instance_(h)
    {
    }

    template<typename T>
    void operator()(rti::sub::ManipulatorSelector<T>& ms)
    {
        ms.next_instance(next_instance_);
    }
private:
    const dds::core::InstanceHandle& next_instance_;
};

} // namespace functors

} } // namespace rti::sub

#endif // RTI_DDS_SUB_SELECTOR_IMPL_HPP_
