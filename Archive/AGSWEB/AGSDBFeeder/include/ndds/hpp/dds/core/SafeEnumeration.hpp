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

#ifndef OMG_DDS_CORE_SAFEENUMERATION_HPP_
#define OMG_DDS_CORE_SAFEENUMERATION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

// DllExport.hpp should be the second include
#include <rti/core/DllExport.hpp>
#include <iosfwd>

namespace dds { namespace core {
/** 
 * @ingroup DDSInfrastructureModule
 * @defgroup SafeEnumModule Safe Enumeration
 * @brief Describes the safe_enum class.
 */

/** 
 * @ingroup SafeEnumModule
 * @brief @st_value_type Provides a safe, scoped enumeration based on def::type
 *
 * The purpose of this class is to provide a C++11-style enum class, where
 * the enumeration constants are scoped.
 *
 * @tparam def A struct containing the actual enumeration, \p def::type
 *
 * See for example dds::core::policy::ReliabilityKind. The actual enumeration is
 * in dds::core::policy::ReliabilityKind_def, but the application only needs
 * to use the former:
 *
 * \code
 * using dds::core::policy::ReliabilityKind;
 *
 * ReliabilityKind kind = ReliabilityKind::RELIABLE;
 * \endcode
 *
 */
template<typename def, typename inner = typename def::type>
class UserDllExport safe_enum : public def {
public:

    /**
     * The underlying \p enum type
     */
    typedef inner inner_enum;

public:

    /**
     * @brief Initializes the enumeration to zero
     *
     * @note Zero may not be a valid enumerator
     */
    safe_enum() : val(static_cast<inner>(0))
    {
    }

    /**
     * @brief Copy constructor
     */
    safe_enum(inner_enum v) : val(v) {}

    /**
     * @brief Retrieves the actual enumeration value
     */
    inner_enum underlying() const { return val; }

    /**
     * @brief Applies operator to underlying enumeration value
     */
    bool operator == (const safe_enum & s) const { return this->val == s.val; }

    /**
     * @brief Applies operator to underlying enumeration value
     */
    bool operator != (const safe_enum & s) const { return this->val != s.val; }

    /**
     * @brief Applies operator to underlying enumeration value
     */
    bool operator <  (const safe_enum & s) const { return this->val <  s.val; }
    /**
     * @brief Applies operator to underlying enumeration value
     */
    bool operator <= (const safe_enum & s) const { return this->val <= s.val; }

    /**
     * @brief Applies operator to underlying enumeration value
     */
    bool operator >  (const safe_enum & s) const { return this->val >  s.val; }

    /**
     * @brief Applies operator to underlying enumeration value
     */
    bool operator >= (const safe_enum & s) const { return this->val >= s.val; }

    /**
     * @brief Swaps to underlying enumeration value
     */
    OMG_DDS_API
    friend void swap(safe_enum& left, safe_enum& right) OMG_NOEXCEPT
    {
        std::swap(left.val, right.val);
    }

private:
    inner_enum val;
};

/** 
 * @relatesalso dds::core::safe_enum 
 * @brief Applies \p operator<< to the underlying enum
 */
template<typename def, typename inner>
std::ostream& operator<< (std::ostream& out, const safe_enum<def, inner>& the_enum)
{
    out << the_enum.underlying();
    return out;
}


} } // namespace dds::core



#endif /* OMG_DDS_CORE_SAFEENUMERATION_HPP_ */
