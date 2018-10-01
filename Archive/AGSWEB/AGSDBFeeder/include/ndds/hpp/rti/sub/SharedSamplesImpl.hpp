/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,27mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_SHARED_SAMPLES_IMPL_HPP_
#define RTI_DDS_SUB_SHARED_SAMPLES_IMPL_HPP_

#include <iterator>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/sub/SampleIterator.hpp>
#include <dds/sub/LoanedSamples.hpp>

namespace rti { namespace sub {

/**
 * \dref_LoanedContainer
 */
template <typename T>
class SharedSamples {
public:
   /**
    * @brief The iterator type
    */
   typedef SampleIterator<T> iterator;
   typedef SampleIterator<T> const_iterator; // TODO: define const it (see xmq)

   typedef typename SampleIterator<T>::value_type value_type;
   //typedef typename dds_type_traits<T>::ConstSampleIteratorValueType    const_value_type;
   typedef std::ptrdiff_t difference_type;

   typedef std::ostream_iterator<typename SharedSamples<T>::value_type> ostream_iterator;

public:

    /* implicit */ SharedSamples(dds::sub::LoanedSamples<T>& ls)
        : samples_ (dds::sub::move(ls))
    {
    }

    ~SharedSamples()
    {
        // samples_'s destructor does all the work
    }

    value_type operator [] (size_t index)
    {
       return samples_[index];
    }

    /*const_value_type operator [] (size_t index) const {
       return const_value_type(data_seq_[index], info_seq_[index]);
    }*/

    unsigned int length() const
    {
        return samples_.length();
    }

    void return_loan()
    {
        samples_.return_loan();
    }

    iterator begin()
    {
        return samples_.begin();
    }

    iterator end()
    {
        return samples_.end();
    }

    const_iterator begin() const
    {
        return samples_.begin();
    }

    const_iterator end() const
    {
        return samples_.end();
    }

    void swap(SharedSamples& other) throw()
    {
        samples_.swap(other.samples_);
    }

private:
    dds::sub::LoanedSamples<T> samples_;
};


template <typename T>
typename SharedSamples<T>::iterator begin(SharedSamples<T> & ls)
{
    return ls.begin();
}

template <typename T>
typename SharedSamples<T>::const_iterator begin(const SharedSamples<T> & ls)
{
    return ls.begin();
}

template <typename T>
typename SharedSamples<T>::iterator end(SharedSamples<T> & ls)
{
    return ls.end();
}

template <typename T>
typename SharedSamples<T>::const_iterator end(const SharedSamples<T> & ls)
{
    return ls.end();
}

template <typename T>
void swap(SharedSamples<T> &ls1, SharedSamples<T> &ls2) throw()
{
    ls1.swap(ls2);
}

} } // namespace rti::sub

#endif // RTI_DDS_SUB_SHARED_SAMPLES_IMPL_HPP_
