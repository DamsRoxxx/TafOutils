/*
Copyright Rene Rivera 2005, 2008-2013
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_VERSION_NUMBER_H
#define RTIBOOST_PREDEF_VERSION_NUMBER_H

/*`
[heading `RTIBOOST_VERSION_NUMBER`]

``
RTIBOOST_VERSION_NUMBER(major,minor,patch)
``

Defines standard version numbers, with these properties:

* Decimal base whole numbers in the range \[0,1000000000).
  The number range is designed to allow for a (2,2,5) triplet.
  Which fits within a 32 bit value.
* The `major` number can be in the \[0,99\] range.
* The `minor` number can be in the \[0,99\] range.
* The `patch` number can be in the \[0,99999\] range.
* Values can be specified in any base. As the defined value
  is an constant expression.
* Value can be directly used in both preprocessor and compiler
  expressions for comparison to other similarly defined values.
* The implementation enforces the individual ranges for the
  major, minor, and patch numbers. And values over the ranges
  are truncated (modulo).

*/
#define RTIBOOST_VERSION_NUMBER(major,minor,patch) \
    ( (((major)%100)*10000000) + (((minor)%100)*100000) + ((patch)%100000) )

#define RTIBOOST_VERSION_NUMBER_MAX \
    RTIBOOST_VERSION_NUMBER(99,99,99999)

#define RTIBOOST_VERSION_NUMBER_ZERO \
    RTIBOOST_VERSION_NUMBER(0,0,0)

#define RTIBOOST_VERSION_NUMBER_MIN \
    RTIBOOST_VERSION_NUMBER(0,0,1)

#define RTIBOOST_VERSION_NUMBER_AVAILABLE \
    RTIBOOST_VERSION_NUMBER_MIN

#define RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE \
    RTIBOOST_VERSION_NUMBER_ZERO

#endif
