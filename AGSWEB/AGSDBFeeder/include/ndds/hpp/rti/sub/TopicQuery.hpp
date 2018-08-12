/* $Id: SharedSamplesImpl.hpp,v 1.4 2015/02/23 22:43:59 erin Exp $

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,01dec15,acr Created (date is approximate)
============================================================================= */

#ifndef RTI_DDS_SUB_TOPIC_QUERY_HPP_
#define RTI_DDS_SUB_TOPIC_QUERY_HPP_


// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>
#include "dds_c/dds_c_subscription_impl.h"

#include <rti/core/NativeValueType.hpp>
#include <rti/core/Guid.hpp>
#include <dds/sub/DataReader.hpp>
#include <rti/topic/topicfwd.hpp> // for ServiceRequest

namespace rti { namespace sub {

// --- TopicQuerySelection: ---------------------------------------------------

/**
 * @ingroup DDSTopicQueryModule
 * @headerfile rti/sub/TopicQuery.hpp
 * @brief @extension @st_value_type Specifies the data query that defines a
 * TopicQuery.
 *
 * A TopicQuerySelection is defined by a dds::topic::Filter that selects a
 * subset of samples in the dds::pub::DataWriters
 */
class OMG_DDS_API TopicQuerySelection {
public:
    /**
     * @brief Creates a TopicQuerySelection
     *
     * @param the_filter Defines the data query. The filter expression can be
     * an empty string, which selects all samples.
     */
    explicit TopicQuerySelection(const dds::topic::Filter& the_filter)
        : filter_(the_filter)
    {
    }

    /**
     * @brief Gets the filter
     */
    dds::topic::Filter& filter()
    {
        return filter_;
    }

    /**
     * @brief Gets the filter
     */
    const dds::topic::Filter& filter() const
    {
        return filter_;
    }

    bool operator==(const TopicQuerySelection& other) const
    {
        return filter() == other.filter();
    }

    bool operator!=(const TopicQuerySelection& other) const
    {
        return !(*this == other);
    }

private:
    dds::topic::Filter filter_;
};

// --- TopicQueryData: --------------------------------------------------------

class TopicQueryData;

class TopicQueryDataNativeAdapter {
public:

    typedef DDS_TopicQueryData native_type;

    static void initialize(native_type& native_value)
    {
        memset(&native_value, 0, sizeof(native_type));
    }

    static void finalize(native_type& native_value)
    {
        DDS_TopicQueryData_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        if (!DDS_TopicQueryData_copy(&destination, &source)) {
            throw std::bad_alloc();
        }
    }

    // equals() not implemented because it doesn't exist in dds_c; the class
    // TopicQueryData directly implements the == and != operators
    static bool equals(const native_type&, const native_type&)
    {
        return false;
    }
};

} // namespace sub

namespace core {

template <>
struct native_type_traits<rti::sub::TopicQueryData> {
    typedef rti::sub::TopicQueryDataNativeAdapter adapter_type;
    typedef rti::sub::TopicQueryDataNativeAdapter::native_type native_type;
};

} // namespace core

namespace sub {

/**
 * @ingroup DDSTopicQueryModule
 * @headerfile rti/sub/TopicQuery.hpp
 * @brief @extension @st_value_type Provides information about a TopicQuery
 *
 * @details \dref_details_TopicQueryData
 */
class OMG_DDS_API TopicQueryData :
    public rti::core::NativeValueType<TopicQueryData> {
public:

    typedef rti::core::NativeValueType<TopicQueryData> Base;

    TopicQueryData();
    TopicQueryData(const TopicQueryData& other) : Base(other.native()) {}
    TopicQueryData(const native_type& native_value) : Base(native_value) {}

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    // Need to define the move constructor and move-assignment operator because
    // we're defining a copy constructor
    TopicQueryData(TopicQueryData&& other) OMG_NOEXCEPT
            : Base(static_cast<Base&&>(other))
    {
    }

    TopicQueryData& operator=(TopicQueryData&& other) OMG_NOEXCEPT
    {
        Base::operator=(std::move(other));
        return *this;
    }

    // Need to define copy-assignment operator because declaring the
    // move-assignment operator deletes it
    TopicQueryData operator=(const TopicQueryData& other)
    {
        Base::operator=(other);
        return *this;
    }
  #endif

    bool operator==(const TopicQueryData& other) const;
    bool operator!=(const TopicQueryData& other) const;

    /** \dref_TopicQueryData_topic_query_selection
     */
    TopicQuerySelection selection() const;

    // internal
    const rti::core::SequenceNumber& sync_sequence_number() const;

    /** \dref_TopicQueryData_topic_name
     */
    const dds::core::string& topic_name() const;

    /** \dref_TopicQueryData_original_related_reader_guid
     */
    const rti::core::Guid& original_related_reader_guid() const;
};

/**
 * @relatesalso TopicQueryData
 *
 * @brief Creates a TopicQueryData from a ServiceRequest
 *
 * @details \dref_details_TopicQueryHelper_topic_query_data_from_service_request
 */
OMG_DDS_API
TopicQueryData create_topic_query_data_from_service_request(
    const rti::topic::ServiceRequest& service_request);

// --- TopicQuery: ------------------------------------------------------------

// As the Delegate of TopicQuery, it implements the actual functionality,
// whereas TopicQuery is a Reference-type wrapper.
class OMG_DDS_API TopicQueryImpl :
    public rti::core::detail::RetainableType<TopicQueryImpl> {
public:
    TopicQueryImpl(
        dds::sub::AnyDataReader reader,
        const TopicQuerySelection& selection);

    TopicQueryImpl(
        dds::sub::AnyDataReader reader,
        const DDS_TopicQuerySelection& native_selection);

    TopicQueryImpl(DDS_TopicQuery * native_tq);
    
    ~TopicQueryImpl();
    void close();
    bool closed() const;
    void remember_reference(ref_type reference);
    dds::sub::AnyDataReader datareader() const;
    const rti::core::Guid guid() const;

private:
    void assert_not_closed() const
    {
        if (closed()) {
            throw dds::core::AlreadyClosedError("TopicQuery already closed");
        }
    }
    
    dds::sub::AnyDataReader reader_;
    DDS_TopicQuery * native_;
};

/**
 * @ingroup DDSTopicQueryModule
 * @headerfile rti/sub/TopicQuery.hpp
 *
 * @brief @extension @st_ref_type Allows a dds::sub::DataReader to query
 * the sample cache of its matching dds::pub::DataWriters.
 *
 * You can create a TopicQuery for a DataReader with the constructor that
 * receives a TopicQuerySelection or with the following static member functions:
 *
 * \li TopicQuery::UseReaderContentFilter
 * \li TopicQuery::SelectAll
 *
 * As a \st_ref_type, a TopicQuery will be deleted when all references to it
 * go out of scope or after calling close(). The middleware will notify the
 * deletion of a TopicQuery to the DataWriters. See close() for more details.
 *
 */
class OMG_DDS_API TopicQuery : public dds::core::Reference<TopicQueryImpl> {
public:
    typedef dds::core::Reference<TopicQueryImpl> Base;

