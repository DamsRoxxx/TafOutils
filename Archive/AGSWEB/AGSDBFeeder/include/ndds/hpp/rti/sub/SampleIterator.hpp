/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,05may14,acr Added ValidSampleIterator and valid_samples helper
1.0a,20mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_SAMPLE_ITERATOR_HPP_
#define RTI_DDS_SUB_SAMPLE_ITERATOR_HPP_

#include <iterator>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/detail/SequenceWrapper.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <rti/sub/LoanedSample.hpp>


#include "ndds/ndds_c.h"

namespace rti { namespace sub {

template <typename T>
class ValidSampleIterator;

/**
 * @ingroup DDSDataSampleModule
 * @brief A random-access iterator of LoanedSample
 *
 * @see dds::sub::LoanedSamples
 */
template <typename T>
class SampleIterator {
public:
   // iterator traits
   typedef std::random_access_iterator_tag iterator_category;
   typedef const LoanedSample<T> value_type;
   typedef value_type reference;
   typedef value_type pointer;
   typedef std::ptrdiff_t difference_type;

   SampleIterator()
     : _data_seq(0),
       _info_seq(0),
       _pos(0)
   {}

   explicit SampleIterator(
       rti::core::detail::ContiguousDataSequence<T>& seq,
       DDS_SampleInfoSeq& info_seq,
       int position = 0)
     : _data_seq(&seq),
       _info_seq(&info_seq),
       _pos(position)
   {}

   SampleIterator (const SampleIterator<T> & other)
     : _data_seq(other._data_seq),
       _info_seq(other._info_seq),
       _pos(other._pos)
   {}

   SampleIterator & operator = (const SampleIterator<T> & other)
   {
     _data_seq      = other._data_seq;
     _info_seq = other._info_seq;
     _pos      = other._pos;

     return *this;
   }

   explicit SampleIterator(const ValidSampleIterator<T>& valid_it)
       : _data_seq(0),
         _info_seq(0),
         _pos(0)
   {
       *this = valid_it.underlying();
   }

   value_type operator * () const {
     return value_type(
         &(*_data_seq)[_pos],
         DDS_SampleInfoSeq_get_reference(_info_seq, _pos));
   }

   value_type operator ->() const {
     return value_type(
         &(*_data_seq)[_pos],
         DDS_SampleInfoSeq_get_reference(_info_seq, _pos));
   }

   value_type operator [] (difference_type offset) const {
       return value_type(
           &(*_data_seq)[_pos + offset],
           DDS_SampleInfoSeq_get_reference(_info_seq, _pos + offset));
   }

   SampleIterator & operator ++ () {
     ++_pos;
     return *this;
   }

   SampleIterator operator ++ (int) {
     SampleIterator temp(*this);
     ++(*this);
     return temp;
   }

   SampleIterator & operator -- () {
     --_pos;
     return *this;
   }

   SampleIterator operator -- (int) {
     SampleIterator temp(*this);
     --(*this);
     return temp;
   }

   SampleIterator & operator -= (difference_type i) {
     _pos -= i;
     return *this;
   }

   SampleIterator & operator += (difference_type i) {
     _pos += i;
     return *this;
   }

   friend SampleIterator operator - (const SampleIterator & si,
                                     difference_type i) {
     return SampleIterator(*si._data_seq, *si._info_seq, si._pos - i);
   }

   friend SampleIterator operator + (const SampleIterator & si,
                                     difference_type i) {
     return SampleIterator(*si._data_seq, *si._info_seq, si._pos + i);
   }

   friend difference_type operator - (const SampleIterator & s1,
                                      const SampleIterator & s2) {
     return s1._pos - s2._pos;
   }

   friend bool operator < (const SampleIterator & s1,
                           const SampleIterator & s2) {
     return s1._pos < s2._pos;
   }

   friend bool operator > (const SampleIterator & s1,
                           const SampleIterator & s2) {
     return s1._pos > s2._pos;
   }

   friend bool operator <= (const SampleIterator & s1,
                            const SampleIterator & s2) {
     return s1._pos <= s2._pos;
   }

   friend bool operator >= (const SampleIterator & s1,
                            const SampleIterator & s2) {
     return s1._pos >= s2._pos;
   }

   friend bool operator == (const SampleIterator & s1,
                            const SampleIterator & s2) {
     return (s1._data_seq == s2._data_seq) && (s1._pos == s2._pos);
   }

   friend bool operator != (const SampleIterator & s1,
                            const SampleIterator & s2) {
     return !(s1 == s2);
   }

   bool is_end() const {
       return ((int) _data_seq->length()) == _pos;
   }

