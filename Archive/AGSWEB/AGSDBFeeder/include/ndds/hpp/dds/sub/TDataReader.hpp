#ifndef OMG_DDS_SUB_TDATA_READER_HPP_
#define OMG_DDS_SUB_TDATA_READER_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/topic/topicfwd.hpp>
#include <dds/topic/TopicInstance.hpp> // returned by some defined functions
#include <dds/sub/qos/DataReaderQos.hpp> // returned by some defined functions
#include <dds/core/TEntity.hpp> // Used as base class
#include <dds/sub/LoanedSamples.hpp> // returned by some defined functions
#include <dds/sub/subfwd.hpp> // forward declares

namespace dds { namespace sub {

class Query;

template<typename T, template<typename Q> class DELEGATE>
class DataReader;

template<typename T>
class DataReaderListener;

/** 
 * @relatesalso dds::sub::DataReader::ManipulatorSelector 
 *  
 * This type is used by the read() and take() functions
 * that are meant to be passed to the ManipulatorSelector. It 
 * makes sure that the user can't pass any function which takes 
 * 0 arguments 
 *  
 * @see dds::sub::read(dds::sub::ReadModeDummyType)
 * @see dds::sub::take(dds::sub::ReadModeDummyType)
 */ 
class ReadModeDummyType {};

} }

/** 
 * @ingroup DDSReaderModule 
 * @RTI_class_definition template <typename T> class dds::sub::DataReader : public dds::core::Entity
 * @headerfile "dds/sub/DataReader.hpp"
 * 
 * @brief @st_ref_type Allows the application to: 
 * (1) declare the data it wishes to receive (i.e. make a subscription) and 
 * (2) access the data received by the attached dds::sub::Subscriber.
 *  
 * @tparam T The topic-type that the DataReader subscribes to 
 *  
 * @details \dref_details_DataReader 
 *  
 * @see \ref DDSReaderExampleModule 
 * @see \ref DDSEntityExampleModuleForCpp2 
 */
template<typename T, template<typename Q> class DELEGATE>
class dds::sub::DataReader : public dds::core::TEntity<DELEGATE<T> > {

public:
    typedef T DataType;
    typedef dds::sub::DataReaderListener<T> Listener;

public:

    // --- Selector and Manipulator classes: ----------------------------------

    /** 
     * @ingroup DDSReaderModule  
     * @brief The Selector class is used by the DataReader to compose 
     * read and take operations. 
     *  
     * A Selector has an associated DataReader and configures
     * the behavior of the read or take operation performed by that DataReader. 
     *   
     * For example, to perform a read of at most 5 unread samples: 
     *  
     * \code 
     * LoanedSamples<Foo> samples = reader.select() 
     *       .read()
     *       .max_samples(5)
     *       .state(dds::sub::status::DataState::new_data());
     * \endcode
     *  
     * @see \ref DDSReaderExampleModule_receive 
     */ 
    class Selector {
    public:

        /**
         * @brief Create a Selector for this DataReader
         *  
         * Selectors are created with the default filter state of the DataReader 
         *  
         * @param dr The DataReader that this Selector is attached to 
         *  
         * @see dds::sub::DataReader::default_filter_state() 
         */
        Selector(DataReader& dr)
          : impl_(dr.delegate())
        {
            state(dr.default_filter_state());
        }

        /**
         * @brief Select a specific instance to read/take 
         *  
         * This operation causes the subsequent read or take operation to 
         * access only  samples belonging the single specified instance 
         * whose handle is \p h. 
         *  
         * Upon successful completion, the data collection will contain
         * samples all belonging to the same instance. The corresponding 
         * SampleInfo  verifies SampleInfo.instance_handle() == \p h. 
         *  
         * The subsequent read/take operation will be semantically equivalent to 
         * a read or take without specifying the instance, except in 
         * building the collection, the DataReader will check that the sample 
         * belongs  to the specified instance and otherwise it will not place 
         * the sample in the returned collection. 
         *  
         * The subsequent read/take may operation may fail with
         * dds::core::InvalidArgumentError if the InstanceHandle does not 
         * correspond to an existing data-object known to the DataReader. 
         * 
         * @param h The handle of the instance to select
         */
        Selector& instance(const dds::core::InstanceHandle& h)
        {
            impl_.instance(h);
            return *this;
        }

        // Spec issue: this method was missing
        /**
         * @brief Select the instance after a specific instance 
         *  
         * \dref_details_FooDataReader_read_next_instance 
         *  
         * @param h The reference instance. The instance after this one will 
         * be selected  
         */
        Selector& next_instance(const dds::core::InstanceHandle& h)
        {
            impl_.next_instance(h);
            return *this;
        }

        /**
         * @brief Select a specific DataState 
         *  
         * By setting the DataState you can specify the state of the samples 
         * that should be read or taken. The DataState of a sample encapsulates 
         * the SampleState, ViewState, and InstanceState of a sample. 
         *  
         * If this method comes before a call to condition() then it will be 
         * overridden and will not have any effect on the read or take 
         * operation. 
         * 
         * @param s The selected DataState
         */
        Selector& state(const dds::sub::status::DataState& s)
        {
            impl_.state(s);
            return *this;
        }

