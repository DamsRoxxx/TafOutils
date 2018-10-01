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

#ifndef OMG_DDS_SUB_SHARED_SAMPLES_HPP__
#define OMG_DDS_SUB_SHARED_SAMPLES_HPP__

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Reference.hpp>
#include <dds/sub/Sample.hpp>
#include <dds/sub/LoanedSamples.hpp>
#include <dds/sub/detail/SharedSamples.hpp>

namespace dds {
  namespace sub {
    template <typename T,
    template <typename Q> class DELEGATE = detail::SharedSamples>
    class SharedSamples;
  }
}

/**
 * @RTI_class_definition class dds::sub::SharedSamples
 *
 * @headerfile dds/sub/SharedSamples.hpp
 *
 * @ingroup DDSDataSampleModule
 * @brief @st_ref_type A sharable and container-safe version of LoanedSamples.
 *
 * A SharedSamples instance is constructed from a LoanedSamples instance,
 * removing the ownership of the loan from the LoanedSamples.
 *
 * The destruction of the LoanedSamples object
 * or the explicit invocation of its method return_loan will have no effect
 * on loaned data.
 *
 * Constructing a SharedSamples from another SharedSamples, creates a new
 * reference to the same loan. Loaned data will be returned automatically to
 * the DataReader once the reference count reaches zero.
 *
 * @see LoanedSamples
 */
template <typename T,
template <typename Q> class DELEGATE>
class dds::sub::SharedSamples : public dds::core::Reference< DELEGATE<T> > {
public:
    typedef T DataType;
    typedef typename DELEGATE<T>::iterator iterator;
    typedef typename DELEGATE<T>::const_iterator const_iterator;

public:
    OMG_DDS_REF_TYPE(SharedSamples, dds::core::Reference, DELEGATE<T>)

    /**
     * @brief Constructs and instance of SharedSamples removing the ownership
     * of the loan from the LoanedSamples.
     *
     * The constructor is implicit to simplify statements like the following:
     *
     * \code
     * SharedSamples samples = reader.take(); // reader.take() returns LoanedSamples
     * \endcode
     *
     * @param ls the loaned samples.
     */
    SharedSamples(dds::sub::LoanedSamples<T>& ls)
        // ls passed by reference because LoanedSamples is non-copyable
        : dds::core::Reference<DELEGATE<T> > (new DELEGATE<T>(ls))
    {
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    // Create from rvalue LoanedSamples
    // e.g. SharedSamples<T> samples = reader.take();
    SharedSamples(dds::sub::LoanedSamples<T>&& ls)
        : dds::core::Reference<DELEGATE<T> > (new DELEGATE<T>(ls))
    {
    }
  #endif

    ~SharedSamples()
    {
    }


public:
    /**
     * @brief Same as LoanedSamples::begin()
     * @see LoanedSamples::begin()
     */
    const_iterator begin() const
    {
        return this->delegate()->begin();
    }

    /**
     * @brief Same as LoanedSamples::end()
     * @see LoanedSamples::end()
     */
    const_iterator end() const
    {
        return this->delegate()->end();
    }

    /**
     * @brief Same as LoanedSamples::operator[](size_t)
     * @see LoanedSamples::operator[](size_t)
     */
    typename DELEGATE<T>::value_type operator [] (size_t index) const
    {
       return (*this->delegate())[index];
    }

    /**
     * @brief Returns the number of samples
     * @see LoanedSamples::length()
     */
    uint32_t length() const
    {
        return this->delegate()->length();
    }
};

#endif // OMG_DDS_SUB_SHARED_SAMPLES_HPP_
