/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_test.h    generated by: makeheader    Fri Feb 16 13:51:43 2018
 *
 *		built from:	test.ifc
 */

#ifndef pres_test_h
#define pres_test_h


  #ifndef test_setting_h
    #include "test/test_setting.h"
  #endif
  #ifndef clock_interface_h
    #include "clock/clock_interface.h"
  #endif
  #ifndef writer_history_odbc_h
    #include "writer_history/writer_history_odbc.h"
  #endif
#ifdef __cplusplus
    extern "C" {
#endif


#define NDDS_PRES_ODBC_PLUGIN_DSN_MAX_LENGTH 100
#define NDDS_PRES_ODBC_PLUGIN_LIBNAME_MAX_LENGTH 255
#define NDDS_PRES_ODBC_PLUGIN_MAX_TEST_DATABASES 10

struct RTIPRESTestOdbcDatabaseInfo {
    char DSN[NDDS_PRES_ODBC_PLUGIN_DSN_MAX_LENGTH];
    char odbcDatabaseLib[NDDS_PRES_ODBC_PLUGIN_LIBNAME_MAX_LENGTH];
};

struct RTIPRESTestSetting {
    struct RTITestSetting parent;
    int numSessions;
    int numOdbcDatabases;
    int odbcDatabaseIndex;
    struct RTIPRESTestOdbcDatabaseInfo 
        testOdbcDatabaseInfo[NDDS_PRES_ODBC_PLUGIN_MAX_TEST_DATABASES]; 
};


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_test_h */
