/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,07mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_DETAIL_ENTITY_DELETER_ITERATOR_HPP_
#define RTI_DDS_CORE_DETAIL_ENTITY_DELETER_ITERATOR_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <iterator>

namespace rti { namespace core { namespace detail {

//
// Acting as a back-insert iterator, calls close() on a range of entities.
//
// Utility to be passed to find()-style functions that take a back-insert
// iterator.
//
template<typename EntityType>
class EntityDeleterIterator :
    public std::iterator<std::output_iterator_tag, void, void, void, void> {
public:
    EntityDeleterIterator& operator=(EntityType entity)
    {
        entity.close();
        return *this;
    }
    EntityDeleterIterator& operator*()
    {
        return *this;
    }
    EntityDeleterIterator& operator++()
    {
        return *this;
    }
    EntityDeleterIterator operator++(int)
    {
        return *this;
    }
};

} } } // namespace rti::core::detail

#endif // RTI_DDS_CORE_DETAIL_ENTITY_DELETER_ITERATOR_HPP_