        /**
         * @brief Select samples based on a Query
         * 
         * The effect of using this manipulator is that the subsequent 
         * read/take will filter the samples based on the Query's expression. 
         * If the DataReader has no samples that meet the constraints, the 
         * read/take will not return any data. 
         *  
         * If this method is called before a call to condition 
         * then it will be overridden and will not have any effect on the 
         * read or take operation. Similarly, if this operation follows a 
         * call to condition(), then the previously set ReadCondition will be
         * cleared. 
         *  
         * @param query The Query to read/take with
         */
        Selector& content(const dds::sub::Query& query)
        {
            impl_.content(query);
            return *this;
        }

        // Spec issue: this method was missing
        /**
         * @brief Select samples based on a ReadCondition
         *  
         * When passing a QueryCondition, the effect of calling this method is
         * that the subsequent read/take will filter the samples based on the
         * QueryConditions's expression and state. If the DataReader has no
         * samples that meet the constraints, the read/take will not return any
         * data.
         *
         * Passing an actual ReadCondition will only filter based on the state.
         *  
         * If this method is called before a call to content then it will be 
         * overridden and will not have any effect on the read or take 
         * operation. Similarly, if this operation follows a call to content() 
         * and/or state, then the previously set Query and DataState will be 
         * cleared. 
         *  
         * This method is effectively a combination of calling content and state,
         * but a QueryCondition is more efficient when reading with the same query
         * multiple times.
         *  
         * For example: 
         * @code
         * samples = reader.select() 
         *                 .read()
         *                 .content(dds::sub::Query(system.reader, "foo = 7"))
         *                 .state(dds::sub::status::DataState::new_data())
         * @endcode
         *  
         * is equivalent to: 
         * @code
         * samples = reader.select() 
         *                 .read()
         *                 .condition(QueryCondition(Query(system.reader, "foo = 7"), DataState::new_data()))
         * @endcode
         * 
         * @param the_condition The ReadCondition (or QueryCondition) to read/take with
         */
        Selector& condition(
           const dds::sub::cond::ReadCondition& the_condition)
        {
            impl_.condition(the_condition);
            return *this;
        }

        /**
         * @brief Choose to only read/take up to a maximum number of samples
         * 
         * @param n The maximum number of samples to read/take
         */
        Selector& max_samples(int32_t n)
        {
            impl_.max_samples(n);
            return *this;
        }

        /**
         * @brief Read samples based on the state associated with this Selector
         * 
         * @return dds::sub::LoanedSamples<T> 
         */
        dds::sub::LoanedSamples<T> read()
        {
            return impl_.read();
        }

        /**
         * @brief Take samples based on the state associated with this Selector
         * 
         * @return dds::sub::LoanedSamples<T> 
         */
        dds::sub::LoanedSamples<T> take()
        {
            return impl_.take();
        }

        // --- Forward Iterators: --- //
        /**
         * @brief Read up to max_samples samples, inserting the samples into 
         * a provided container 
         * 
         * @tparam SamplesFWIterator A forward iterator whose value type is 
         * dds::sub::Sample<T> 
         * @param sfit A forward iterator pointing to the position in a
         * container in which to put the read samples
         * @param the_max_samples The maximum number of samples to read
         * 
         * @return uint32_t The number of read samples
         */
        template<typename SamplesFWIterator>
        uint32_t
        read(SamplesFWIterator sfit, int32_t the_max_samples)
        {
            return impl_.read(sfit, the_max_samples);
        }

        /**
         * @brief Take up to max_samples samples, inserting the samples into 
         * a provided container
         * 
         * @tparam SamplesFWIterator A forward iterator whose value type is 
         * dds::sub::Sample<T> 
         * @param sfit A forward iterator pointing to the position in a
         * container in which to put the taken samples
         * @param the_max_samples The maximum number of samples to take
         * 
         * @return uint32_t The number of taken samples
         */
        template<typename SamplesFWIterator>
        uint32_t
        take(SamplesFWIterator sfit, int32_t the_max_samples)
        {
            return impl_.take(sfit, the_max_samples);
        }

        // --- Back-Inserting Iterators: --- //
        /**
         * @brief Read samples, inserting them into a provided contianer
         * 
         * @tparam SamplesBIIterator A back-inserting iterator whose value type 
         * is dds::sub::Sample<T> 
         * @param sbit A back-inserting iterator placed at the position in the 
         * destination container where the read samples should be placed 
         * 
         * @return uint32_t The number of samples that were read
         */
        template<typename SamplesBIIterator>
        uint32_t
        read(SamplesBIIterator sbit)
        {
            return impl_.read(sbit);
        }

