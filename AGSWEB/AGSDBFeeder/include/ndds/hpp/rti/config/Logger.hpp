/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_UTIL_LOGGER_HPP_
#define RTI_UTIL_LOGGER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "ndds/ndds_config_c.h"

#include <dds/core/LengthUnlimited.hpp>
#include <dds/core/SafeEnumeration.hpp>

namespace rti { 

/**
 * @brief @extension Contains configuration utilities such as logging.
 */
namespace config {

/** 
 * @ingroup NDDSConfigModule
 * @brief The definition of the dds::core::safe_enum Verbosity
 */
struct Verbosity_def {

    typedef NDDS_Config_LogVerbosity native_type;

    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /** \dref_LogVerbosity_NDDS_CONFIG_LOG_VERBOSITY_SILENT */
        SILENT = RTI_LOG_BIT_SILENCE,

        /** \dref_LogVerbosity_NDDS_CONFIG_LOG_VERBOSITY_ERROR */
        EXCEPTION = RTI_LOG_BIT_EXCEPTION,

        /** \dref_LogVerbosity_NDDS_CONFIG_LOG_VERBOSITY_WARNING */
        WARNING = EXCEPTION | RTI_LOG_BIT_WARN,

        /** \dref_LogVerbosity_NDDS_CONFIG_LOG_VERBOSITY_STATUS_LOCAL */
        STATUS_LOCAL = WARNING | RTI_LOG_BIT_LOCAL,

        /** \dref_LogVerbosity_NDDS_CONFIG_LOG_VERBOSITY_STATUS_REMOTE */
        STATUS_REMOTE = STATUS_LOCAL | RTI_LOG_BIT_REMOTE,

        /** \dref_LogVerbosity_NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL */
        STATUS_ALL = STATUS_REMOTE | RTI_LOG_BIT_PERIODIC,
        
        // For backward compatibilty:
        ERRORY = EXCEPTION
    };
};

/**
 * @ingroup NDDSConfigModule 
 * @brief The verbosities at which \ndds diagnostic information is logged. 
 *
 * @see Verbosity_def
 */
typedef dds::core::safe_enum<Verbosity_def> Verbosity;

/** 
 * @ingroup NDDSConfigModule
 * @brief The definition of the dds::core::safe_enum LogCategory
 */
struct LogCategory_def {

    typedef NDDS_Config_LogCategory native_type;

    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /** \dref_LogCategory_NDDS_CONFIG_LOG_CATEGORY_PLATFORM
         */
        PLATFORM = NDDS_CONFIG_LOG_CATEGORY_PLATFORM,

        /** \dref_LogCategory_NDDS_CONFIG_LOG_CATEGORY_COMMUNICATION
         */
        COMMUNICATION = NDDS_CONFIG_LOG_CATEGORY_COMMUNICATION,

        /** \dref_LogCategory_NDDS_CONFIG_LOG_CATEGORY_DATABASE
         */
        DATABASE = NDDS_CONFIG_LOG_CATEGORY_DATABASE,

        /** \dref_LogCategory_NDDS_CONFIG_LOG_CATEGORY_ENTITIES
         */
        ENTITIES = NDDS_CONFIG_LOG_CATEGORY_ENTITIES,

        /** \dref_LogCategory_NDDS_CONFIG_LOG_CATEGORY_API
         */
        API = NDDS_CONFIG_LOG_CATEGORY_API,

        /** \dref_LogCategory_NDDS_CONFIG_LOG_CATEGORY_ALL
         */
        ALL_CATEGORIES = NDDS_CONFIG_LOG_CATEGORY_ALL
    };
};

/** 
 * @ingroup NDDSConfigModule 
 * @brief Categories of logged messages. 
 * @see @ref LogCategory_def   
 */
typedef dds::core::safe_enum<LogCategory_def> LogCategory;

/** 
 * @ingroup NDDSConfigModule
 * @brief The definition of the dds::core::safe_enum PrintFormat
 */
struct PrintFormat_def {

    typedef NDDS_Config_LogPrintFormat native_type;

    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_NUMBER
         */
        BIT_NUMBER = NDDS_CONFIG_LOG_PRINT_BIT_NUMBER,

        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_MESSAGE
         */
        BIT_MESSAGE = NDDS_CONFIG_LOG_PRINT_BIT_MESSAGE,

        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_LOCATION_MODULE
         */
        BIT_LOCATION_MODULE = NDDS_CONFIG_LOG_PRINT_BIT_LOCATION_MODULE,

        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_LOCATION_FILELINE
         */
        BIT_LOCATION_FILELINE = NDDS_CONFIG_LOG_PRINT_BIT_LOCATION_FILELINE,

        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_LOCATION_METHOD
         */
        BIT_LOCATION_METHOD = NDDS_CONFIG_LOG_PRINT_BIT_LOCATION_METHOD,

        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_TIMESTAMP
         */
        BIT_TIMESTAMP = NDDS_CONFIG_LOG_PRINT_BIT_TIMESTAMP,

        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_THREAD_ID
         */
        BIT_THREAD_ID = NDDS_CONFIG_LOG_PRINT_BIT_THREAD_ID,

        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_CONTEXT
         */
        BIT_CONTEXT = NDDS_CONFIG_LOG_PRINT_BIT_CONTEXT,

