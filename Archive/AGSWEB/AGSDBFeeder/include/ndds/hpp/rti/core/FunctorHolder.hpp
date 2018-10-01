/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,22jan13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_FUNCTOR_HOLDER_HPP_
#define RTI_DDS_CORE_FUNCTOR_HOLDER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>

namespace rti { namespace core {

class FunctorHolder {
public:
    virtual ~FunctorHolder()
    {
    }

    virtual void invoke() = 0;
};

template <typename Functor>
class VoidFunctorHolder : public FunctorHolder {
public:
  VoidFunctorHolder(const Functor& func)
     : func_(func) { }

  virtual ~VoidFunctorHolder() { }

public:
  virtual void invoke() {
     func_();
  }
private:
  Functor func_;
};

template <typename Functor, typename ARG1>
class OneArgFunctorHolder : public FunctorHolder {
public:
  OneArgFunctorHolder(const Functor& func, const ARG1& arg1)
  : func_(func), arg1_(arg1) { }

  virtual ~OneArgFunctorHolder() { }

public:
  virtual void invoke() {
     func_(arg1_);
  }
private:
  Functor func_;
  ARG1 arg1_;
};

template <typename Functor, typename ARG1, typename ARG2>
class TwoArgFunctorHolder : public FunctorHolder {
public:
  TwoArgFunctorHolder(const Functor& func,
                      const ARG1& arg1,
                      const ARG2& arg2)
  :  func_(func),
     arg1_(arg1),
     arg2_(arg2)
  { }

  virtual ~TwoArgFunctorHolder() { }

public:
  virtual void invoke() {
     func_(arg1_, arg2_);
  }
private:
  Functor func_;
  ARG1 arg1_;
  ARG2 arg2_;
};


} } // namespace rti::core

#endif // RTI_DDS_CORE_FUNCTOR_HOLDER_HPP_