        /**
         * @brief Take samples, inserting them into a provided contianer
         * 
         * @tparam SamplesBIIterator A back-inserting iterator whose value type 
         * is dds::sub::Sample<T> 
         * @param sbit A back-inserting iterator placed at the position in the 
         * destination container where the taken samples should be placed 
         * 
         * @return uint32_t The number of samples that were taken
         */
        template<typename SamplesBIIterator>
        uint32_t
        take(SamplesBIIterator sbit)
        {
            return impl_.take(sbit);
        }

    private:
        typename DELEGATE<T>::Selector impl_;
    };

    /** 
     * @ingroup DDSReaderModule
     * @brief A Selector class enabling the streaming API. 
     *  
     * Similar to the Selector class, the ManipulatorSelector class is used by 
     * the DataReader to compose read and take operations using the streaming 
     * operator >>.  
     *  
     * A ManipulatorSelector has an associated DataReader and configures
     * the behavior of the read or take operation performed by that DataReader. 
     *  
     * The ManipulatorSelector works by using a number of functions which 
     * configure the stream: 
     * - read(dds::sub::ReadModeDummyType)
     * - take(dds::sub::ReadModeDummyType) 
     * - dds::sub::max_samples(uint32_t n) 
     * - dds::sub::content(const dds::sub::Query& query) 
     * - dds::sub::condition(const dds::sub::cond::ReadCondition& condition)
     * - dds::sub::state(const dds::sub::status::DataState& s) 
     * - dds::sub::instance(const dds::core::InstanceHandle& h) 
     * - dds::sub::next_instance(const dds::core::InstanceHandle& h) 
     *  
     * The above functions all return functors. You do not and should not use 
     * these functors directly:
     * - dds::sub::functors::MaxSamplesManipulatorFunctor
     * - dds::sub::functors::ContentFilterManipulatorFunctor
     * - dds::sub::functors::ConditionManipulatorFunctor
     * - dds::sub::functors::StateFilterManipulatorFunctor
     * - dds::sub::functors::InstanceManipulatorFunctor
     * - dds::sub::functors::NextInstanceManipulatorFunctor 
     *     
     * For example, to perform a read of at most 5 unread samples: 
     *  
     * \code 
     * LoanedSamples<Foo> samples; 
     *  
     * reader >> read 
     *        >> max_samples(5)
     *        >> state(dds::sub::status::DataState::new_data())
     *        >> samples;
     * \endcode 
     *  
     * @see \ref DDSReaderExampleModule_receive 
     */
    class ManipulatorSelector {
    public:
        ManipulatorSelector(DataReader& dr)
        : impl_(dr.delegate())
        {
            state(dr.default_filter_state());
        }

        bool read_mode()
        {
            return impl_.read_mode();
        }

        void read_mode(bool b)
        {
            impl_.read_mode(b);
        }

        ManipulatorSelector& max_samples(int32_t n)
        {
            impl_.max_samples(n);
            return *this;
        }

        ManipulatorSelector& instance(const dds::core::InstanceHandle& h)
        {
            impl_.instance(h);
            return *this;
        }

        ManipulatorSelector& next_instance(const dds::core::InstanceHandle& h)
        {
            impl_.next_instance(h);
            return *this;
        }

        ManipulatorSelector& state(const dds::sub::status::DataState& s)
        {
            impl_.state(s);
            return *this;
        }

        ManipulatorSelector& content(const dds::sub::Query& query)
        {
            impl_.content(query);
            return *this;
        }

        ManipulatorSelector& condition(
           const dds::sub::cond::ReadCondition& the_condition)
        {
            impl_.condition(the_condition);
            return *this;
        }

        /**
         * @brief Streaming operator taking a LoanedSamples object
         * 
         * This operator allows you to direct the outcome of a string of 
         * stream operators into a LoanedSamples object.  
         * 
         * @param samples The LoanedSamples container to fill with the 
         * read/taken samples.  
         * 
         */
        ManipulatorSelector& operator >>(dds::sub::LoanedSamples<T>& samples)
        {
            if (read_mode()) {
                samples = impl_.read();
            } else {
                samples = impl_.take();
            }
            return *this;
        }

        /**
         * @brief Streaming operator taking in a stream manipulator that will 
         * determine whether the samples will be read or taken. 
         *  
         * The provided manipulator for this operator will be either 
         * dds::sub::read or dds::sub::take.  
         * 
         * @param manipulator Either dds::sub::read or dds::sub::take
         *  
         * @see dds::sub::read(dds::sub::ReadModeDummyType) 
         * @see dds::sub::take(dds::sub::ReadModeDummyType) 
         */
        ManipulatorSelector&
        operator >>(bool(*manipulator)(ReadModeDummyType))
        {
            read_mode(manipulator(ReadModeDummyType()));
            return *this;
        }

