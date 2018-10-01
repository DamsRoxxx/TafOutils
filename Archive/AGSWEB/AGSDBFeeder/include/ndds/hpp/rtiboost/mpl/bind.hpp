
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_BIND_HPP_INCLUDED
#define RTIBOOST_MPL_BIND_HPP_INCLUDED

// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   include <rtiboost/mpl/bind_fwd.hpp>
#   include <rtiboost/mpl/placeholders.hpp>
#   include <rtiboost/mpl/next.hpp>
#   include <rtiboost/mpl/protect.hpp>
#   include <rtiboost/mpl/apply_wrap.hpp>
#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/na.hpp>
#   include <rtiboost/mpl/aux_/arity_spec.hpp>
#   include <rtiboost/mpl/aux_/type_wrapper.hpp>
#   include <rtiboost/mpl/aux_/yes_no.hpp>
#   if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <rtiboost/type_traits/is_reference.hpp>
#   endif 
#endif

#include <rtiboost/mpl/aux_/config/bind.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   if defined(RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)
#       define RTIBOOST_MPL_PREPROCESSED_HEADER basic_bind.hpp
#   else
#       define RTIBOOST_MPL_PREPROCESSED_HEADER bind.hpp
#   endif
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/def_params_tail.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/ext_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/repeat.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/add.hpp>
#   include <rtiboost/mpl/aux_/config/dmc_ambiguous_ctps.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/config/ttp.hpp>
#   include <rtiboost/mpl/aux_/config/dtp.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>

#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/cat.hpp>
#   include <rtiboost/preprocessor/inc.hpp>

namespace rtiboost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define RTIBOOST_AUX778076_APPLY \
    RTIBOOST_PP_CAT(apply_wrap,RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY) \
    /**/

#   if defined(RTIBOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)
#       define RTIBOOST_AUX778076_DMC_PARAM() , int dummy_
#   else
#       define RTIBOOST_AUX778076_DMC_PARAM()
#   endif

#   define RTIBOOST_AUX778076_BIND_PARAMS(param) \
    RTIBOOST_MPL_PP_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define RTIBOOST_AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    RTIBOOST_MPL_PP_DEFAULT_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define RTIBOOST_AUX778076_BIND_N_PARAMS(n, param) \
    RTIBOOST_PP_COMMA_IF(n) RTIBOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define RTIBOOST_AUX778076_BIND_N_SPEC_PARAMS(n, param, def) \
    RTIBOOST_PP_COMMA_IF(n) \
    RTIBOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
    /**/

#if !defined(RTIBOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define RTIBOOST_AUX778076_BIND_NESTED_DEFAULT_PARAMS(param, value) \
    RTIBOOST_AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    /**/
#else
#   define RTIBOOST_AUX778076_BIND_NESTED_DEFAULT_PARAMS(param, value) \
    RTIBOOST_AUX778076_BIND_PARAMS(param) \
    /**/
#endif

