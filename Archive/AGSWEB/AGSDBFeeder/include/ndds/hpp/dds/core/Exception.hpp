#ifndef OMG_DDS_CORE_EXCEPTION_HPP_
#define OMG_DDS_CORE_EXCEPTION_HPP_

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

#include <stdexcept>
#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace dds { namespace core {

/** 
 * @ingroup DDSInfrastructureModule 
 * @defgroup DDSException Exceptions 
 * @section DDSReturnTypesModule_std_retcodes Standard Exceptions 
 *
 * Any operation can can throw one of the DDS "standard exceptions", which are
 * the following:
 *  \li dds::core::Error
 *  \li dds::core::IllegalOperationError
 *  \li dds::core::AlreadyClosedError
 *  \li dds::core::InvalidArgumentError
 *  \li dds::core::UnsupportedError
 *  \li dds::core::NotAllowedBySecError
 *
 * Operations that throw other exceptions will document them explicitly.
 *
 * As a general rule constructors may only throw dds::core::Error.
 * Destructors never throw, even in case of error.
 *
 * Note that any operation can throw C++ standard exceptions such as \p
 * std::bad_alloc.
 *  
 * @section Catching_exceptions Catching exceptions
 *
 * The class dds::core::Exception is the abstract base class for all DDS
 * exceptions. All concrete exceptions inherit also from subclasses
 * of \p std::exception, so when you need to catch an exception you have
 * flexibility on the level of detail you need. For example, if you are setting
 * the DomainParticipant QoS:
 *
 * \code
 * try {
 *     my_participant.qos(my_participant_qos);
 * } catch (const dds::core::InconsistentPolicyError& ipe) {
 *     // catch a specific exception (documented in DomainParticipant::qos())
 * } catch (const std::exception& ex) {
 *     // catch any other exception here, including other DDS exceptions
 * }
 * \endcode
 *
 *
 * @{ 
 */

/**
* @brief The abstract base class for all of the DDS exceptions which may be 
* thrown by the API. 
*/
class OMG_DDS_API Exception {
protected:
    Exception();
public:
    virtual ~Exception() throw ();

public:
    /**
     * @brief Get a description of the error
     */
    virtual const char* what() const throw () = 0;
};

/**
 * @brief A generic, unspecified Error
 *
 * Inherits also from \p std::exception
 */
class OMG_DDS_API Error: public Exception, public std::exception {
public:
    /**
     * @brief Create an Error exception with no message. 
     */
    Error();
    // Spec error: missing ctor with message
    /**
     * @brief Create an Error exception with a message
     * 
     * @param msg The message to create the Error with. 
     */
    explicit Error(const std::string& msg);

    Error(const Error& src);

    virtual ~Error() throw ();

    /**
     * @brief Access the message contained in this Error exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();

private:
    // The message to be returned by what()
    std::string message_;
};

/**
 * @brief Indicates that an object has been closed.
 *
 * Inherits also from \p std::logic_error
 *
 * @see \ref DDSEntityExampleModule_teardown
 */
class OMG_DDS_API AlreadyClosedError: public Exception, public std::logic_error {
public:
    explicit AlreadyClosedError(const std::string& msg);
    AlreadyClosedError(const AlreadyClosedError& src);
    virtual ~AlreadyClosedError() throw ();

    /**
     * @brief Access the message contained in this AlreadyClosedError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

/**
 * @brief Indicates that an operation was called under improper circumstances.
 *
 * Inherits also from \p std::logic_error
 *  
 * @details \dref_details_ReturnCode_t_RETCODE_ILLEGAL_OPERATION
 */
class OMG_DDS_API IllegalOperationError: public Exception, public std::logic_error {
public:
    explicit IllegalOperationError(const std::string& msg);
    IllegalOperationError(const IllegalOperationError& src);
    virtual ~IllegalOperationError() throw ();

    /**
     * @brief Access the message contained in this IllegalOperationError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

/**
 * @brief Indicates that an operation on the DDS API fails because the security
 * plugins do not allow it.
 *
 * Inherits also from \p std::logic_error
 *
 * @details \dref_details_ReturnCode_t_RETCODE_NOT_ALLOWED_BY_SEC
 */
class OMG_DDS_API NotAllowedBySecError: public Exception, public std::logic_error {
public:
    explicit NotAllowedBySecError(const std::string& msg);
    NotAllowedBySecError(const NotAllowedBySecError& src);
    virtual ~NotAllowedBySecError() throw ();

    /**
     * @brief Access the message contained in this NotAllowedBySecError
     * exception.
     *
     * @return The message.
     */
    virtual const char* what() const throw ();
};

/**
 * @brief Indicates that the application attempted to modify an immutable
 * QoS policy.
 *
 * Inherits also from \p std::logic_error
 */
class OMG_DDS_API ImmutablePolicyError: public Exception, public std::logic_error {
public:
    explicit ImmutablePolicyError(const std::string& msg);
    ImmutablePolicyError(const ImmutablePolicyError& src);
    virtual ~ImmutablePolicyError() throw ();
    