        // Spec error: should return by reference
        /**
         * @brief Streaming operator taking in a Functor. 
         *  
         * There are a number of functions which return the Functors that this 
         * operator expects:
         * 
         * - dds::sub::max_samples(uint32_t n) 
         * - dds::sub::content(const dds::sub::Query& query) 
         * - dds::sub::condition(const dds::sub::cond::ReadCondition& condition)
         * - dds::sub::state(const dds::sub::status::DataState& s) 
         * - dds::sub::instance(const dds::core::InstanceHandle& h) 
         * - dds::sub::next_instance(const dds::core::InstanceHandle& h) 
         * 
         * @param f A Functor that is returned from one of the above functions
         * 
         * @return ManipulatorSelector& 
         */
        template<typename Functor>
        ManipulatorSelector& operator >>(Functor f)
        {
            f(impl_);
            return *this;
        }

    private:
        typename DELEGATE<T>::ManipulatorSelector impl_;
    };

public:
    // --- Construction, destruction and copy: --------------------------------

    OMG_DDS_REF_TYPE(DataReader, dds::core::TEntity, DELEGATE<T>)

    /**
     * @brief Create a DataReader. 
     *  
     * It uses the default DataReaderQos, and no listener.
     *
     * @param sub the Subscriber owning this DataReader.
     * @param topic the Topic associated with this DataReader.
     */
    DataReader(
        const dds::sub::Subscriber& sub,
        const dds::topic::Topic<T>& topic)
        : dds::core::TEntity<DELEGATE<T> >(new DELEGATE<T>(sub, topic))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
     * @brief Create a DataReader. 
     *
     * When a DataReader is created, only those transports already
     * registered are available to the DataReader. See
     * \ref NDDS_TransportBuiltinsComponent for details on when a
     * builtin transport is registered.
     *
     * @mtsafety UNSAFE. If the qos parameter is omitted it is not safe to 
     * create the datareader while another thread may be simultaneously
     * calling dds::sub::Subscriber::default_datareader_qos(dds::sub::qos::DataReaderQos).
     *
     * @pre If sub is enabled, the topic must be enabled. If it is not, 
     * this operation will fail and no DataReader will be created.
     *
     * @pre The given dds::topic::Topic must have been created from the same 
     * participant as this subscriber. If it was created from a different 
     * participant no DataReader will be created.
     * 
     * @param sub the Subscriber owning this DataReader.
     * @param topic the Topic associated with this DataReader.
     * @param the_qos the QoS settings for this DataReader.
     * @param the_listener the listener.
     * @param mask the event mask associated to the DataReader listener.
     *
     * @see \ref DDSQosTypesModule_usage for information on setting QoS before entity creation
     * @see dds::sub::qos::DataReaderQos for rules on consistency among QoS
     * @see dds::core::QosProvider::datareader_qos()
     * @see dds::sub::qos::DataReaderQos::operator=(const dds::topic::qos::TopicQos&) 
     * which allows assigning the contents of a TopicQos into a DataReaderQos
     * @see listener()
     */
    DataReader(
        const dds::sub::Subscriber& sub,
        const dds::topic::Topic<T>& topic,
        const dds::sub::qos::DataReaderQos& the_qos,
        dds::sub::DataReaderListener<T>* the_listener = NULL,
        const dds::core::status::StatusMask& mask =
            dds::core::status::StatusMask::all()) :
            dds::core::TEntity<DELEGATE<T> >(
                new DELEGATE<T>(sub, topic, the_qos, the_listener, mask))
    {
        this->delegate()->remember_reference(this->delegate());
    }

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

    /**
     * @brief Create a DataReader for a dds::topic::ContentFilteredTopic.
     *  
     * This DataReader will only receive that data that matches the Filter 
     * associated with the ContentFilteredTopic. The QoS will be 
     * set to sub.default_datareader_qos(). 
     *
     * @param sub the Subscriber owning this DataReader.
     * @param topic the content filtered topic
     */
    DataReader(
        const dds::sub::Subscriber& sub,
        const dds::topic::ContentFilteredTopic<T>& topic) :
        dds::core::TEntity<DELEGATE<T> >(new DELEGATE<T>(sub, topic))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
     * @brief Create a DataReader for a dds::topic::ContentFilteredTopic.
     *  
     *  This DataReader will only receive that data that mathes the Filter
     *  associated with the ContentFilteredTopic.
     *
     * @param sub the subscriber owning this DataReader.
     * @param topic the content filtered topic.
     * @param the_qos the QoS settings for this DataReader.
     * @param the_listener the listener.
     * @param mask the event mask associated to the DataReader listener.
     */
    DataReader(
        const dds::sub::Subscriber& sub,
        const dds::topic::ContentFilteredTopic<T>& topic,
        const dds::sub::qos::DataReaderQos& the_qos,
        dds::sub::DataReaderListener<T>* the_listener = NULL,
        const dds::core::status::StatusMask& mask =
            dds::core::status::StatusMask::all()) :
            dds::core::TEntity<DELEGATE<T> >(
                new DELEGATE<T>(sub, topic, the_qos, the_listener, mask))
    {
        this->delegate()->remember_reference(this->delegate());
    }

#endif /* OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT */

#ifdef OMG_DDS_MULTI_TOPIC_SUPPORT

