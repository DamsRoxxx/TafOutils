// (C) Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPE_DWA20010120_HPP
# define RTIBOOST_TYPE_DWA20010120_HPP

namespace rtiboost {

  // Just a simple "type envelope". Useful in various contexts, mostly to work
  // around some MSVC deficiencies.
  template <class T>
  struct type {};

}

#endif // RTIBOOST_TYPE_DWA20010120_HPP