    OMG_DDS_REF_TYPE_NOTYPENAME(TopicQuery, dds::core::Reference, TopicQueryImpl)

    /**
     * @brief Creates a TopicQuery for a given DataReader
     *
     * The resulting TopicQuery will propagate to the matching DataWriters right
     * after creating if the reader is enabled. Otherwise it will propagate after
     * enabling the reader.
     *
     * Any late-joining DataWriter matching with the DataReader
     * will also receive the query.
     *
     * @param reader The DataReader that will query and receive the requested
     * samples
     * @param selection Selects which samples the matching DataWriters will
     * provide.
     *
     * There are two special kinds of TopicQueries, created with the static
     * member functions UseReaderContentFilter() and SelectAll().
     *
     */
    TopicQuery(
        dds::sub::AnyDataReader reader,
        const TopicQuerySelection& selection)
        : Base(new TopicQueryImpl(reader,selection))
    {
        this->delegate()->remember_reference(this->delegate());
    }            
    
    // Internal
    explicit TopicQuery(Base::DELEGATE_REF_T reference) : Base(reference)
    {
        if (this->delegate()) {
            this->delegate()->remember_reference(this->delegate());
        }
    }
    
    void retain()
    {
        this->delegate()->retain();
    }

    /**
     * @brief Deletes and cancels this TopicQuery
     *
     * This is a explicit deletion, which otherwise would occur when all
     * references to this TopicQuery go out of scope.
     *
     * After deleting a TopicQuery new DataWriters won't discover it and
     * existing DataWriters currently publishing cached samples may stop before
     * delivering all of them.
     */
    void close()
    {
        this->delegate()->close();
    }
    
    /**
     * @brief Gets the TopicQuery GUID.
     *
     * @see rti::sub::find_topic_query()
     */
    const rti::core::Guid guid() const
    {
        return this->delegate()->guid();
    }

    /**
     * @brief Indicates whether this TopicQuery has been closed with close().
     */
    bool closed() const
    {
        return this->delegate()->closed();
    }

    /**
     * @brief Gets the DataReader associated to this TopicQuery
     */
    dds::sub::AnyDataReader datareader() const
    {
        return this->delegate()->datareader();
    }

    /**
     * @brief Creates a TopicQuery with the same filter as this reader's
     * ContentFilteredTopic
     *
     * If the reader doesn't use a dds::topic::ContentFilteredTopic, this
     * TopicQuery behaves as TopicQuery::SelectAll().
     */
    static TopicQuery UseReaderContentFilter(dds::sub::AnyDataReader reader);

    /**
     * @brief Creates a TopicQuery that requests all the samples in the
     * DataWriters' cache.
     */
    static TopicQuery SelectAll(dds::sub::AnyDataReader reader);
};

/**
 * @relatesalso rti::sub::TopicQuery
 * @brief Looks up a TopicQuery by its GUID
 * @headerfile rti/sub/TopicQuery.hpp
 *
 * @param datareader The DataReader used to create the TopicQuery
 * @param guid The TopicQuery's GUID
 * @return The TopicQuery if it exists or a dds::core::null reference otherwise.
 *
 * @see rti::sub::TopicQuery::guid()
 */
OMG_DDS_API
TopicQuery find_topic_query(
    dds::sub::AnyDataReader datareader, const rti::core::Guid& guid);


} } // namespace rti::sub

#endif // RTI_DDS_SUB_TOPIC_QUERY_HPP_