    /**
     * @brief Create a DataReader for a MultiTopic.
     *  
     *  This DataReader will only receive that 
     *       data that matches the Filter
     * associated with the ContentFilteredTopic. The 
     * QoS will be set to sub.default_datareader_qos(). 
     *
     * @param sub the subscriber owning this DataReader.
     * @param topic the multi-topic.
     */
    DataReader(
        const dds::sub::Subscriber& sub,
        const dds::topic::MultiTopic<T>& topic);

    /**
     * @brief Create a DataReader for a 
     *        MultiTopic.
     *  
     *  This DataReader will only receive that 
     *       data that mathes the Filter associated
     *       with the ContentFilteredTopic.
     *
     * @param sub the subscriber owning this DataReader.
     * @param topic the multi-topic.
     * @param qos the QoS settings for this DataReader.
     * @param listener the listener.
     * @param mask the event mask associated to the DataReader listener.
     */
    DataReader(
        const dds::sub::Subscriber& sub,
        const dds::topic::MultiTopic<T>& topic,
        const dds::sub::qos::DataReaderQos& qos,
        dds::sub::DataReaderListener<T>* listener = NULL,
        const dds::core::status::StatusMask& mask =
            dds::core::status::StatusMask::all());

#endif /* OMG_DDS_MULTI_TOPIC_SUPPORT */

    // Spec issue CPPPSM-18: need this constructor to make polymorphic_cast work.
    DataReader(
        typename dds::core::smart_ptr_traits<DELEGATE<T> >::ref_type delegate_ref)
        : dds::core::TEntity<DELEGATE<T> >(delegate_ref)
    {
        if (this->delegate()) {
            this->delegate()->remember_reference(this->delegate());
        }
    }

    // Spec error: need this method
    DataReader(dds::core::construct_from_native_tag_t, DELEGATE<T>* the_delegate)
        : dds::core::TEntity<DELEGATE<T> >(the_delegate)
    {
        this->delegate()->remember_reference(this->delegate());
    }

    ~DataReader()
    {
    }

    // --- DataState management: ----------------------------------------------

    /**
     * @brief Returns the default state for read/take operations.
     *  
     * If left as default, it is set to dds::sub::status::DataState::any().
     */
    const dds::sub::status::DataState& default_filter_state()
    {
        return this->delegate()->default_filter_state();
    }

    /**
     * @brief Set the default state filter for read/take operations.
     *
     * @param state the state mask that will be used to read/take samples. 
     */ 

    DataReader& default_filter_state(const dds::sub::status::DataState& state)
    {
        this->delegate()->default_filter_state(state);
        return *this;
    }

    // --- Stream read/take: --------------------------------------------------

    /**
     * @brief Use the stream operator to take samples, placing them into a 
     * LoanedSamples container. 
     *  
     * For example: 
     * @code 
     * reader >> loaned_samples;  
     * @endcode 
     *  
     * If you want to read samples, instead of take, you must use the stream 
     * manipulator read(dds::sub::ReadModeDummyType) and 
     * operator>>(bool(*manipulator)(ReadModeDummyType)) 
     *  
     * For example: 
     * @code 
     * reader >> read >> loaned_samples;  
     * @endcode 
     * 
     * @param ls The LoanedSamples container to put the taken samples into 
     * @see operator>>(bool(*manipulator)(ReadModeDummyType)) 
     * @see operator>>(Functor f) 
     * @see \ref DDSReaderExampleModule_receive 
     */
    DataReader& operator >>(dds::sub::LoanedSamples<T>& ls)
    {
        // Default read_mode is to take
        ls = this->delegate()->take();
        return *this;
    }

    /**
     * @brief Use the stream operator to read or take samples. 
     * 
     * The read and take manipulators are defined externally to make it 
     * possible to control whether the stream operators reads or 
     * takes. 
     *  
     * This stream operator can be chained together with operator>>(Functor f) 
     * to set other various properties of the read/take operation.  
     *  
     * It is used as follows: 
     * @code 
     * dr >> read >> loanedSamples; 
     * dr >> take >> loanedSamples; 
     * @endcode 
     *  
     * If either the read or take manipulator is not passed into the stream, 
     * the default behavior is to take. 
     * 
     * @param manipulator Either read or take 
     *  
     * @see operator>>(Functor f) 
     * @see operator>>(dds::sub::LoanedSamples<T>& ls) 
     * @see ReadModeDummyType 
     * @see \ref DDSReaderExampleModule_receive 
     */
    ManipulatorSelector operator >>(
        bool(*manipulator)(ReadModeDummyType))
    {
        ManipulatorSelector ms(*this);
        // manipulator will be read or take and just set the read_mode
        ms.read_mode(manipulator(ReadModeDummyType()));
        return ms;
    }

