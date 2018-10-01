/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.7a,30jul14,eam Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_CUSTOM_FILTER_HPP_
#define RTI_DDS_TOPIC_CUSTOM_FILTER_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Reference.hpp>
#include <rti/core/detail/SelfReference.hpp>
#include <rti/topic/ContentFilter.hpp>

namespace rti { namespace topic {

/**
 * @ingroup DDSCustomContentFilterModule 
 * @headerfile rti/topic/CustomFilter.hpp 
 * @brief @extension @st_ref_type A wrapper class for the user-defined 
 * implementation of a ContentFilter. 
 *  
 * In order to register a custom content filter a user must: 
 * - Implement the content filter by creating their own class which inherits 
 * from one of the abstract classes: ContentFilter, WriterContentFilter, 
 * or WriterContentFilterHelper 
 * - Create a CustomFilter which holds a shared pointer to the user-defined 
 * content filter 
 * - Register the CustomFilter with the dds::domain::DomainParticipant 
 * using dds::domain::DomainParticipant::register_contentfilter 
 *  
 * The CustomFilter class prevents your content filter from being deleted while 
 * \ndds is using your filter by retaining a reference to your filter until it 
 * is no longer being used by \ndds. 
 *  
 * For an example of how to create anad register a custom content filter see
 * \ref NDDSCustomFilterExampleModuleForCpp2.
 *  
 * @tparam T The type of the custom content filter that is being registered. It 
 * must be a type which inherits and implements the interface of one of  
 * ContentFilter, WriterContentFilter, or WriterContentFilterHelper 
 *  
 */
template <typename T>
class CustomFilter : public dds::core::Reference<T>
{
    OMG_DDS_REF_TYPE(CustomFilter, dds::core::Reference, T)
public:

    // Contructor from shared pointer to make polymorphic cast work
    /**
     * @brief Create a CustomFilter which holds a shared pointer to a 
     * user-defined content filter
     * 
     * @param content_filter_ref A shared pointer to a user-defined content 
     * filter object.
     */
    CustomFilter(
        typename dds::core::smart_ptr_traits<T>::ref_type content_filter_ref)
    : dds::core::Reference<T>(content_filter_ref) {}

    ~CustomFilter() {}

    /**
     * @brief Get a const pointer to the underlying content filter
     */
    const T* get() const
    {
        return this->delegate().get();
    }

    /**
     * @brief Get a pointer to the underlying content filter
     */
    T* get()
    {
        return this->delegate().get();
    }
};

class FilterHolderImpl : public rti::core::detail::RetainableType<FilterHolderImpl> {
public:    
    typedef rti::core::detail::RetainableType<FilterHolderImpl> Base;

    typedef Base::ref_type ref_type;
    typedef Base::weak_ref_type weak_ref_type;

    FilterHolderImpl(const CustomFilter<ContentFilterBase>& filter)
      : custom_filter_(filter)
    {}

    ~FilterHolderImpl(){}

    CustomFilter<ContentFilterBase>& custom_filter()
    {
        return custom_filter_;
    }

private:
    CustomFilter<ContentFilterBase> custom_filter_;
};

class OMG_DDS_API FilterHolder : public dds::core::Reference<FilterHolderImpl> {
public:
    explicit FilterHolder(const CustomFilter<ContentFilterBase>& filter)
      : dds::core::Reference<FilterHolderImpl>(
         new FilterHolderImpl(filter))
    {
        // Setup FilterHolderImpl's self-reference
        this->delegate()->remember_reference(this->delegate());
    }

    FilterHolder(FilterHolderImpl::ref_type delegate_ref)
      : dds::core::Reference<FilterHolderImpl>(delegate_ref)
    {
        // Setup FilterHolderImpl's self-reference
        this->delegate()->remember_reference(this->delegate());
    }

    // Constructor from null
    FilterHolder(const dds::core::null_type&)
      : dds::core::Reference<FilterHolderImpl>(
         static_cast<FilterHolderImpl*>(NULL)) 
    { 
    }

    CustomFilter<ContentFilterBase>& custom_filter() const
    {
        return delegate()->custom_filter();
    }

    void retain() const
    {
        delegate()->retain();
    }

    void unretain()
    {
        delegate()->unretain();
    }

    bool operator==(dds::core::null_type) const
    {
        return delegate().get() == 0;
    }
};

// ContentFilter and WriterContentFilter's to_native calls must be defined here 
// because they need access to FilterHolder's full definition
template<typename T, typename CompileData>
void ContentFilter<T, CompileData>::to_native(
   const rti::topic::FilterHolder& filter, 
   struct DDS_ContentFilter* c_filter)
{
    c_filter->compile = 
        compile_wrapper<T, CompileData>;
    c_filter->evaluate = 
        evaluate_wrapper<T, CompileData>;
    c_filter->finalize = 
        finalize_wrapper<T, CompileData>;

    c_filter->writer_compile = NULL;
    c_filter->writer_evaluate = NULL;
    c_filter->writer_finalize = NULL;
    c_filter->writer_attach = NULL;
    c_filter->writer_detach = NULL;
    c_filter->writer_return_loan = NULL;

    c_filter->filter_data = reinterpret_cast<void *>(
       &(const_cast<FilterHolder&>(filter).delegate()->get_weak_reference()));
}

template <typename T, typename CompileData, typename WriterFilterData>
void WriterContentFilter<T, CompileData, WriterFilterData>::to_native(
   const rti::topic::FilterHolder& filter, 
   struct DDS_ContentFilter* c_filter)
{
    c_filter->compile = 
        compile_wrapper<T, CompileData>;
    c_filter->evaluate = 
        evaluate_wrapper<T, CompileData>;
    c_filter->finalize = 
        finalize_wrapper<T, CompileData>;

    c_filter->writer_compile = 
        writer_compile_wrapper<T, CompileData, WriterFilterData>;
    c_filter->writer_evaluate = 
        writer_evaluate_wrapper<T, CompileData, WriterFilterData>;
    c_filter->writer_finalize = 
        writer_finalize_wrapper<T, CompileData, WriterFilterData>;
    c_filter->writer_attach = 
        writer_attach_wrapper<T, CompileData, WriterFilterData>;
    c_filter->writer_detach = 
        writer_detach_wrapper<T, CompileData, WriterFilterData>;
    c_filter->writer_return_loan = 
        writer_return_loan_wrapper<T, CompileData, WriterFilterData>;

    c_filter->filter_data = reinterpret_cast<void *>(
       &(const_cast<FilterHolder&>(filter).delegate()->get_weak_reference()));
}

OMG_DDS_API FilterHolder
create_filter_holder_from_filter_data(void *filter_data);

//ContentFilterBase* get_filter_ptr(void *filter_data);

} } // namespace rti::topic

#endif // RTI_DDS_TOPIC_CUSTOM_FILTER_HPP_