    /**
     * @brief Access the message contained in this ImmutablePolicyError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

/**
 * @brief Indicates that the application specified
 * a set of QoS policies that are not consistent with each other
 *
 * Inherits also from \p std::logic_error
 */
class OMG_DDS_API InconsistentPolicyError: public Exception, public std::logic_error {
public:
    explicit InconsistentPolicyError(const std::string& msg);
    InconsistentPolicyError(const InconsistentPolicyError& src);
    virtual ~InconsistentPolicyError() throw ();

    /**
     * @brief Access the message contained in this NotEnabledError exception.
     *
     * @return The message.
     */
    virtual const char* what() const throw ();
};

/**
 * @brief Indicates that the application passed an illegal parameter value into
 * an operation.
 *
 * Inherits also from \p std::invalid_argument
 */
class OMG_DDS_API InvalidArgumentError: public Exception, public std::invalid_argument {
public:
    explicit InvalidArgumentError(const std::string& msg);
    InvalidArgumentError(const InvalidArgumentError& src);
    virtual ~InvalidArgumentError() throw ();

    /**
     * @brief Access the message contained in this InvalidArgumentError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

/**
 * @brief A NotEnabledError is thrown when an operation is invoked on a 
 * dds::core::Entity that is not yet enabled
 *
 * Inherits also from \p std::logic_error
 */
class OMG_DDS_API NotEnabledError: public Exception, public std::logic_error {
public:
    explicit NotEnabledError(const std::string& msg);
    NotEnabledError(const NotEnabledError& src);
    virtual ~NotEnabledError() throw ();

    /**
     * @brief Access the message contained in this NotEnabledError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

/**
 * @brief Indicates that \ndds ran out of the resources
 * needed to complete the operation.
 *
 * Inherits also from \p std::runtime_error
 */
class OMG_DDS_API OutOfResourcesError: public Exception, public std::runtime_error {
public:
    explicit OutOfResourcesError(const std::string& msg);
    OutOfResourcesError(const OutOfResourcesError& src);
    virtual ~OutOfResourcesError() throw ();

    /**
     * @brief Access the message contained in this OutOfResourcesError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

/**
 * @brief A PreconditionNotMetError is thrown when a pre-condition for the 
 * operation was not met. 
 *
 * Inherits also from \p std::logic_error
 *  
 * @details \dref_details_ReturnCode_t_RETCODE_PRECONDITION_NOT_MET
 */
class OMG_DDS_API PreconditionNotMetError: public Exception, public std::logic_error {
public:
    explicit PreconditionNotMetError(const std::string& msg);
    PreconditionNotMetError(const PreconditionNotMetError& src);
    virtual ~PreconditionNotMetError() throw ();

    /**
     * @brief Access the message contained in this PreconditionNotMetError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();

};

/**
 * @brief Indicates that an operation has timed out
 *
 * Inherits also from \p std::runtime_error
 */
class OMG_DDS_API TimeoutError: public Exception, public std::runtime_error {
public:
    explicit TimeoutError(const std::string& msg);
    TimeoutError(const TimeoutError& src);
    virtual ~TimeoutError() throw ();

    /**
     * @brief Access the message contained in this TimeoutError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

/**
 * @brief Indicates that the application used an unsupported operation.
 *
 * Inherits also from \p std::logic_error
 *
 * Only unsupported operations can throw this exception.
 */
class OMG_DDS_API UnsupportedError: public Exception, public std::logic_error {
public:
    explicit UnsupportedError(const std::string& msg);
    UnsupportedError(const UnsupportedError& src);
    virtual ~UnsupportedError() throw ();

public:
    /**
     * @brief Access the message contained in this UnsupportedError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

/**
 * @brief Indicates that a dds::core::Entity downcast was incorrect.
 *
 * Inherits also from \p std::runtime_error
 *
 * @see dds::core::polymorphic_cast
 * @see dds::pub::AnyDataWriter::get()
 */
class OMG_DDS_API InvalidDowncastError: public Exception, public std::runtime_error {
public:
    explicit InvalidDowncastError(const std::string& msg);
    InvalidDowncastError(const InvalidDowncastError& src);
    virtual ~InvalidDowncastError() throw ();

    /**
     * @brief Access the message contained in this InvalidDowncastError exception. 
     * 
     * @return The message. 
     */
    virtual const char* what() const throw ();
};

// Currently unused
class OMG_DDS_API NullReferenceError: public Exception, public std::runtime_error {
public:
    explicit NullReferenceError(const std::string& msg);
    NullReferenceError(const NullReferenceError& src);
    virtual ~NullReferenceError() throw ();

    virtual const char* what() const throw ();
};

// Currently unused
class OMG_DDS_API InvalidDataError: public Exception, public std::logic_error {
public:
    explicit InvalidDataError(const std::string& msg);
    InvalidDataError(const InvalidDataError& src);
    virtual ~InvalidDataError() throw ();

    virtual const char* what() const throw ();
};

/** @} */

}}

#endif /* OMG_DDS_CORE_EXCEPTION_HPP_ */