    /**
     * @brief Use the stream operator to dictate the behavior of the 
     * read or take operation.  
     * 
     * There are a number of pre-defined stream manipulators (functions which 
     * return a functor that will be used by the stream operator). They 
     * dictate how the samples will be read or taken: 
     *  
     * - max_samples: Read/Take up to a maximum number of samples
     * - content: Read/Take using a Query 
     * - condition: Read/Take using a dds::sub::cond::ReadCondition
     * - state: Read/Take only samples with a specific DataState 
     * - instance: Read/Take a specific instance 
     * - next_instance: Read/Take the next instance after a specified instance 
     *  
     * For example, to read up to 10 samples that have not been read before: 
     * @code 
     * dr >> read 
     *    >> max_samples(10)
     *    >> state(DataState::new_data())
     *    >> loanedSamples;
     * @endcode 
     * 
     * @param f Each of the stream manipulators listed above return a Functor 
     * that will be passed to the stream operator. These Functors do not need 
     * to be accessed by the user directly. They should instead be passed 
     * indirectly via the return value of one of the provided stream manipulators. 
     *  
     * @see dds::sub::max_samples(uint32_t n) 
     * @see dds::sub::content(const dds::sub::Query& query)
     * @see dds::sub::condition(const dds::sub::cond::ReadCondition& query_condition)
     * @see dds::sub::state(const dds::sub::status::DataState& s)
     * @see dds::sub::instance(const dds::core::InstanceHandle& h)
     * @see dds::sub::next_instance(const dds::core::InstanceHandle& h) 
     * @see \ref DDSReaderExampleModule_receive 
     */
    template<typename Functor>
    ManipulatorSelector operator >>(Functor f)
    {
        ManipulatorSelector ms(*this);
        // Call the manipulator selector's >> so the correct operation
        // can be called on ms.impl
        ms >> f;
        return ms;
    }

    // --- Loan read/take: ----------------------------------------------------

    /**
     * @brief Read all samples using the default filter state. 
     *  
     * \dref_details_FooDataReader_read 
     *  
     * @see \ref DDSReaderExampleModule_receive 
     * @see select()
     */
    LoanedSamples<T> read()
    {
        return this->delegate()->read();
    }

    /**
     * @brief Take all samples using the default filter state. 
     * 
     * \dref_details_FooDataReader_take 
     *  
     * @see \ref DDSReaderExampleModule_receive 
     * @see select()
     */
    LoanedSamples<T> take()
    {
        return this->delegate()->take();
    }

    // --- Copy read/take with forward iterators: -----------------------------

    /**
     * @brief Read up to max_samples samples using the default 
     *        filter state. 
     *  
     *  The samples are copied into the application provided container
     *  using the forward iterator parameter.
     *
     * @tparam SamplesFWIterator A forward iterator whose value type
     * is dds::sub::Sample<T>
     * @param sfit samples forward iterator
     * @param max_samples the maximum number of samples to read 
     * @return uint32_t the number of read samples. 
     *  
     * @see read() 
     * @see \ref DDSReaderExampleModule_receive 
     */
    template<typename SamplesFWIterator>
    uint32_t read(SamplesFWIterator sfit, int32_t max_samples)
    {
        return this->delegate()->read(sfit, max_samples);
    }

    /**
     * @brief Take up to max_samples samples using the default 
     * filter state. 
     *  
     * The samples are copied into the application provided container 
     * using the forward iterator parameter.
     *  
     * @tparam SamplesFWIterator A forward iterator whose value type
     * is dds::sub::Sample<T>
     * @param sfit samples forward iterator.
     * @param max_samples the maximum number of samples to take.
     * @return uint32_t The number of taken samples.
     *  
     * @see take() 
     * @see \ref DDSReaderExampleModule_receive 
     */
    template<typename SamplesFWIterator>
    uint32_t take(SamplesFWIterator sfit, int32_t max_samples)
    {
        return this->delegate()->take(sfit, max_samples);
    }

    // --- Copy read/take with back-insertion iterators: ----------------------

    /**
     * @brief Read all samples available in the reader cache using the default 
     * filter state.
     *  
     * The samples are copied into the application provided container 
     * using a back-inserting iterator. Notice that as a consequence of using a 
     * back-inserting iterator, this operation may allocate memory to resize 
     * the underlying container.
     *  
     * @tparam SamplesBIIterator A back-inserting iterator whose value type
     * is dds::sub::Sample<T>
     * @param sbit samples back-inserting iterator.
     * @return uint32_t the number of read samples. 
     *  
     * @see read() 
     * @see \ref DDSReaderExampleModule_receive 
     */
    template<typename SamplesBIIterator>
    uint32_t read(SamplesBIIterator sbit)
    {
        return this->delegate()->read(sbit);
    }

    /**
     * @brief Take all samples available in the reader cache samples using the 
     * default filter state. 
     *  
     * The samples are copied into the application provided container 
     * using a back-inserting iterator. Notice that as a consequence of using 
     * a back-inserting iterator, this operation may allocate memory to resize 
     * the underlying container.
     *  
     * @tparam SamplesBIIterator A back-inserting iterator whose value type
     * is dds::sub::Sample<T>
     * @param sbit samples back-inserting iterator.
     * @return the number of taken samples. 
     *  
     * @see take() 
     * @see \ref DDSReaderExampleModule_receive 
     */
    template<typename SamplesBIIterator>
    uint32_t take(SamplesBIIterator sbit)
    {
        return this->delegate()->take(sbit);
    }

