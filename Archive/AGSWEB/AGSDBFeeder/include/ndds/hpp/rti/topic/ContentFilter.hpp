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

#ifndef RTI_DDS_TOPIC_CONTENT_FILTER_HPP_
#define RTI_DDS_TOPIC_CONTENT_FILTER_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/topic/ExpressionProperty.hpp>
#include <rti/topic/FilterSampleInfo.hpp>
#include <rti/core/Cookie.hpp>
#include <dds/core/Optional.hpp>
#include <dds/core/xtypes/DynamicType.hpp>
#include <dds/core/types.hpp> // StringSeq
#include <rti/core/detail/NativeConversion.hpp> // from_native, to_native
#include <dds/core/ref_traits.hpp> // for polymorphic_cast

#include "dds_c/dds_c_topic.h" // DDS_ContentFilter
#include "dds_c/dds_c_typecode.h"
#include "dds_c/dds_c_infrastructure.h"


// forward declaration
namespace rti { namespace domain {
class DomainParticipantImpl;
}
}

/** @defgroup DDSCustomContentFilterModule Custom Content Filters
 * @ingroup DDSTopicModule
 * 
 * @brief Classes and associated types used to implement custom content filters
 */

namespace rti { namespace topic {

// A type to specify that no compile data will be created by a user
/** 
 * @ingroup DDSCustomContentFilterModule 
 * @relatesalso ContentFilter 
 * @headerfile rti/topic/ContentFilter.hpp 
 * @brief The type to specify as the CompileData template parameter to your 
 * ContentFilter if your compile function does not return any data
 */
struct no_compile_data_t {};

// A global variable that a user can return in the compile function if they do
// not wish to create compile data
/** 
 * @ingroup DDSCustomContentFilterModule 
 * @relatesalso ContentFilter 
 * @headerfile rti/topic/ContentFilter.hpp 
 * @brief A constant to return if your compile function does not create any 
 * compile data  
 */
extern OMG_DDS_API_VARIABLE no_compile_data_t no_compile_data;

// Forward declarations
class FilterHolder;

template <typename T>
class CustomFilter;

class ContentFilterBase;

template<typename T, typename CompileData>
class ContentFilter;

template<typename T, typename CompileData, typename WriterFilterData>
class WriterContentFilter;

OMG_DDS_API
CustomFilter<ContentFilterBase>& get_filter_ref(void *filter_data);

// Wrapper functions to be called from C
template<typename T, typename CompileData>
DDS_ReturnCode_t compile_wrapper(
    void *filter_data,
    void **new_compile_data,
    const char *expression,
    const struct DDS_StringSeq *parameters,
    const struct DDS_TypeCode *type_code,
    const char *type_class_name,
    void *old_compile_data) {

    using namespace rti::core::native_conversions;

    typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
    typedef CustomFilter<ContentFilter<T, CompileData> > CustomContentFilter;
    typedef dds::core::optional<dds::core::xtypes::DynamicType> OptionalDynamicType;

    // Cast the stored CustomFilter to the user's CustomFilter type, 
    // through a polymorphic dynamic cast
    CustomContentFilterBase& custom_filter = 
        get_filter_ref(filter_data);

    CustomContentFilter filter = dds::core::polymorphic_cast<
        CustomContentFilter, CustomContentFilterBase>(custom_filter);

    try {
        // The following cast for the type_code parameter is necessary because 
        // creating an optional object requires a copy of the object that it is
        // holding, and we want to avoid that copy. 
        CompileData& compile_data =
            filter->compile(
            expression,
            from_native<std::string, DDS_StringSeq>(*parameters),
            type_code == NULL ? 
            OptionalDynamicType() :
            reinterpret_cast<const OptionalDynamicType&>(type_code),
            type_class_name,
            reinterpret_cast<CompileData *>(old_compile_data));

        *new_compile_data = reinterpret_cast<void *>(&compile_data);
    }
    catch (const std::exception& ex) {
        DDSLog_exception(
            "compile", &RTI_LOG_ANY_FAILURE_s, ex.what());
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

template<typename T, typename CompileData>
DDS_Boolean evaluate_wrapper(
    void *filter_data,
    void *compile_data,
    const void *sample,
    const struct DDS_FilterSampleInfo *meta_data) {

    typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
    typedef CustomFilter<ContentFilter<T, CompileData> > CustomContentFilter;

    // Cast the stored CustomFilter to the user's CustomFilter type, 
    // through a polymorphic dynamic cast
    CustomContentFilterBase& custom_filter = 
        get_filter_ref(filter_data);

    CustomContentFilter filter = dds::core::polymorphic_cast<
        CustomContentFilter, CustomContentFilterBase>(custom_filter);

    DDS_Boolean result = DDS_BOOLEAN_FALSE;

    try {
        result = filter->evaluate(
            *reinterpret_cast<CompileData *>(compile_data),
            *reinterpret_cast<const T *>(sample),
            *meta_data);
    }
    catch (const std::exception& ex) {
        DDSLog_exception(
            "evaluate", &RTI_LOG_ANY_FAILURE_s, ex.what());
        return DDS_BOOLEAN_FALSE;
    }

    return result;
}

template<typename T, typename CompileData>
void finalize_wrapper(
    void *filter_data, void *compile_data) {

    typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
    typedef CustomFilter<ContentFilter<T, CompileData> > CustomContentFilter;

    // Cast the stored CustomFilter to the user's CustomFilter type, 
    // through a polymorphic dynamic cast
    CustomContentFilterBase& custom_filter = 
        get_filter_ref(filter_data);

    CustomContentFilter filter = dds::core::polymorphic_cast<
        CustomContentFilter, CustomContentFilterBase>(custom_filter);

    try {
        filter->finalize(
            *reinterpret_cast<CompileData *>(compile_data));
    }
    catch (const std::exception& ex) {
        DDSLog_exception(
            "finalize", &RTI_LOG_ANY_FAILURE_s, ex.what());
    }
}

template<typename T, typename CompileData, typename WriterFilterData>
DDS_ReturnCode_t writer_attach_wrapper(
    void *native_filter_data, void **writer_filter_data, void *) {

    typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
    typedef CustomFilter<WriterContentFilter<T, CompileData, WriterFilterData> >
        CustomWriterContentFilter;

    // Cast the stored CustomFilter to the user's CustomFilter type, 
    // through a polymorphic dynamic cast
    CustomContentFilterBase& custom_filter = 
        get_filter_ref(native_filter_data);

    CustomWriterContentFilter filter = dds::core::polymorphic_cast<
        CustomWriterContentFilter, CustomContentFilterBase>(custom_filter);

    try {
        WriterFilterData& filter_data =
            filter->writer_attach();

        *writer_filter_data = reinterpret_cast<void *>(&filter_data);
    }
    catch (const std::exception& ex) {
        DDSLog_exception(
            "writer_attach", &RTI_LOG_ANY_FAILURE_s, ex.what());
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

template<typename T, typename CompileData, typename WriterFilterData>
void writer_detach_wrapper(
    void *filter_data, void *writer_filter_data) {

    typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
    typedef CustomFilter<WriterContentFilter<T, CompileData, WriterFilterData> >
        CustomWriterContentFilter;

    // Cast the stored CustomFilter to the user's CustomFilter type, 
    // through a polymorphic dynamic cast
    CustomContentFilterBase& custom_filter = 
        get_filter_ref(filter_data);

    CustomWriterContentFilter filter = dds::core::polymorphic_cast<
        CustomWriterContentFilter, CustomContentFilterBase>(custom_filter);

    try {
        filter->writer_detach(
            *reinterpret_cast<WriterFilterData *>(writer_filter_data));
    } catch (const std::exception& ex) {
        DDSLog_exception(
            "writer_detach", &RTI_LOG_ANY_FAILURE_s, ex.what());
    }
}

template<typename T, typename CompileData, typename WriterFilterData>
DDS_ReturnCode_t writer_compile_wrapper(
    void *filter_data,
    void *writer_filter_data,
    struct DDS_ExpressionProperty *prop,
    const char *expression,
    const struct DDS_StringSeq *parameters,
    const struct DDS_TypeCode *type_code,
    const char *type_class_name,
    const struct DDS_Cookie_t *cookie){

   using namespace rti::core::native_conversions;

   typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
   typedef CustomFilter<WriterContentFilter<T, CompileData, WriterFilterData> >
       CustomWriterContentFilter;
   typedef dds::core::optional<dds::core::xtypes::DynamicType> OptionalDynamicType;

   // Cast the stored CustomFilter to the user's CustomFilter type, 
   // through a polymorphic dynamic cast
   CustomContentFilterBase& custom_filter = 
       get_filter_ref(filter_data);

   CustomWriterContentFilter filter = dds::core::polymorphic_cast<
       CustomWriterContentFilter, CustomContentFilterBase>(custom_filter);

    try {
        // The following cast for the type_code parameter is necessary because 
        // creating an optional object requires a copy of the object that it is
        // holding, and we want to avoid that copy. 
        filter->writer_compile(
            *reinterpret_cast<WriterFilterData *>(writer_filter_data),
            reinterpret_cast<rti::topic::ExpressionProperty&>(*prop),
            expression,
            from_native<std::string, DDS_StringSeq>(*parameters),
            type_code == NULL ? 
            OptionalDynamicType() :
            reinterpret_cast<const OptionalDynamicType&>(type_code),
            type_class_name,
            *cookie);
    } catch(const std::exception& ex){
        DDSLog_exception(
            "writer_compile", &RTI_LOG_ANY_FAILURE_s, ex.what());
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

template<typename T, typename CompileData, typename WriterFilterData>
DDS_CookieSeq* writer_evaluate_wrapper(
    void *filter_data,
    void *writer_filter_data,
    const void *sample,
    const struct DDS_FilterSampleInfo *meta_data) {

    using namespace rti::core::native_conversions;
    DDS_CookieSeq *cookies = NULL;

    typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
    typedef CustomFilter<WriterContentFilter<T, CompileData, WriterFilterData> >
        CustomWriterContentFilter;

    // Cast the stored CustomFilter to the user's CustomFilter type, 
    // through a polymorphic dynamic cast
    CustomContentFilterBase& custom_filter = 
        get_filter_ref(filter_data);

    CustomWriterContentFilter filter = dds::core::polymorphic_cast<
        CustomWriterContentFilter, CustomContentFilterBase>(custom_filter);

    try {
        cookies = reinterpret_cast<struct DDS_CookieSeq *>(
            &filter->writer_evaluate(
                *reinterpret_cast<WriterFilterData *>(writer_filter_data),
                *reinterpret_cast<const T *>(sample),
                *meta_data));
    }
    catch (const std::exception& ex) {
        DDSLog_exception(
            "writer_evaluate", &RTI_LOG_ANY_FAILURE_s, ex.what());
    }

    return cookies;
}

template<typename T, typename CompileData, typename WriterFilterData>
void writer_return_loan_wrapper(
                                void *filter_data,
                                void *writer_filter_data,
                                struct DDS_CookieSeq *cookies){

    typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
    typedef CustomFilter<WriterContentFilter<T, CompileData, WriterFilterData> >
        CustomWriterContentFilter;

    // Cast the stored CustomFilter to the user's CustomFilter type, 
    // through a polymorphic dynamic cast
    CustomContentFilterBase& custom_filter = 
        get_filter_ref(filter_data);

    CustomWriterContentFilter filter = dds::core::polymorphic_cast<
        CustomWriterContentFilter, CustomContentFilterBase>(custom_filter);

    rti::core::CookieSeq my_seq;

    try {
        filter->writer_return_loan(
            *reinterpret_cast<WriterFilterData *>(writer_filter_data),
            *reinterpret_cast<rti::core::CookieSeq *>(cookies));
    } catch (const std::exception& ex){
        DDSLog_exception(
            "writer_return_loan", &RTI_LOG_ANY_FAILURE_s, ex.what());
    }
}

template<typename T, typename CompileData, typename WriterFilterData>
void writer_finalize_wrapper(
    void *filter_data,
    void *writer_filter_data,
    const struct DDS_Cookie_t *cookie) {

    typedef CustomFilter<ContentFilterBase> CustomContentFilterBase;
    typedef CustomFilter<WriterContentFilter<T, CompileData, WriterFilterData> >
        CustomWriterContentFilter;

    // Cast the stored CustomFilter to the user's CustomFilter type, 
    // through a polymorphic dynamic cast
    CustomContentFilterBase& custom_filter = 
        get_filter_ref(filter_data);

    CustomWriterContentFilter filter = dds::core::polymorphic_cast<
        CustomWriterContentFilter, CustomContentFilterBase>(custom_filter);

    try {
        filter->writer_finalize(
            *reinterpret_cast<WriterFilterData *>(writer_filter_data),
            *cookie);
    } catch (const std::exception& ex) {
        DDSLog_exception(
            "writer_finalize", &RTI_LOG_ANY_FAILURE_s, ex.what());
    }
}

// Untyped base class for ContentFilter so that CustomFilter does not have to
// be a template
class ContentFilterBase {
    friend class rti::domain::DomainParticipantImpl;
public:
    virtual ~ContentFilterBase() { }

private:
    virtual void to_native(
        const rti::topic::FilterHolder& filter_holder,
        struct DDS_ContentFilter *c_filter) = 0;
};

// A user will inherit from one of the following 3 classes and then implement
// the virtual functions in this class

// -- ContentFilter ----------------------------------------------------------

/**
 * @ingroup DDSCustomContentFilterModule 
 * @headerfile rti/topic/ContentFilter.hpp
 * @RTI_class_definition template<typename T, typename CompileData = no_compile_data_t> class ContentFilter 
 * @brief @extension A class to inherit from when implementing a 
 * custom content filter 
 *  
 * This interface can be implemented by an application-provided class and
 * then registered with the DomainParticipant such that samples can be
 * filtered for dds::topic::ContentFilteredTopic with the filter name that the
 * filter is registered with.
 *
 * \b Note: the API for using a custom content filter is subject to change in a future release.
 * 
 * For an example of how to create a custom content filter see
 * \ref NDDSCustomFilterExampleModuleForCpp2
 * 
 * @tparam T The type of the samples that this ContentFilter will filter 
 * @tparam CompileData the type of the data that the compile function will 
 * return. If your compile function will not return data, you can leave this 
 * template parameter to the default no_compile_data_t type and return 
 * rti::topic::no_compile_data in your compile function  
 *  
 * @see rti::topic::CustomFilter 
 * @see dds::domain::DomainParticipant::register_contentfilter()
 */
template<typename T,
         typename CompileData = no_compile_data_t>
class ContentFilter : public ContentFilterBase {

public:
    virtual ~ContentFilter() { };

    /**
     * @brief Compile an instance of the content filter according to the filter 
     * expression and parameters of the given data type.
     *  
     * \dref_ContentFilterCompileDesc 
     *  
     * @param expression An std::string with the filter expression. If you want 
     * to manipulate this string, you \b must first make a copy of it. 
     *  
     * @param parameters A string sequence with the expression parameters the 
     * ContentFilteredTopic was created with. The string sequence is 
     * \b equal (but \b not identical) to the string sequence passed to 
     * dds::topic::ContentFilteredTopic(). Note that the 
     * sequence passed to the compile function is \b owned by \ndds and 
     * \b must \b not be referenced outside the compile function. 
     *  
     * @param type_code The DynamicType for the related Topic of the
     * ContentFilteredTopic. A type code is a description of a type in terms 
     * of which \b types it contains (such as long, string, etc.) and the
     * corresponding member field names in the data type structure.
     * The type code can be used to write custom content filters that can
     * be used with any type. 
     *  
     * @param type_class_name Fully qualified class name of the related Topic. 
     *  
     * @param old_compile_data The previous CompileData
     * value from a previous call to this instance of a content filter.
     * If the compile function is called more than once for an instance
     * of a ContentFilteredTopic, e.g., if the expression parameters
     * are changed, then the CompileData value returned by the
     * previous invocation is passed in the old_compile_data
     * parameter (which can be NULL). If this is a new instance of
     * the filter, NULL is passed. This parameter is useful for freeing or 
     * reusing previously allocated resources.
     * 
     * @return User specified compile data for this instance of the content 
     * filter. This value is then passed to the evaluate finalize functions for
     * this instance of the content filter. Can be set to 
     * rti::topic::no_compile_data.
     */
    virtual CompileData& compile(
        const std::string& expression,
        const dds::core::StringSeq& parameters,
        const dds::core::optional<dds::core::xtypes::DynamicType>& type_code,
        const std::string& type_class_name,
        CompileData *old_compile_data) = 0;

    /**
     * @brief Evaluate whether the sample is passing the filter or not 
     * according to the sample content. 
     *  
     * \dref_ContentFilterEvaluateDesc 
     * 
     * @param compile_data The last return value of the compile function for 
     * this instance of the content filter.
     * @param sample A deserialized sample to be filtered.
     * @param meta_data Meta data associated with the sample.
     * 
     * @return The function must return false if the sample should be filtered 
     * out (did not pass the filter), true otherwise
     */
    virtual bool evaluate(
        CompileData& compile_data,
        const T& sample,
        const FilterSampleInfo& meta_data) = 0;

    /**
     * @brief A previously compiled instance of the content filter is no longer 
     * in use and resources can now be cleaned up. 
     *  
     * \dref_ContentFilterFinalizeDesc 
     * 
     * @param compile_data The last return value of the compile function for 
     * this instance of the content filter.
     */
    virtual void finalize(CompileData& compile_data) = 0;

private:
    virtual void to_native(
        const rti::topic::FilterHolder& filter_holder, 
        struct DDS_ContentFilter *c_filter);
};

// -- WriterContentFilter ----------------------------------------------------
/** 
 * @ingroup DDSCustomContentFilterModule 
 * @headerfile rti/topic/ContentFilter.hpp 
 * @brief @extension A class to inherit from when implementing a writer-side
 * custom content filter 
 *  
 * This interface can be implemented by an application-provided class and
 * then registered with the DomainParticipant such that samples can be
 * filtered for dds::topic::ContentFilteredTopic with the filter name that the
 * filter is registered with. This class inherits from rti::topic::ContentFilter,
 * therefore you must implement the compile, evaluate, and finalize funtions
 * from that class in addition to the functions in this class. 
 *
 * \b Note: the API for using a custom content filter is subject to change in a
 * future release.
 * 
 * For an example of how to create a custom content filter see
 * \ref NDDSCustomFilterExampleModuleForCpp2
 *               
 * @tparam T The type of the samples that this ContentFilter will filter 
 * @tparam CompileData the type of the data that the compile function will 
 * return. If your compile function will not return data, you can leave this 
 * template parameter to the default no_compile_data_t type and return 
 * rti::topic::no_compile_data in your compile function
 * @tparam WriterFilterData the type of the data that the writer_attach function
 * will return. If your writer_attach function will not return data, you can
 * leave this template parameter to the default no_compile_data_t type and
 * return rti::topic::no_compile_data in your compile function
 *  
 * @see rti::topic::CustomFilter 
 * @see rti::topic::ContentFilter 
 * @see dds::domain::DomainParticipant::register_contentfilter()
 */
template<typename T,
         typename CompileData = no_compile_data_t,
         typename WriterFilterData = no_compile_data_t>
class WriterContentFilter : public ContentFilter<T, CompileData> {
public:
    virtual ~WriterContentFilter() { };

    // DDS_TypeCode can be NULL--take this into account when changing it to
    // DynamicType (probably making the parameter a boost::optional type)
    /**
     * @brief A writer-side filtering API to compile an instance of the content 
     * filter according to the filter expression and parameters specified by a 
     * matching dds::sub::DataReader. 
     *  
     * \dref_ContentFilterWriterCompileDesc 
     * 
     * @param writer_filter_data The state created using writer_attach
     * @param prop An ExpressionProperty that allows you to indicate 
     * to \ndds if a filter expression can be optimized. 
     *  
     * @param expression An std::string with the filter expression. If you want 
     * to manipulate this string, you \b must first make a copy of it. 
     *  
     * @param parameters A string sequence with the expression parameters the 
     * ContentFilteredTopic was created with. The string sequence is 
     * \b equal (but \b not identical) to the string sequence passed to 
     * dds::topic::ContentFilteredTopic(). Note that the 
     * sequence passed to the compile function is \b owned by \ndds and 
     * \b must \b not be referenced outside the compile function. 
     *  
     * @param type_code The DynamicType for the related Topic of the
     * ContentFilteredTopic. A type code is a description of a type in terms 
     * of which \b types it contains (such as long, string, etc.) and the
     * corresponding member field names in the data type structure.
     * The type code can be used to write custom content filters that can
     * be used with any type. 
     *  
     * @param type_class_name Fully qualified class name of the related Topic. 
     *  
     * @param cookie rti::core::Cookie to uniquely identify the 
     * DataReader for which writer_compile was called
     */
    virtual void writer_compile(
        WriterFilterData& writer_filter_data,
        ExpressionProperty& prop,
        const std::string& expression,
        const dds::core::StringSeq& parameters,
        const dds::core::optional<dds::core::xtypes::DynamicType>& type_code,
        const std::string& type_class_name,
        const rti::core::Cookie& cookie) = 0;

    /**
     * @brief A writer-side filtering API to compile an instance of the content 
     * filter according to the filter expression and parameters specified by a 
     * matching dds::sub::DataReader. 
     *  
     * \dref_ContentFilterWriterEvaluateDesc 
     * 
     * @param writer_filter_data The state created using the writer_compile method
     * @param sample A deserialized sample to be filtered.
     * @param meta_data Meta data associated with the sample.
     * 
     * @return A rti::core::CookieSeq which identifies the set of DataReaders whose 
     * filters pass the sample.
     */
    virtual rti::core::CookieSeq& writer_evaluate(
        WriterFilterData& writer_filter_data,
        const T& sample,
        const FilterSampleInfo& meta_data) = 0;

    /**
     * @brief A writer-side filtering API to clean up a previously compiled 
     * instance of the content filter. 
     *  
     * \dref_ContentFilterWriterFinalizeDesc 
     * 
     * @param writer_filter_data The state created using writer_attach
     * @param cookie rti::core::Cookie to uniquely identify the DataReader for 
     * which this method was invoked
     */
    virtual void writer_finalize(
        WriterFilterData& writer_filter_data,
        const rti::core::Cookie& cookie) = 0;

    /**
     * @brief A writer-side filtering API to create some state that can 
     * facilitate filtering on the writer side. 
     *  
     * \dref_ContentFilterWriterAttachDesc 
     * 
     * @return An object of user-specified type to some state created on the 
     * DataWriter that will help perform writer-side filtering efficiently. Can 
     * be no_compile_data 
     */
    virtual WriterFilterData& writer_attach() = 0;

    /**
     * @brief A writer-side filtering API to clean up a previously created 
     * state using writer_attach. 
     *  
     * \dref_ContentFilterWriterDetachDesc 
     * 
     * @param writer_filter_data The state created using writer_attach
     */
    virtual void writer_detach(WriterFilterData& writer_filter_data) = 0;

    /**
     * @brief A writer-side filtering API to return the loan on the list of 
     * DataReaders returned by writer_evaluate. 
     *  
     * \dref_ContentFilterWriterReturnLoanDesc 
     * 
     * @param writer_filter_data The state created using writer_attach
     * @param cookies rti::core::CookieSeq for which writer_return_loan 
     * was invoked
     */
    virtual void writer_return_loan(
        WriterFilterData& writer_filter_data,
        rti::core::CookieSeq& cookies) = 0;

private:
    void to_native(
        const rti::topic::FilterHolder& filter_holder,
        struct DDS_ContentFilter *c_filter);
};

// -- WriterContentFilterHelper ----------------------------------------------
// A helper class that manages the CookieSeq returned by writer_evaluate. A
// user can inherit from this class instead of from WriterContentFilter
/** 
 * @ingroup DDSCustomContentFilterModule 
 * @headerfile rti/topic/ContentFilter.hpp 
 * @brief @extension A class to inherit from when implementing a writer-side
 * custom content filter. 
 *  
 * This class manages for you the rti::core::CookieSeq 
 * which maintains a list of Cookies associated with the DataReaders whose 
 * filters pass the sample. 
 *  
 * This class has a private CookieSeq member that you can add cookies too using 
 * the helper method, add_cookie(), and the sequence is automatically cleared 
 * for you in the return_loan method, meaning that you do not need to implement 
 * that method yourself.  
 *  
 * For an example of how to create a custom content filter see
 * \ref NDDSCustomFilterExampleModuleForCpp2
 *               
 * @tparam T The type of the samples that this ContentFilter will filter 
 * @tparam CompileData the type of the data that the compile function will 
 * return. If your compile function will not return data, you can leave this 
 * template parameter to the default no_compile_data_t type and return 
 * rti::topic::no_compile_data in your compile function
 * @tparam WriterFilterData the type of the data that the writer_attach function
 * will return. If your writer_attach function will not return data, you can
 * leave this template parameter to the default no_compile_data_t type and
 * return rti::topic::no_compile_data in your compile function
 *  
 * @see rti::topic::CustomFilter 
 * @see rti::topic::WriterContentFilter 
 * @see rti::topic::ContentFilter 
 * @see dds::domain::DomainParticipant::register_contentfilter()
 */
template<typename T,
         typename CompileData = no_compile_data_t,
         typename WriterFilterData = no_compile_data_t>
class WriterContentFilterHelper :
    public WriterContentFilter<T, CompileData, WriterFilterData> {
public:
    virtual ~WriterContentFilterHelper() { };

    /** @RTI_remove_lines 11 */
    rti::core::CookieSeq& writer_evaluate(
        WriterFilterData& writer_filter_data,
        const T& sample,
        const FilterSampleInfo& meta_data)
    {
        // Call the user's evaluate implementation and then return the
        // CookeiSeq
        writer_evaluate_helper(writer_filter_data, sample, meta_data);

        return cookie_seq_;
    }

    /**
     * @brief A writer-side filtering API to compile an instance of the content 
     * filter according to the filter expression and parameters specified by a 
     * matching dds::sub::DataReader. 
     *  
     * \dref_ContentFilterWriterEvaluateDesc 
     *  
     * When using the WriterContentFilterHelper helper class, you implement 
     * this method instead of writer_evaluate. The writer_evaluate function 
     * calls this method and then returns the CookieSeq for you.
     * 
     * @param writer_filter_data The state created using the writer_compile method
     * @param sample A deserialized sample to be filtered.
     * @param meta_data Meta data associated with the sample.
     */
    virtual void writer_evaluate_helper(
        WriterFilterData& writer_filter_data,
        const T& sample,
        const FilterSampleInfo& meta_data) = 0;

    /** @RTI_remove_lines 7 */
    void writer_return_loan(
        WriterFilterData&,
        rti::core::CookieSeq&)
    {
        // Clear the CookieSeq
        cookie_seq_.resize(0);
    }

protected:
    /**
     * @brief A helper function which will add a rti::core::Cookie to the 
     * CookieSeq that is then returned by the writer_evaluate function. 
     *  
     * Call this method from writer_evaluate_helper whenever you need to add a 
     * Cookie for a DataReader whose filter has passed a particular sample.
     * 
     * @param cookie The cookie to add to the CookieSeq
     */
    void add_cookie(rti::core::Cookie& cookie)
    {
        // Resize the CookieSeq and add the cookie
        cookie_seq_.resize(cookie_seq_.size() + 1);
        cookie_seq_[cookie_seq_.size() - 1] = cookie;
    }

private:
    rti::core::CookieSeq cookie_seq_;
};

OMG_DDS_API bool is_builtin_filter(const std::string& name);

/** 
 * @ingroup DDSDomainParticipantModule 
 * @brief @extension The name of the built-in SQL filter that can be used 
 *        with dds::topic::ContentFilteredTopic and
 *        rti::core::policy::MultiChannel dds::pub::DataWriter.
 */
OMG_DDS_API std::string sql_filter_name();

/** 
 * @ingroup DDSDomainParticipantModule 
 * @brief @extension The name of the built-in StringMatch filter that can be 
 *        used with dds::topic::ContentFilteredTopic
 *        and rti::core::policy::MultiChannel dds::pub::DataWriter.
 * @details @dref_Shared_string_match_filter 
 */
OMG_DDS_API std::string stringmatch_filter_name();

}
} // namespace rti::topic


#endif // RTI_DDS_TOPIC_CONTENT_FILTER_HPP_
