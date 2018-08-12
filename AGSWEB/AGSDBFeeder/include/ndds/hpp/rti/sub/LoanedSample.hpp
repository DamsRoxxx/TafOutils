/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,20mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_SAMPLE_REF_IMPL_HPP_
#define RTI_DDS_SUB_SAMPLE_REF_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/sub/SampleInfo.hpp>
#include <dds/sub/Sample.hpp>
#include <rti/sub/subfwd.hpp>
#include <utility>

#include "ndds/ndds_c.h"

namespace rti { namespace sub {

/**
 * @ingroup DDSDataSampleModule
 * @brief The element type of a dds::sub::LoanedSamples collection.
 *
 * This class encapsulates loaned, read-only data and SampleInfo from a DataReader.
 *
 * LoanedSample instances are always the element of a dds::sub::LoanedSamples
 * collection and have to be returned through that collection. A LoanedSample
 * instance is a lightweight handle to data owned by the DataReader
 * from where you received a LoanedSamples collection.
 *
 * This type is not exactly a reference type, value type or move-only type.
 * Copying a LoanedSample simply creates a new handle to the same loaned data.
 *
 * The difference between LoanedSample and dds::sub::Sample is that the latter
 * is a \ref a_st_value_type "value type" that the application owns. A Sample
 * can be constructed by copying the data and meta-data referenced by a LoanedSample.
 *
 * In most cases the only thing applications care about is that the elements of
 * a dds::sub::LoanedSamples collection have two methods, data() and info().
 * For example:
 *
 * \code
 * dds::sub::LoanedSamples<Foo> samples = reader.take();
 * for (auto sample : samples) {
 *     if (sample.info().valid()) {
 *         std::cout << sample.data() << std::endl;
 *     }
 * }
 * \endcode
 *
 * @see dds::sub::LoanedSamples
 */
template <typename T>
class LoanedSample
{
public:
    /**
     * @brief The data type
     */
    typedef T DataType;

    /**
     * @brief dds::sub::SampleInfo
     */
    typedef dds::sub::SampleInfo InfoType;

    LoanedSample()
        : _data_ptr(NULL),
          _info_ptr(NULL)
    {}

    LoanedSample(DataType * the_data, InfoType * the_info)
        : _data_ptr(the_data),
          _info_ptr(the_info)
    {}

    // construct from C DDS_SampleInfo
    //
    // reinterpret_cast works because both types have the exact same memory mapping
    LoanedSample(DataType * the_data, DDS_SampleInfo * the_info)
        : _data_ptr(the_data),
          _info_ptr(reinterpret_cast<dds::sub::SampleInfo*>(the_info))
    {
    }

    LoanedSample(DataType & the_data, InfoType & the_info)
        : _data_ptr(&the_data),
          _info_ptr(&the_info)
    {}

    /**
     * @brief Gets the data
     *
     * @throws dds::core::PreconditionNotMetError if !info().valid().
     */
    const DataType & data() const
    {
        if (!info().valid()) {
            throw dds::core::PreconditionNotMetError("Invalid data");
        }

        return *_data_ptr;
    }

    /**
     * @brief Gets the sample info
     */
    const InfoType & info() const {
        return *_info_ptr;
    }

    /**
     * @brief Allows implicit conversion to the data type.
     *
     * One use of this conversion operator is to simplify the usage of generic
     * algorithms that iterate on a LoanedSamples collection.
     *
     * For example, the following example copies all the data of in a
     * LoanedSamples collection into a vector of the data type. The call to
     * \p std::copy works as-is thanks to this conversion.
     *
     * \code
     * LoanedSamples<KeyedType> samples = reader.take();
     * std::vector<KeyedType> data_vector;
     * std::copy(samples.begin(), samples.end(), std::back_inserter(data_vector));
     * \endcode
     *
     * Note: the example above may throw dds::core::PreconditionNotMetError if
     * any of the samples has invalid data. See valid_samples() to
     * skip invalid samples in an iterator range.
     *
     * @throws dds::core::PreconditionNotMetError if \p !info().valid().
     */
    operator const DataType & () const 
    {
        return data();
    }

    LoanedSample<DataType> * operator ->() {
        return this;
    }

    const LoanedSample<DataType> * operator ->() const {
        return this;
    }

    /**
     * @brief Compares the data and info
     */
    bool operator==(const LoanedSample& other) const
    {
        if (info() != other.info()) {
            return false;
        }

        if (info().valid()) {
            if (data() != other.data()) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const LoanedSample& other) const
    {
        return !(*this == other);
    }

    void swap(LoanedSample & other) throw()
    {
        using std::swap;

        swap(_data_ptr, other._data_ptr);
        swap(_info_ptr, other._info_ptr);
    }

private:
    DataType * _data_ptr;
    InfoType * _info_ptr;
};

/**
 * @relatesalso rti::sub::LoanedSample
 *
 * @brief Copies the contents of a rti::sub::LoanedSample into a dds::sub::Sample
 *
 * Example:
 *
 * \code
 * dds::sub::LoanedSamples<Foo> samples = reader.take();
 * std::vector<Sample<Foo> > sample_vector;
 * std::transform(
 *     rti::sub::valid_samples(samples.begin()),
 *     rti::sub::valid_samples(samples.end()),
 *     std::back_inserter(sample_vector),
 *     rti::sub::copy_to_sample<Foo>);
 * \endcode
 *
 */
template <typename T>
dds::sub::Sample<T> copy_to_sample(const rti::sub::LoanedSample<T>& ls)
{
    return dds::sub::Sample<T>(ls);
}

/**
 * @relatesalso LoanedSample
 * @brief Calls the operator on the data or prints [invalid data].
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const LoanedSample<T>& sample)
{
    if (sample.info().valid()) {
        out << sample.data();
    } else {
        out << "[invalid data]";
    }

    return out;
}

} } // namespace rti::sub

#endif // RTI_DDS_SUB_SAMPLE_REF_IMPL_HPP_