    // --- Data selector: -----------------------------------------------------

    /**
     * @brief Get a Selector to perform complex data selections, such as
     * per-instance selection, content and status filtering.
     *
     *  The selector can be used as follows:
     *
     *  \code
     *  LoanedSamples<Foo> samples = reader.select()
     *      .instance(handle)
     *      .content(query)
     *      .state(state)
     *      .take();
     *  \endcode
     *  
     * This shows how samples can be taken by selecting a specific instance,
     * then filtering by state and content.
     *
     * Note that when the application wants to access all available samples it
     * can simply call DataReader::read() or DataReader::take().
     *
     * @return A Selector, typically used in-line to configure it and finally
     * call Selector::read() or Selector::take().
     *
     * @see Selector, for the different parameters that can be set to configure
     * what samples to read or take.
     * @see \ref DDSReaderExampleModule_select_samples
     */
    Selector select()
    {
        return Selector(*this);
    }

    // --- Instance management: -----------------------------------------------

    /**
     * @brief Retrieve the instance key that corresponds to an instance handle.
     * 
     * Useful for keyed data types.
     *  
     * The operation will only fill the fields that form the key inside 
     * the \p key_holder instance.
     *  
     * For keyed data types, this operation may fail with
     * dds::core::InvalidArgumentError if the \p handle does not correspond to 
     * an existing data-object known to the DataReader. 
     *  
     * @param key_holder A user data type specific key holder of type T whose key 
     * fields are filled by this operation. If T has no key, this operation has 
     * no effect. 
     * 
     * @param handle The instance whose key is to be retrieved. 
     * If T has a key, \p handle must represent an existing instance of type T 
     * known to the DataReader. Otherwise, this method will fail with 
     * dds::core::InvalidArgumentError.
     * If T has a key and \p handle is dds::core::InstanceHandle::nil(), 
     * this method will fail with dds::core::InvalidArgumentError.
     * If T has a key and \p handle represents an  instance of another type or 
     * an instance of type T that has been unregistered, this method will 
     * fail with dds::core::InvalidArgumentError.
     * If T has no key, this method has no effect.
     */
    T& key_value(T& key_holder, const dds::core::InstanceHandle& handle)
    {
        return this->delegate()->key_value(key_holder, handle);
    }

    // Spec issue CPPPSM-247: changed this method to match the signature from
    // the corresponding TDataWriter method
    /**
     * @brief Retrieve the instance key that corresponds to an instance handle.
     * 
     * Useful for keyed data types.
     *  
     * The operation will only fill the fields that form the key inside 
     * the \p key_holder instance.
     *  
     * For keyed data types, this operation may fail with
     * dds::core::InvalidArgumentError if the \p handle does not correspond to 
     * an existing data-object known to the DataReader.
     * 
     * @param key_holder A TopicInstance whose sample's key fields are filled 
     * by this operation. If T does not have a key, this method has no effect.
     * @param handle The instance whose key is to be retrieved. 
     * If T has a key, \p handle must represent an existing instance of type T 
     * known to the DataReader. Otherwise, this method will fail with 
     * dds::core::InvalidArgumentError.
     * If T has a key and \p handle is dds::core::InstanceHandle::nil(), 
     * this method will fail with dds::core::InvalidArgumentError.
     * If T has a key and \p handle represents an  instance of another type or 
     * an instance of type T that has been unregistered, this method will 
     * fail with dds::core::InvalidArgumentError.
     * If T has no key, this method has no effect.
     */
    dds::topic::TopicInstance<T>& key_value(
        dds::topic::TopicInstance<T>& key_holder,
        const dds::core::InstanceHandle& handle)
    {
        return this->delegate()->key_value(key_holder, handle);
    }

    /**
     * @brief Retrieve the InstanceHandle that corresponds to an instance
     * key holder
     * 
     * \dref_details_FooDataReader_lookup_instance
     */
    dds::core::InstanceHandle lookup_instance(const T& key_holder) const
    {
        return this->delegate()->lookup_instance(key_holder);
    }

    // --- Entity getters: ----------------------------------------------------

    /**
     * @brief Returns the dds::topic::TopicDescription associated with the
     * DataReader. 
     *  
     * \dref_details_DataReader_get_topicdescription 
     */
    dds::topic::TopicDescription<DataType> topic_description() const
    {
        return this->delegate()->topic_description();
    }

    /**
     * @brief  Returns the Subscriber to which the DataReader belongs.
     */
    const dds::sub::Subscriber& subscriber() const
    {
        return this->delegate()->subscriber();
    }

