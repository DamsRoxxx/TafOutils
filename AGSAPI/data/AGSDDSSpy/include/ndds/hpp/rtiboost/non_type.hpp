// -------------------------------------
//
//           (C) Copyright Gennaro Prota 2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// ------------------------------------------------------

#ifndef RTIBOOST_NON_TYPE_HPP_GP_20030417
#define RTIBOOST_NON_TYPE_HPP_GP_20030417


namespace rtiboost {

  // Just a simple "envelope" for non-type template parameters. Useful
  // to work around some MSVC deficiencies.

 template <typename T, T n>
 struct non_type { };


}


#endif // include guard