namespace aux {

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename T, RTIBOOST_AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg
{
    typedef T type;
};

#   if !defined(RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

template<
      typename T
    , typename Arg
    >
struct replace_unnamed_arg
{
    typedef Arg next;
    typedef T type;
};

template<
      typename Arg
    >
struct replace_unnamed_arg< arg<-1>,Arg >
{
    typedef typename Arg::next next;
    typedef Arg type;
};

#   endif // RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

template<
      RTIBOOST_MPL_AUX_NTTP_DECL(int, N), RTIBOOST_AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg< arg<N>,RTIBOOST_AUX778076_BIND_PARAMS(U) >
{
    typedef typename RTIBOOST_AUX778076_APPLY<mpl::arg<N>, RTIBOOST_AUX778076_BIND_PARAMS(U)>::type type;
};

#if !defined(RTIBOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, RTIBOOST_AUX778076_BIND_PARAMS(typename T), RTIBOOST_AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg< bind<F,RTIBOOST_AUX778076_BIND_PARAMS(T)>,RTIBOOST_AUX778076_BIND_PARAMS(U) >
{
    typedef bind<F,RTIBOOST_AUX778076_BIND_PARAMS(T)> f_;
    typedef typename RTIBOOST_AUX778076_APPLY<f_, RTIBOOST_AUX778076_BIND_PARAMS(U)>::type type;
};
#endif

#else // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// agurt, 15/jan/02: it's not a intended to be used as a function class, and 
// MSVC6.5 has problems with 'apply' name here (the code compiles, but doesn't
// work), so I went with the 'result_' here, and in all other similar cases
template< bool >
struct resolve_arg_impl
{
    template< typename T, RTIBOOST_AUX778076_BIND_PARAMS(typename U) > struct result_
    {
        typedef T type;
    };
};

template<> 
struct resolve_arg_impl<true>
{
    template< typename T, RTIBOOST_AUX778076_BIND_PARAMS(typename U) > struct result_
    {
        typedef typename RTIBOOST_AUX778076_APPLY<
              T
            , RTIBOOST_AUX778076_BIND_PARAMS(U)
            >::type type;
    };
};

// for 'resolve_bind_arg'
template< typename T > struct is_bind_template;

template< 
      typename T, RTIBOOST_AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg
    : resolve_arg_impl< is_bind_template<T>::value >
            ::template result_< T,RTIBOOST_AUX778076_BIND_PARAMS(U) >
{
};

#   if !defined(RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

template< typename T > 
struct replace_unnamed_arg_impl
{
    template< typename Arg > struct result_
    {
        typedef Arg next;
        typedef T type;
    };
};

template<> 
struct replace_unnamed_arg_impl< arg<-1> >
{
    template< typename Arg > struct result_
    {
        typedef typename next<Arg>::type next;
        typedef Arg type;
    };
};

template< typename T, typename Arg > 
struct replace_unnamed_arg
    : replace_unnamed_arg_impl<T>::template result_<Arg>
{
};

#   endif // RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

// agurt, 10/mar/02: the forward declaration has to appear before any of
// 'is_bind_helper' overloads, otherwise MSVC6.5 issues an ICE on it
template< RTIBOOST_MPL_AUX_NTTP_DECL(int, arity_) > struct bind_chooser;

aux::no_tag is_bind_helper(...);
template< typename T > aux::no_tag is_bind_helper(protect<T>*);

// overload for "main" form
// agurt, 15/mar/02: MSVC 6.5 fails to properly resolve the overload 
// in case if we use 'aux::type_wrapper< bind<...> >' here, and all 
// 'bind' instantiations form a complete type anyway
#if !defined(RTIBOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, RTIBOOST_AUX778076_BIND_PARAMS(typename T)
    >
aux::yes_tag is_bind_helper(bind<F,RTIBOOST_AUX778076_BIND_PARAMS(T)>*);
#endif

template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N) >
aux::yes_tag is_bind_helper(arg<N>*);

template< bool is_ref_ = true >
struct is_bind_template_impl
{
    template< typename T > struct result_
    {
        RTIBOOST_STATIC_CONSTANT(bool, value = false);
    };
};

template<>
struct is_bind_template_impl<false>
{
    template< typename T > struct result_
    {
        RTIBOOST_STATIC_CONSTANT(bool, value = 
              sizeof(aux::is_bind_helper(static_cast<T*>(0))) 
                == sizeof(aux::yes_tag)
            );
    };
};