    /**
     * @brief Sets the listener associated with this reader.
     *
     * @param the_listener The DataReaderListener to set
     * @param event_mask The dds::core::status::StatusMask associated with the listener  
     */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask& event_mask)
    {
        this->delegate()->listener(the_listener, event_mask);
    }

    /**
   * @brief Returns the listener currently associated with this DataReader.
   *
   * If there's no listener it returns NULL.
     */
    Listener* listener() const
    {
        return this->delegate()->listener();
    }

    // --- Qos management: ----------------------------------------------------

    // Spec issue CPPPSM-217: modified to return by value, not by reference
    /**
     * @brief Get the QoS associated with this reader.
     */
    dds::sub::qos::DataReaderQos qos() const
    {
        return this->delegate()->qos();
    }

    /**
     * @brief Set the QoS associated with this reader. 
     *  
     * This operation modifies the QoS of the DataReader.
     *    
     * The dds::core::policy::UserData,
     * dds::core::policy::Deadline,
     * dds::core::policy::LatencyBudget,
     * dds::core::policy::TimeBasedFilter,               
     * dds::core::policy::ReaderDataLifecycle
     * can be changed. The other policies are immutable.    
     *
     * @param the_qos The DataReaderQos to be set to.
     * Policies must be consistent. Immutable policies
     * cannot be changed after the DataReader is enabled.
     * dds::sub::Subscriber::default_datareader_qos() can be
     * used to set the QoS of the DataReader to match the current 
     * default DataReaderQos set in the Subscriber.
     *            
     * @throws dds::core::ImmutablePolicyError,
     * or dds::core::InconsistentPolicyError., 
     *
     * @see dds::sub::qos::DataReaderQos for rules on consistency among QoS
     * @see \ref Entity_set_qos
     * @see \ref SharedEACallbackRules		
     */
    void qos(const dds::sub::qos::DataReaderQos& the_qos)
    {
        this->delegate()->qos(the_qos);
    }

    /**
     * @brief Set the QoS associated with this reader.
     * 
     * @param the_qos the new qos for this DataReader. 
     * 
     * @see qos(const dds::sub::qos::DataReaderQos& qos)
     */
    DataReader& operator <<(const dds::sub::qos::DataReaderQos& the_qos)
    {
        qos(the_qos);
        return *this;
    }

    /**
     * @brief Get the QoS associated with this reader.
     *
     * @param the_qos the object to populate with the qos for this DataWriter.
     *
     * @see qos()
     */
    DataReader& operator >>(dds::sub::qos::DataReaderQos& the_qos)
    {
        the_qos = qos();
        return *this;
    }

    // --- Historical data: ---------------------------------------------------

    /**
     * @brief Waits until all "historical" data is received for DataReaders 
     * that have a non-VOLATILE Durability Qos kind
     *
     * \dref_details_DataReader_wait_for_historical_data
     */
    void wait_for_historical_data(const dds::core::Duration& max_wait)
    {
        this->delegate()->wait_for_historical_data(max_wait);
    }

    // --- Status getters: ----------------------------------------------------

    // Spec issue CPPPSM-217: modified to return by value, not by reference
    /**
     * @brief Get the LivelinessChangedStatus for this DataReader
     *  
     * @see dds::core::status::LivelinessChangedStatus 
     */
    dds::core::status::LivelinessChangedStatus
    liveliness_changed_status() const
    {
        return this->delegate()->liveliness_changed_status();
    }

    /**
     * @brief Get the SampleRejectedStatus for this DataReader
     * 
     * @see dds::core::status::SampleRejectedStatus 
     */
    dds::core::status::SampleRejectedStatus
    sample_rejected_status() const
    {
        return this->delegate()->sample_rejected_status();
    }

    /**
     * @brief Get the SampleLostStatus for this DataReader
     * 
     * @see dds::core::status::SampleLostStatus 
     */
    dds::core::status::SampleLostStatus
    sample_lost_status() const
    {
        return this->delegate()->sample_lost_status();
    }

    /**
     * @brief Get the RequestedDeadlineMissedStatus for this DataReader
     * 
     * @see dds::core::status::RequestedDeadlineMissedStatus 
     */
    dds::core::status::RequestedDeadlineMissedStatus
    requested_deadline_missed_status()
    {
        return this->delegate()->requested_deadline_missed_status();
    }

    /**
     * @brief Get the RequestedIncompatibleQosStatus for this DataReader
     * 
     * @see dds::core::status::RequestedIncompatibleQosStatus 
     */
    dds::core::status::RequestedIncompatibleQosStatus
    requested_incompatible_qos_status() const
    {
        return this->delegate()->requested_incompatible_qos_status();
    }

    /**
     * @brief Get the SubscriptionMatchedStatus for this DataReader
     * 
     * @see dds::core::status::SubscriptionMatchedStatus 
     */
    dds::core::status::SubscriptionMatchedStatus
    subscription_matched_status() const
    {
        return this->delegate()->subscription_matched_status();
    }
};

#endif /* OMG_DDS_SUB_TDATA_READER_HPP_ */