        /*i \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_BIT_TWO_LINES
         */
        BIT_TWO_LINES = NDDS_CONFIG_LOG_PRINT_BIT_TWO_LINES,

        /** \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_FORMAT_DEFAULT
         */
        DEFAULT = NDDS_CONFIG_LOG_PRINT_FORMAT_DEFAULT,

        /** \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_FORMAT_TIMESTAMPED
         */
        TIMESTAMPED = NDDS_CONFIG_LOG_PRINT_FORMAT_TIMESTAMPED,

        /** \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_FORMAT_VERBOSE
         */
        VERBOSE = NDDS_CONFIG_LOG_PRINT_FORMAT_VERBOSE,

        /** \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_FORMAT_VERBOSE_TIMESTAMPED
         */
        VERBOSE_TIMESTAMPED = NDDS_CONFIG_LOG_PRINT_FORMAT_VERBOSE_TIMESTAMPED,

        /** \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_FORMAT_DEBUG
         */
        DEBUG = NDDS_CONFIG_LOG_PRINT_FORMAT_DEBUG,

        /** \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_FORMAT_MINIMAL
         */
        MINIMAL = NDDS_CONFIG_LOG_PRINT_FORMAT_MINIMAL,

        /** \dref_LogPrintFormat_NDDS_CONFIG_LOG_PRINT_FORMAT_MAXIMAL
         */
        MAXIMAL = NDDS_CONFIG_LOG_PRINT_FORMAT_MAXIMAL

    };
};

/** 
 * @ingroup NDDSConfigModule 
 * @brief The format used to output RTI Connext diagnostic information.
 * @see @ref PrintFormat_def   
 */
typedef dds::core::safe_enum<PrintFormat_def> PrintFormat;

struct LoggerMode_def {

    typedef NDDS_Config_LoggerMode native_type;

    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /*i \dref_LoggerMode_NDDS_CONFIG_LOGGER_MODE_DEFAULT,
         */
        DEFAULT = NDDS_CONFIG_LOGGER_MODE_DEFAULT,

        /*i \dref_LoggerMode_NDDS_CONFIG_LOGGER_MODE_DISABLE_STANDARD_DEVICES
         */
        DISABLE_STANDARD_DEVICES = NDDS_CONFIG_LOGGER_MODE_DISABLE_STANDARD_DEVICES,

        /*i \dref_LoggerMode_NDDS_CONFIG_LOGGER_MODE_DISABLE_ADVANCED_LOGGING
         */
        DISABLE_ADVANCED_LOGGING = NDDS_CONFIG_LOGGER_MODE_DISABLE_ADVANCED_LOGGING

    };
};

typedef dds::core::safe_enum<LoggerMode_def> LoggerMode;

/** 
 * @ingroup NDDSConfigModule 
 * @brief The singleton type used to configure RTI Connext logging.
 */
class OMG_DDS_API Logger {
  public:
    /** \dref_Logger_get_instance
     */
    static Logger& instance();

    /** \dref_Logger_get_verbosity
     */
    Verbosity verbosity();

    /** \dref_Logger_get_verbosity_by_category
     */
    Verbosity verbosity_by_category(LogCategory category);

    /** \dref_Logger_set_verbosity
     */
    void verbosity(Verbosity verbosity);

    /** \dref_Logger_set_verbosity_by_category
     */
    void verbosity_by_category(LogCategory category, Verbosity verbosity);

    /** \dref_Logger_get_output_file
     */
    FILE* output_file();

    /** \dref_Logger_set_output_file
     */
    void output_file(FILE* out);

    /** \dref_Logger_set_output_file_name
     */
    void output_file(const char * file_name);

    /** \dref_Logger_set_output_file_name
     */
    void output_file_set(
            const char * file_preffix,
            const char * file_suffix,
            int max_bytes,
            int max_files = dds::core::LENGTH_UNLIMITED);

    /** \dref_Logger_get_print_format
     */
    PrintFormat print_format();

    /** \dref_Logger_set_print_format
     */
    void print_format(PrintFormat print_format);

    /*i \dref_Logger_set_mode
     */
    void mode(LoggerMode mode);

    virtual ~Logger();

private:
    Logger(); // Constructor is private: this class is a singleton

    // Disable copy
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    NDDS_Config_Logger * native_logger_; // implementation
};

/** 
 * @ingroup NDDSConfigModule 
 * @brief Changes the logger verbosity temporarily during the scope of a variable.
 *
 * RAII utility to modify logging verbosity during the scope of a variable and
 * restore it to the previous value upon destruction.
 */
class ScopedLoggerVerbosity {
public:
    /**
     * Sets the verbosity of Logger::instance()
     */
    ScopedLoggerVerbosity(Verbosity verbosity)
        : previous_verbosity_ (Logger::instance().verbosity())
    {
        Logger::instance().verbosity(verbosity);
    }

    /**
     * Restores the verbosity of Logger::instance() to the value before the
     * construction of this object.
     */
    ~ScopedLoggerVerbosity()
    {
        Logger::instance().verbosity(previous_verbosity_);
    }

private:
    Verbosity previous_verbosity_;
};

} } // namespace rti::config

#endif // RTI_UTIL_LOGGER_HPP_