   // Keep these members public otherwise some of the
   // converting constructors will not compile.
public:
   rti::core::detail::ContiguousDataSequence<T> * _data_seq;
   DDS_SampleInfoSeq * _info_seq;
   int    _pos;
};

/**
 * @ingroup DDSDataSampleModule
 * @brief A forward iterator adapter that skips invalid samples
 *
 * Instead of instantiating this class directly, use valid_samples().
 *
 * @see valid_samples()
 */
template <typename T>
class ValidSampleIterator {
public:
   typedef std::forward_iterator_tag iterator_category;

   typedef typename SampleIterator<T>::difference_type difference_type;
   typedef typename SampleIterator<T>::value_type value_type;
   typedef typename SampleIterator<T>::reference reference;
   typedef typename SampleIterator<T>::value_type pointer;

   ValidSampleIterator()
    : iterator_()
   {}

   explicit ValidSampleIterator(const SampleIterator<T>& related_it)
     : iterator_(related_it)
   {
       skip_invalid();
   }

   ValidSampleIterator (const ValidSampleIterator<T> & other)
     : iterator_(other.underlying())
   {}

   ValidSampleIterator & operator = (const ValidSampleIterator<T> & other)
   {
     iterator_ = other.underlying();
     return *this;
   }

   value_type operator * () const {
     return *iterator_;
   }

   value_type operator ->() const {
     return *iterator_;
   }

   ValidSampleIterator & operator ++ () {
       ++iterator_;
       skip_invalid();
       return *this;
   }

   ValidSampleIterator operator ++ (int) {
       ValidSampleIterator temp(*this);
       ++(*this);
       return temp;
   }

   SampleIterator<T> underlying() const
   {
       return iterator_;
   }

   friend bool operator < (const ValidSampleIterator & s1,
                           const ValidSampleIterator & s2) {
     return s1.iterator_ < s2.iterator_;
   }

   friend bool operator > (const ValidSampleIterator & s1,
                           const ValidSampleIterator & s2) {
     return s1.iterator_ > s2.iterator_;
   }

   friend bool operator <= (const ValidSampleIterator & s1,
                            const ValidSampleIterator & s2) {
     return s1.iterator_ <= s2.iterator_;
   }

   friend bool operator >= (const ValidSampleIterator & s1,
                            const ValidSampleIterator & s2) {
     return s1.iterator_ >= s2.iterator_;
   }

   friend bool operator == (const ValidSampleIterator & s1,
                            const ValidSampleIterator & s2) {
     return s1.iterator_ == s2.iterator_;
   }

   friend bool operator != (const ValidSampleIterator & s1,
                            const ValidSampleIterator & s2) {
     return !(s1 == s2);
   }

private:

   void skip_invalid()
   {
       while (!iterator_.is_end() && !(iterator_->info().valid())) {
           ++iterator_;
       }
   }

   SampleIterator<T> iterator_;
};


/**
 * @relatesalso dds::sub::LoanedSamples
 *
 * @brief @extension Returns an iterator that skips invalid samples
 *
 * Given a regular sample iterator, this functions creates another iterator \p it
 * that behaves exactly the same except that \p it++ moves to the next valid sample
 * (or to the end of the collection). That is, if \p it doesn't point to the end
 * of the collection, \p it->info.valid() is always true.
 *
 * This is useful when your application doesn't need to deal with samples
 * containing meta-information only.
 *
 * For example, the following code copies all the data in a LoanedSamples collection
 * skipping any invalid samples (otherwise, attempting to copy the data from an
 * invalid sample would throw an exception, see
 * rti::sub::LoanedSample::operator const DataType& ()).
 *
 * \code
 * dds::sub::LoanedSamples<KeyedType> samples = reader.take();
 * std::vector<KeyedType> data_vector;
 * std::copy(
 *      rti::sub::valid_samples(samples.begin()),
 *      rti::sub::valid_samples(samples.end()),
 *      std::back_inserter(data_vector));
 * \endcode
 *
 * Note that \p valid_samples(samples.begin()) won't point to the first element
 * if that element is not a valid sample.
 *
 * A similar utility is the functor rti::sub::IsValidData.
 *
 * @see dds::sub::LoanedSamples
 * @see rti::sub::IsValidData
 * @see dds::sub::SampleInfo::valid()
 * @see \ref DDSReaderExampleModule_read_samples
 */
template <typename T>
ValidSampleIterator<T> valid_samples(const SampleIterator<T>& sample_iterator)
{
    return ValidSampleIterator<T>(sample_iterator);
}

} } // namespace rti::sub

#endif // RTI_DDS_SUB_SAMPLE_ITERATOR_HPP_
