/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)writer_history_test.h    generated by: makeheader    Fri Feb 16 13:51:41 2018
 *
 *		built from:	test.ifc
 */

#ifndef writer_history_test_h
#define writer_history_test_h


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


#define NDDS_WRITERHISTORY_ODBC_PLUGIN_MAX_TEST_DATABASES 10

struct RTIWriterHistoryTestOdbcDatabaseInfo {
    char DSN[NDDS_WRITERHISTORY_ODBC_PLUGIN_DSN_MAX_LENGTH];
    char odbcDatabaseLib[NDDS_WRITERHISTORY_ODBC_PLUGIN_LIBNAME_MAX_LENGTH];
};

struct RTIWriterHistoryTestSetting {
    struct RTITestSetting parent;
    int numOdbcDatabases;
    int odbcDatabaseIndex;
    struct RTIWriterHistoryTestOdbcDatabaseInfo 
        testOdbcDatabaseInfo[NDDS_WRITERHISTORY_ODBC_PLUGIN_MAX_TEST_DATABASES];       
};


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* writer_history_test_h */