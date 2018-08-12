/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)ndds_config_cpp.h    generated by: makeheader    Fri Feb 16 13:52:08 2018
 *
 *		built from:	ndds_config_cpp.ifcxx
 */

#ifndef ndds_config_cpp_h
#define ndds_config_cpp_h


#ifndef dds_cpp_dll_h
  #include "dds_cpp/dds_cpp_dll.h"
#endif
#ifndef ndds_config_c_h
  #include "ndds/ndds_config_c.h"
#endif


#define NDDS_Config_Version_MAX_STRING_LENGTH_I   512

class DDSCPPDllExport NDDSConfigVersion {
  public:
    /*e \dref_Version_t_get_instance */
    static const NDDSConfigVersion& get_instance();

    /*e \dref_Version_t_get_product_version */
    const DDS_ProductVersion_t& get_product_version() const;

    /*e \dref_Version_t_get_cpp_api_version */
    const NDDS_Config_LibraryVersion_t& get_cpp_api_version() const;

    /*e \dref_Version_t_get_c_api_version */
    const NDDS_Config_LibraryVersion_t& get_c_api_version() const;

    /*e \dref_Version_t_get_core_version */
    const NDDS_Config_LibraryVersion_t& get_core_version() const;

    /*e \dref_Version_t_to_string */
    const char* to_string() const;

    static const char* get_core_build_number_string();
    static const char* get_C_build_number_string();
    static const char* get_CPP_build_number_string();

    virtual ~NDDSConfigVersion();

  private:
    NDDSConfigVersion();
    void build_version_string();

    static NDDSConfigVersion* _singleton;
    static const char *const LIBRARY_VERSION_STRING;

    NDDS_Config_LibraryVersion_t _libraryVersion;
    char _stringified[NDDS_Config_Version_MAX_STRING_LENGTH_I];
};

class DDSCPPDllExport NDDSConfigLoggerDevice {
  protected:
    /*i
     * Don't instantiate NDDSConfigLoggerDevice directly; instantiate an
     * application-specific subclass.
     */
    NDDSConfigLoggerDevice();
    virtual ~NDDSConfigLoggerDevice();
  public:

    /*e \dref_LoggerDevice_write
     */
    virtual void write(const NDDS_Config_LogMessage *message) = 0;

    /*e \dref_LoggerDevice_close
     */
    virtual void close();
};

class DDSCPPDllExport NDDSConfigLogger {
  public:
    /*e \dref_Logger_get_instance
     */
    static NDDSConfigLogger* get_instance();
    
    /*e \dref_Logger_finalize_instance
     */
    static void finalize_instance();
    
    /*e \dref_Logger_get_verbosity
     */
    NDDS_Config_LogVerbosity get_verbosity();
    
    /*e \dref_Logger_get_verbosity_by_category
     */
    NDDS_Config_LogVerbosity get_verbosity_by_category(
        NDDS_Config_LogCategory category);
    
    /*e \dref_Logger_set_verbosity
     */
    void set_verbosity(NDDS_Config_LogVerbosity verbosity);
    
    /*e \dref_Logger_set_verbosity_by_category
     */
    void set_verbosity_by_category(NDDS_Config_LogCategory category,
        NDDS_Config_LogVerbosity verbosity);
    
    /*e \dref_Logger_get_output_file
     */
    FILE* get_output_file();
    
    /*e \dref_Logger_set_output_file
     */
    bool set_output_file(FILE* out);

    /*e \dref_Logger_set_output_file_set
     */
    bool set_output_file_set(
            const char *file_prefix,
            const char *file_suffix,
            int max_capacity,
            int max_files);

    /*e \dref_Logger_get_output_device
     */
    NDDSConfigLoggerDevice *get_output_device();

    /*e \dref_Logger_set_output_device
     */
    bool set_output_device(NDDSConfigLoggerDevice *device);

    /*e \dref_Logger_get_print_format
     */
    NDDS_Config_LogPrintFormat get_print_format();

    /*e \dref_Logger_set_print_format
     */
    bool set_print_format(NDDS_Config_LogPrintFormat print_format);

    /*i \dref_Logger_set_mode
     */
    bool set_mode(NDDS_Config_LoggerMode mode);
    
    virtual ~NDDSConfigLogger();

  private:
    NDDSConfigLogger(NDDS_Config_Logger* logger);
    
    static NDDSConfigLogger* _singleton;
    NDDS_Config_Logger* _cLogger;
    NDDSConfigLoggerDevice* _cppDevice;
    struct NDDS_Config_LoggerDevice* _implDevice;
};

#endif /* ndds_config_cpp_h */