template< typename T > struct is_bind_template
    : is_bind_template_impl< ::rtiboost::detail::is_reference_impl<T>::value >
        ::template result_<T>
{
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux


#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/bind.hpp>))
#include RTIBOOST_PP_ITERATE()

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(RTIBOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS)
/// if_/eval_if specializations
#   define RTIBOOST_AUX778076_SPEC_NAME if_
#   define RTIBOOST_PP_ITERATION_PARAMS_1 (3,(3, 3, <rtiboost/mpl/bind.hpp>))
#   include RTIBOOST_PP_ITERATE()

#if !defined(RTIBOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)
#   define RTIBOOST_AUX778076_SPEC_NAME eval_if
#   define RTIBOOST_PP_ITERATION_PARAMS_1 (3,(3, 3, <rtiboost/mpl/bind.hpp>))
#   include RTIBOOST_PP_ITERATE()
#endif
#endif

// real C++ version is already taken care of
#if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(RTIBOOST_MPL_CFG_NO_BIND_TEMPLATE)

namespace aux {
// apply_count_args
#define RTIBOOST_AUX778076_COUNT_ARGS_PREFIX bind
#define RTIBOOST_AUX778076_COUNT_ARGS_DEFAULT na
#define RTIBOOST_AUX778076_COUNT_ARGS_ARITY RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
#include <rtiboost/mpl/aux_/count_args.hpp>
}

// bind
template<
      typename F, RTIBOOST_AUX778076_BIND_PARAMS(typename T) RTIBOOST_AUX778076_DMC_PARAM()
    >
struct bind
    : aux::bind_chooser<
          aux::bind_count_args<RTIBOOST_AUX778076_BIND_PARAMS(T)>::value
        >::template result_< F,RTIBOOST_AUX778076_BIND_PARAMS(T) >::type
{
};

RTIBOOST_MPL_AUX_ARITY_SPEC(
      RTIBOOST_PP_INC(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY)
    , bind
    )

RTIBOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(
      RTIBOOST_PP_INC(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY)
    , bind
    )


#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef RTIBOOST_AUX778076_BIND_NESTED_DEFAULT_PARAMS
#   undef RTIBOOST_AUX778076_BIND_N_SPEC_PARAMS
#   undef RTIBOOST_AUX778076_BIND_N_PARAMS
#   undef RTIBOOST_AUX778076_BIND_DEFAULT_PARAMS
#   undef RTIBOOST_AUX778076_BIND_PARAMS
#   undef RTIBOOST_AUX778076_DMC_PARAM
#   undef RTIBOOST_AUX778076_APPLY

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_BIND_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// RTIBOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // RTIBOOST_PP_IS_ITERATING
#if RTIBOOST_PP_ITERATION_DEPTH() == 1

#   define i_ RTIBOOST_PP_FRAME_ITERATION(1)

#if defined(RTIBOOST_AUX778076_SPEC_NAME)

// lazy metafunction specialization
template< template< RTIBOOST_MPL_PP_PARAMS(i_, typename T) > class F, typename Tag >
struct RTIBOOST_PP_CAT(quote,i_);

template< RTIBOOST_MPL_PP_PARAMS(i_, typename T) > struct RTIBOOST_AUX778076_SPEC_NAME;

template<
      typename Tag RTIBOOST_AUX778076_BIND_N_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(bind,i_)< 
      RTIBOOST_PP_CAT(quote,i_)<RTIBOOST_AUX778076_SPEC_NAME,Tag>
    RTIBOOST_AUX778076_BIND_N_PARAMS(i_,T)
    >
{
    template<
          RTIBOOST_AUX778076_BIND_NESTED_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
     private:
        typedef mpl::arg<1> n1;
#       define RTIBOOST_PP_ITERATION_PARAMS_2 (3,(1, i_, <rtiboost/mpl/bind.hpp>))
#       include RTIBOOST_PP_ITERATE()

        typedef typename RTIBOOST_AUX778076_SPEC_NAME<
              typename t1::type
            , RTIBOOST_MPL_PP_EXT_PARAMS(2, RTIBOOST_PP_INC(i_), t)
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

#undef RTIBOOST_AUX778076_SPEC_NAME

#else // RTIBOOST_AUX778076_SPEC_NAME

template<
      typename F RTIBOOST_AUX778076_BIND_N_PARAMS(i_, typename T) RTIBOOST_AUX778076_DMC_PARAM()
    >
struct RTIBOOST_PP_CAT(bind,i_)
{
    template<
          RTIBOOST_AUX778076_BIND_NESTED_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
     private:
#   if !defined(RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

        typedef aux::replace_unnamed_arg< F,mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg<a0,RTIBOOST_AUX778076_BIND_PARAMS(U)>::type f_;
        ///
#   else
        typedef typename aux::resolve_bind_arg<F,RTIBOOST_AUX778076_BIND_PARAMS(U)>::type f_;

#   endif // RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#   if i_ > 0
#       define RTIBOOST_PP_ITERATION_PARAMS_2 (3,(1, i_, <rtiboost/mpl/bind.hpp>))
#       include RTIBOOST_PP_ITERATE()
#   endif

     public:

#   define RTIBOOST_AUX778076_ARG(unused, i_, t) \
    RTIBOOST_PP_COMMA_IF(i_) \
    typename RTIBOOST_PP_CAT(t,RTIBOOST_PP_INC(i_))::type \
/**/

        typedef typename RTIBOOST_PP_CAT(apply_wrap,i_)<
              f_ 
            RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_ARG, t)
            >::type type;

#   undef RTIBOOST_AUX778076_ARG
    };
};

