/*
 Copyright (c) 2014, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_COLLECTIONTYPESIMPL_HPP_
#define RTI_DDS_CORE_XTYPES_COLLECTIONTYPESIMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/vector.hpp>
#include <dds/core/xtypes/DynamicType.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

/**
 * @RTI_class_definition class CollectionType : public DynamicType
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/CollectionTypes.hpp
 * @brief @st_value_type The base class of all collection types
 */
class OMG_DDS_API CollectionTypeImpl : public DynamicTypeImpl {
protected:
    CollectionTypeImpl() {}

public:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(CollectionTypeImpl, DynamicTypeImpl)

    /**
     * @brief Gets the type of the elements of this collection
     */
    const dds::core::xtypes::DynamicType& content_type() const;
};

/**
 * @RTI_class_definition class UnidimensionalCollectionTypeImpl : public CollectionType
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/CollectionTypes.hpp
 * @brief @st_value_type The base class of collection types with only one dimension.
 */
class OMG_DDS_API UnidimensionalCollectionTypeImpl : public CollectionTypeImpl {
public:
    static const uint32_t UNBOUNDED = RTI_INT32_MAX;

protected:
    UnidimensionalCollectionTypeImpl() {}

public:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(UnidimensionalCollectionTypeImpl, CollectionTypeImpl)

    /**
     * @brief Gets the maximum length of this collection.
     */
    uint32_t bounds() const;
};

/**
 * @RTI_class_definition class SequenceType : public UnidimensionalCollectionTypeImpl
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/CollectionTypes.hpp
 * @brief @st_value_type Represents an IDL \p sequence type.
 */
class OMG_DDS_API SequenceTypeImpl : public UnidimensionalCollectionTypeImpl {
public:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(SequenceTypeImpl, UnidimensionalCollectionTypeImpl)

    /**
     * @brief Creates an unbounded collection with an element type
     *
     * @param type The element type
     */
    explicit SequenceTypeImpl(const dds::core::xtypes::DynamicType& type);

    /**
     * @brief Creates a bounded collection with an element type
     *
     * @param type The element type
     * @param bounds The maximum length
     */
    SequenceTypeImpl(
        const dds::core::xtypes::DynamicType& type, uint32_t bounds);

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Creates an unbounded collection with an element type
     *
     * @param type The element type
     */
    explicit SequenceTypeImpl(dds::core::xtypes::DynamicType&& type)
    {
        initialize(&type, UNBOUNDED, false);
    }

    /**
     * @brief @st_cpp11 Creates a bounded collection with an element type
     *
     * @param type The element type
     * @param the_bounds The maximum length
     */
    SequenceTypeImpl(dds::core::xtypes::DynamicType&& type, uint32_t the_bounds)
    {
        initialize(&type, the_bounds, false);
    }
  #endif

private:
    void initialize(
        const DynamicTypeImpl * type, uint32_t bounds, bool clone_type = true);
};

/**
 * @RTI_class_definition class StringType : public UnidimensionalCollectionTypeImpl
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/CollectionTypes.hpp
 * @brief @st_value_type Represents an IDL \p string type.
 */
class OMG_DDS_API StringTypeImpl : public UnidimensionalCollectionTypeImpl {
public:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(StringTypeImpl, UnidimensionalCollectionTypeImpl)

    /**
     * @brief Creates a bounded string
     *
     * @param bounds The maximum length
     */
    explicit StringTypeImpl(uint32_t bounds);
};

/**
 * @RTI_class_definition class WStringType : public UnidimensionalCollectionTypeImpl
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/CollectionTypes.hpp
 * @brief @st_value_type Represents an IDL \p wstring type.
 */
class OMG_DDS_API WStringTypeImpl : public UnidimensionalCollectionTypeImpl {
public:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(WStringTypeImpl, UnidimensionalCollectionTypeImpl)

    /**
     * @brief Creates a bounded wide string
     * @param bounds The maximum length
     */
    explicit WStringTypeImpl(uint32_t bounds);
};

/**
 * @RTI_class_definition class ArrayType : public CollectionType
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/CollectionTypes.hpp
 * @brief @st_value_type Represents an IDL array type.
 */
