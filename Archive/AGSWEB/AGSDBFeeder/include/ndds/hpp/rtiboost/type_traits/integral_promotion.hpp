// Copyright 2005 Alexander Nasonov.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_type_traits_integral_promotion_hpp_INCLUDED
#define RTIBOOST_type_traits_integral_promotion_hpp_INCLUDED

#include <rtiboost/config.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>
#include <rtiboost/type_traits/is_const.hpp>
#include <rtiboost/type_traits/is_enum.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#include <rtiboost/type_traits/remove_cv.hpp>

namespace rtiboost {

namespace type_traits { namespace detail {

// 4.5/2
template <class T> struct need_promotion : public rtiboost::is_enum<T> {};

// 4.5/1
template<> struct need_promotion<char              > : public true_type {};
template<> struct need_promotion<signed char       > : public true_type {};
template<> struct need_promotion<unsigned char     > : public true_type {};
template<> struct need_promotion<signed short int  > : public true_type {};
template<> struct need_promotion<unsigned short int> : public true_type {};


// Specializations for non-standard types.
// Type is promoted if it's smaller then int.

#define RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(T) \
    template<> struct need_promotion<T>          \
        : public integral_constant<bool, (sizeof(T) < sizeof(int))> {};

// Same set of integral types as in boost/type_traits/is_integral.hpp.
// Please, keep in sync.
#if (defined(RTIBOOST_INTEL_CXX_VERSION) && defined(_MSC_VER) && (RTIBOOST_INTEL_CXX_VERSION <= 600)) \
    || (defined(__BORLANDC__) && (__BORLANDC__ == 0x600) && (_MSC_VER < 1300))
// TODO: common macro for this #if. Or better yet, PP SEQ of non-standard types.
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(__int8          )
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(unsigned __int8 )
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(__int16         )
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(unsigned __int16)
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(__int32         )
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(unsigned __int32)
#ifdef __BORLANDC__
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(unsigned __int64)
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(         __int64)
#endif
#endif

#if defined(RTIBOOST_HAS_LONG_LONG)
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(rtiboost::ulong_long_type)
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(rtiboost::long_long_type )
#elif defined(RTIBOOST_HAS_MS_INT64)
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(unsigned __int64)
RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE(         __int64)
#endif

#undef RTIBOOST_TT_AUX_PROMOTE_NONSTANDARD_TYPE


#ifndef RTIBOOST_NO_INTRINSIC_WCHAR_T
// 4.5/2
template<> struct need_promotion<wchar_t> : public true_type {};
#endif

// 4.5/3 (integral bit-field) is not supported.

// 4.5/4
template<> struct need_promotion<bool> : public true_type {};


// Get promoted type by index and cv qualifiers.

template<int Index, int IsConst, int IsVolatile> struct promote_from_index;

#define RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(N,T)                                   \
    template<> struct promote_from_index<N,0,0> { typedef T type; };           \
    template<> struct promote_from_index<N,0,1> { typedef T volatile type; };  \
    template<> struct promote_from_index<N,1,0> { typedef T const type; };     \
    template<> struct promote_from_index<N,1,1> { typedef T const volatile type; };


RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(1, int          )
RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(2, unsigned int )
RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(3, long         )
RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(4, unsigned long)


// WARNING: integral promotions to non-standard types
// long long and __int64 are not defined by the standard.
// Additional specialisations and overloads shouldn't
// introduce ambiguity, though.

#if defined(RTIBOOST_HAS_LONG_LONG)
RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(5, rtiboost::long_long_type )
RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(6, rtiboost::ulong_long_type)
#elif defined(RTIBOOST_HAS_MS_INT64)
RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(7, __int64         )
RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX(8, unsigned __int64)
#endif

#undef RTIBOOST_TT_AUX_PROMOTE_FROM_INDEX


// Define RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER:
#if !defined(RTIBOOST_MSVC)

template<int N>
struct sized_type_for_promotion
{
    typedef char (&type)[N];
};

#define RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(I,T) \
    sized_type_for_promotion<I>::type promoted_index_tester(T);

#else

#define RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(I,T) \
    char (&promoted_index_tester(T))[I];

#endif

RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(1, int          )
RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(2, unsigned int )
RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(3, long         )
RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(4, unsigned long)

#if defined(RTIBOOST_HAS_LONG_LONG)
RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(5, rtiboost::long_long_type )
RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(6, rtiboost::ulong_long_type)
#elif defined(RTIBOOST_HAS_MS_INT64)
RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(7, __int64         )
RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER(8, unsigned __int64)
#endif

#undef RTIBOOST_TT_AUX_PROMOTED_INDEX_TESTER


// Get an index of promoted type for type T.
// Precondition: need_promotion<T>
template<class T>
struct promoted_index
{
    static T testee; // undefined
    RTIBOOST_STATIC_CONSTANT(int, value = sizeof(promoted_index_tester(+testee)) );
    // Unary plus promotes testee                    LOOK HERE ---> ^
};

template<class T>
struct integral_promotion_impl
{
    typedef RTIBOOST_DEDUCED_TYPENAME promote_from_index<
        (rtiboost::type_traits::detail::promoted_index<T>::value)
      , (rtiboost::is_const<T>::value)
      , (rtiboost::is_volatile<T>::value)
      >::type type;
};

template<class T, bool b> struct integral_promotion { typedef T type; };
template<class T> struct integral_promotion<T, true> : public integral_promotion_impl<T>{};

} }

template <class T> struct integral_promotion
{
private:
   typedef rtiboost::type_traits::detail::need_promotion<typename remove_cv<T>::type> tag_type;
public:
   typedef typename rtiboost::type_traits::detail::integral_promotion<T, tag_type::value>::type type;
};

}

#endif // #ifndef RTIBOOST_type_traits_integral_promotion_hpp_INCLUDED

