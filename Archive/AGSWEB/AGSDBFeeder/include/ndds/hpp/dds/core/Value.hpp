#ifndef OMG_DDS_CORE_VALUE_HPP_
#define OMG_DDS_CORE_VALUE_HPP_

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

#include <algorithm> // for std::swap

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>


#ifndef RTI_NO_CXX11_NOEXCEPT
#include <type_traits>
#endif

namespace dds {
  namespace core {
    template <typename D>
    class Value;
  }
}


/**
 * This class provides the basic behavior for Value types. 
 */
template <typename D>
class dds::core::Value {
protected:
    Value() { }
    Value(const Value& p) : d_(p.d_) { }

public:
    template <typename ARG>
    Value(const ARG& arg) : d_(arg) { }

    template <typename ARG1, typename ARG2>
    Value(const ARG1& arg1, const ARG2& arg2) : d_(arg1, arg2) { }

    template <typename ARG1, typename ARG2, typename ARG3>
    Value(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
        : d_(arg1, arg2, arg3) { }

    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
    Value(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
        : d_ (arg1, arg2, arg3, arg4)
    {
    }

    template <
        typename ARG1,
        typename ARG2,
        typename ARG3,
        typename ARG4,
        typename ARG5>
    Value(const ARG1& arg1, 
          const ARG2& arg2, 
          const ARG3& arg3, 
          const ARG4& arg4, 
          const ARG5& arg5)
        : d_(arg1, arg2, arg3, arg4, arg5)
    {
    }

    template <
        typename ARG1,
        typename ARG2,
        typename ARG3,
        typename ARG4,
        typename ARG5,
        typename ARG6>
    Value(
        const ARG1& arg1,
        const ARG2& arg2,
        const ARG3& arg3,
        const ARG4& arg4,
        const ARG5& arg5,
        const ARG6& arg6)
        : d_(arg1, arg2, arg3, arg4, arg5, arg6)
    {
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    Value(Value&& value)
        OMG_NOEXCEPT_IF(std::is_nothrow_move_constructible<D>::value)
        : d_(std::move(value.d_))
    {
    }
  #endif

public:
    ~Value() { }

public:
    Value& operator=(const Value& other)
    {
        if (this != &other) {
          d_ = other.d_;
        }
        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    Value& operator=(Value&& other)
        OMG_NOEXCEPT_IF(std::is_nothrow_move_assignable<D>::value)
    {
        d_ = std::move(other.d_);
        return *this;
    }
  #endif

    // Spec error: operators were not const

    bool operator==(const Value& other) const
    {
        return (d_ == other.d_);
    }

    bool operator !=(const Value& other) const
    {
        return !(d_ == other.d_);
    }


public:
    /**
     * Return the delegate.
     */
    const D* operator->() const OMG_NOEXCEPT
    {
        return &d_;
    }

    /**
     * Return the delegate.
     */
    D* operator->() OMG_NOEXCEPT
    {
        return &d_;
    }

    /**
     * Return the delegate.
     */
    const D& delegate() const OMG_NOEXCEPT
    {
        return d_;
    }

    /**
     * Return the delegate.
     */
    D& delegate() OMG_NOEXCEPT
    {
        return d_;
    }

    /**
     * Return the delegate.
     */
    operator D& () OMG_NOEXCEPT
    {
        return d_;
    }

    /**
     * Return the delegate.
     */
    operator const D& () const OMG_NOEXCEPT
    {
        return d_;
    }

protected:
  D d_;
};

namespace dds { namespace core {

template <typename D>
void swap(dds::core::Value<D>& left, dds::core::Value<D>& right)
    OMG_NOEXCEPT_IF(noexcept(swap(left.delegate(), right.delegate())))
{
    swap(left.delegate(), right.delegate());
}

} } // namespace dds::core


#endif /* OMG_DDS_CORE_VALUE_HPP_ */
