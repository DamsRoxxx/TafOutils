/* $Id$
 (c) Copyright, Real-Time Innovations, 2014-2016.
 All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
--------------------
1.0a,21apr14,acr Created
============================================================================= */

#ifndef OMG_RTI_DDS_CORE_VECTOR_ITERATOR_HPP_
#define OMG_RTI_DDS_CORE_VECTOR_ITERATOR_HPP_

#include <iterator>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "osapi/osapi_type.h"
#include "osapi/osapi_heap.h"

#include <rti/core/VectorIterator.hpp>

namespace rti { namespace core {

template <typename Iterator>
class VectorIterator {
public:
    typedef std::iterator_traits<Iterator> traits_type;

    typedef Iterator                                iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type        value_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::reference         reference;
    typedef typename traits_type::pointer           pointer;

   VectorIterator() : pos_(Iterator())
   {
   }

   VectorIterator(const Iterator& i) : pos_ (i)
   {
   }

   reference operator * () const
   {
       return *pos_;
   }

   pointer operator ->() const
   {
       return pos_;
   }

   VectorIterator& operator ++ ()
   {
       ++pos_;
       return *this;
   }

   VectorIterator operator ++ (int)
   {
       VectorIterator temp(*this);
       ++(*this);
       return temp;
   }

   VectorIterator& operator -- ()
   {
       --pos_;
       return *this;
   }

   VectorIterator operator -- (int)
   {
       VectorIterator temp(*this);
       --(*this);
       return temp;
   }

   reference operator[] (const difference_type& n) const
   {
       return pos_[n];
   }

   VectorIterator & operator -= (difference_type i) {
     pos_ -= i;
     return *this;
   }

   VectorIterator & operator += (difference_type i) {
     pos_ += i;
     return *this;
   }

   friend VectorIterator operator - (
       const VectorIterator & it,
       difference_type i)
   {
       return VectorIterator(it.pos_ - i);
   }

   friend VectorIterator operator + (
       const VectorIterator & it,
       difference_type i)
   {
       return VectorIterator(it.pos_ + i);
   }

   friend difference_type operator - (
       const VectorIterator & s1,
       const VectorIterator & s2)
   {
       return s1.pos_ - s2.pos_;
   }

   friend bool operator < (const VectorIterator & s1,
                           const VectorIterator & s2) {
     return s1.pos_ < s2.pos_;
   }

   friend bool operator > (const VectorIterator & s1,
                           const VectorIterator & s2) {
     return s1.pos_ > s2.pos_;
   }

   friend bool operator <= (const VectorIterator & s1,
                            const VectorIterator & s2) {
     return s1.pos_ <= s2.pos_;
   }

   friend bool operator >= (const VectorIterator & s1,
                            const VectorIterator & s2) {
     return s1.pos_ >= s2.pos_;
   }

   friend bool operator == (const VectorIterator & s1,
                            const VectorIterator & s2) {
     return s1.pos_ == s2.pos_;
   }

   friend bool operator != (const VectorIterator & s1,
                            const VectorIterator & s2) {
     return !(s1 == s2);
   }


private:
   Iterator pos_;

public:
   void swap(VectorIterator& other)
       OMG_NOEXCEPT_IF(noexcept(std::swap(VectorIterator::pos_, VectorIterator::pos_)))
   {
       std::swap(pos_, other.pos_);
   }
};

template <typename Iterator>
void swap(VectorIterator<Iterator>& left, VectorIterator<Iterator>& right)
     OMG_NOEXCEPT_IF(noexcept(left.swap(right)))
{
    left.swap(right);
}


} } // namespace rti::core

#endif // OMG_RTI_DDS_CORE_VECTOR_ITERATOR_HPP_