namespace aux {

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename F RTIBOOST_AUX778076_BIND_N_PARAMS(i_, typename T), RTIBOOST_AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg<
      RTIBOOST_PP_CAT(bind,i_)<F RTIBOOST_AUX778076_BIND_N_PARAMS(i_,T)>,RTIBOOST_AUX778076_BIND_PARAMS(U)
    >
{
    typedef RTIBOOST_PP_CAT(bind,i_)<F RTIBOOST_AUX778076_BIND_N_PARAMS(i_,T)> f_;
    typedef typename RTIBOOST_AUX778076_APPLY<f_, RTIBOOST_AUX778076_BIND_PARAMS(U)>::type type;
};

#else

template<
      typename F RTIBOOST_AUX778076_BIND_N_PARAMS(i_, typename T)
    >
aux::yes_tag
is_bind_helper(RTIBOOST_PP_CAT(bind,i_)<F RTIBOOST_AUX778076_BIND_N_PARAMS(i_,T)>*);

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

RTIBOOST_MPL_AUX_ARITY_SPEC(RTIBOOST_PP_INC(i_), RTIBOOST_PP_CAT(bind,i_))
RTIBOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(RTIBOOST_PP_INC(i_), RTIBOOST_PP_CAT(bind,i_))

#   if !defined(RTIBOOST_MPL_CFG_NO_BIND_TEMPLATE)
#   if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    
#if i_ == RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
/// primary template (not a specialization!)
template<
      typename F RTIBOOST_AUX778076_BIND_N_PARAMS(i_, typename T) RTIBOOST_AUX778076_DMC_PARAM()
    >
struct bind
    : RTIBOOST_PP_CAT(bind,i_)<F RTIBOOST_AUX778076_BIND_N_PARAMS(i_,T) >
{
};
#else
template<
      typename F RTIBOOST_AUX778076_BIND_N_PARAMS(i_, typename T) RTIBOOST_AUX778076_DMC_PARAM()
    >
struct bind< F RTIBOOST_AUX778076_BIND_N_SPEC_PARAMS(i_, T, na) >
    : RTIBOOST_PP_CAT(bind,i_)<F RTIBOOST_AUX778076_BIND_N_PARAMS(i_,T) >
{
};
#endif

#   else // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace aux {

template<>
struct bind_chooser<i_>
{
    template<
          typename F, RTIBOOST_AUX778076_BIND_PARAMS(typename T)
        >
    struct result_
    {
        typedef RTIBOOST_PP_CAT(bind,i_)< F RTIBOOST_AUX778076_BIND_N_PARAMS(i_,T) > type;
    };
};

} // namespace aux

#   endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // RTIBOOST_MPL_CFG_NO_BIND_TEMPLATE

#endif // RTIBOOST_AUX778076_SPEC_NAME

#   undef i_

///// iteration, depth == 2

#elif RTIBOOST_PP_ITERATION_DEPTH() == 2

#   define j_ RTIBOOST_PP_FRAME_ITERATION(2)
#   if !defined(RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

        typedef aux::replace_unnamed_arg< RTIBOOST_PP_CAT(T,j_),RTIBOOST_PP_CAT(n,j_) > RTIBOOST_PP_CAT(r,j_);
        typedef typename RTIBOOST_PP_CAT(r,j_)::type RTIBOOST_PP_CAT(a,j_);
        typedef typename RTIBOOST_PP_CAT(r,j_)::next RTIBOOST_PP_CAT(n,RTIBOOST_PP_INC(j_));
        typedef aux::resolve_bind_arg<RTIBOOST_PP_CAT(a,j_), RTIBOOST_AUX778076_BIND_PARAMS(U)> RTIBOOST_PP_CAT(t,j_);
        ///
#   else
        typedef aux::resolve_bind_arg< RTIBOOST_PP_CAT(T,j_),RTIBOOST_AUX778076_BIND_PARAMS(U)> RTIBOOST_PP_CAT(t,j_);

#   endif
#   undef j_

#endif // RTIBOOST_PP_ITERATION_DEPTH()
#endif // RTIBOOST_PP_IS_ITERATING