class OMG_DDS_API ArrayTypeImpl : public CollectionTypeImpl {
public:
    typedef dds::core::vector<uint32_t> DimensionsSeq;

    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(ArrayTypeImpl, CollectionTypeImpl)

    /**
     * @brief Creates an unidimensional array
     *
     * @param type The element type
     * @param the_dimension The dimension of this unidimensional array
     */
    ArrayTypeImpl(
        const dds::core::xtypes::DynamicType& type, uint32_t the_dimension)
    {
        initialize(&type, DimensionsSeq(1, the_dimension));
    }

    /**
     * @brief Creates a multidimensional array
     *
     * For example, to create the following IDL array:
     * \code
     * double x[10][20];
     * \endcode
     *
     * We can use this code:
     *
     * \code
     * std::vector<uint32_t> dim(2);
     * dim[0] = 10;
     * dim[1] = 20;
     * ArrayType my_array(primitive_type<double>(), dim.begin(), dim.end());
     * \endcode
     *
     * @param type The element type
     * @param dimensions_begin The beginning of range of dimensions (uint32_t)
     * @param dimensions_end The end of a range of dimensions (uint32_t)
     */
    template <typename IntegerFwdIterator>
    ArrayTypeImpl(
        const dds::core::xtypes::DynamicType& type,
        IntegerFwdIterator dimensions_begin,
        IntegerFwdIterator dimensions_end)
    {
        initialize(
            &type, std::vector<uint32_t>(dimensions_begin, dimensions_end));
    }

  #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief @st_cpp11 Creates a multidimensional array
     *
     * For example, to create the following IDL array:
     * \code
     * double x[10][20];
     * \endcode
     *
     * We can use this code:
     *
     * \code
     * ArrayType my_array(primitive_type<double>(), {10, 20});
     * \endcode
     *
     * @param type The element type
     * @param dimensions The dimensions of this array
     */
    ArrayTypeImpl(
        const dds::core::xtypes::DynamicType& type,
        std::initializer_list<uint32_t> dimensions)
    {
        initialize(
            &type, std::vector<uint32_t>(dimensions.begin(), dimensions.end()));
    }
  #endif

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Creates an unidimensional array
     *
     * @param type The element type (to be moved)
     * @param the_dimension The dimension of this unidimensional array
     */
    ArrayTypeImpl(dds::core::xtypes::DynamicType&& type, uint32_t the_dimension)
    {
        initialize(&type, DimensionsSeq(1, the_dimension), false);
    }

    /**
     * @brief @st_cpp11 Creates a multidimensional array
     *
     * @param type The element type (to be moved)
     * @param dimensions_begin The beginning of range of dimensions (uint32_t)
     * @param dimensions_end The end of a range of dimensions (uint32_t)
     */
    template <typename IntegerFwdIterator>
    ArrayTypeImpl(
        dds::core::xtypes::DynamicType&& type,
        IntegerFwdIterator dimensions_begin,
        IntegerFwdIterator dimensions_end)
    {
        initialize(
            &type,
            std::vector<uint32_t>(dimensions_begin, dimensions_end),
            false);
    }

   #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief @st_cpp11 Creates a multidimensional array
     *
     * @param type The element type (to be moved)
     * @param dimensions The dimensions of this array
     */
    ArrayTypeImpl(
        dds::core::xtypes::DynamicType&& type,
        std::initializer_list<uint32_t> dimensions)
    {
        initialize(
            &type,
            std::vector<uint32_t>(dimensions.begin(), dimensions.end()),
            false);
    }
   #endif
  #endif

    /**
     * @brief Returns the number of dimensions
     */
    uint32_t dimension_count() const;

    /**
     * @brief Returns the ith dimension
     */
    uint32_t dimension(uint32_t dimension_index) const;

    /**
     * @brief Returns the sum of all the dimensions
     */
    uint32_t total_element_count() const;

private:
    void initialize(
        const DynamicTypeImpl * type,
        const std::vector<uint32_t>& dimensions,
        bool clone_type = true);

    void initialize(
        const DynamicTypeImpl * type,
        const DimensionsSeq& dimensions,
        bool clone_type = true);
};

} } } // namespace rti::core::xtypes

#endif //RTI_DDS_CORE_XTYPES_COLLECTIONTYPESIMPL_HPP_
