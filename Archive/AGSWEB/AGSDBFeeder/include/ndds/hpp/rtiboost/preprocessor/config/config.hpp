# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002-2011.                             *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef RTIBOOST_PREPROCESSOR_CONFIG_CONFIG_HPP
# define RTIBOOST_PREPROCESSOR_CONFIG_CONFIG_HPP
#
# /* RTIBOOST_PP_CONFIG_FLAGS */
#
# define RTIBOOST_PP_CONFIG_STRICT() 0x0001
# define RTIBOOST_PP_CONFIG_IDEAL() 0x0002
#
# define RTIBOOST_PP_CONFIG_MSVC() 0x0004
# define RTIBOOST_PP_CONFIG_MWCC() 0x0008
# define RTIBOOST_PP_CONFIG_BCC() 0x0010
# define RTIBOOST_PP_CONFIG_EDG() 0x0020
# define RTIBOOST_PP_CONFIG_DMC() 0x0040
#
# ifndef RTIBOOST_PP_CONFIG_FLAGS
#    if defined(__GCCXML__)
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_STRICT())
#    elif defined(__WAVE__)
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_STRICT())
#    elif defined(__MWERKS__) && __MWERKS__ >= 0x3200
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_STRICT())
#    elif defined(__EDG__) || defined(__EDG_VERSION__)
#        if defined(_MSC_VER) && __EDG_VERSION__ >= 308
#            define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_MSVC())
#        else
#            define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_EDG() | RTIBOOST_PP_CONFIG_STRICT())
#        endif
#    elif defined(__MWERKS__)
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_MWCC())
#    elif defined(__DMC__)
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_DMC())
#    elif defined(__BORLANDC__) && __BORLANDC__ >= 0x581
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_STRICT())
#    elif defined(__BORLANDC__) || defined(__IBMC__) || defined(__IBMCPP__) || defined(__SUNPRO_CC)
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_BCC())
#    elif defined(_MSC_VER)
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_MSVC())
#    else
#        define RTIBOOST_PP_CONFIG_FLAGS() (RTIBOOST_PP_CONFIG_STRICT())
#    endif
# endif
#
# /* RTIBOOST_PP_CONFIG_EXTENDED_LINE_INFO */
#
# ifndef RTIBOOST_PP_CONFIG_EXTENDED_LINE_INFO
#    define RTIBOOST_PP_CONFIG_EXTENDED_LINE_INFO 0
# endif
#
# /* RTIBOOST_PP_CONFIG_ERRORS */
#
# ifndef RTIBOOST_PP_CONFIG_ERRORS
#    ifdef NDEBUG
#        define RTIBOOST_PP_CONFIG_ERRORS 0
#    else
#        define RTIBOOST_PP_CONFIG_ERRORS 1
#    endif
# endif
#
# /* RTIBOOST_PP_VARIADICS */
#
# if !defined RTIBOOST_PP_VARIADICS
#    /* variadic support explicitly disabled for all untested compilers */
#    if defined __GCCXML__ || defined __CUDACC__ || defined __PATHSCALE__ || defined __clang__ || defined __DMC__ || defined __CODEGEARC__ || defined __BORLANDC__ || defined __MWERKS__ || defined __SUNPRO_CC || defined __HP_aCC && !defined __EDG__ || defined __MRC__ || defined __SC__ || defined __IBMCPP__ || defined __PGI
#        define RTIBOOST_PP_VARIADICS 0
#    /* VC++ (C/C++) */
#    elif defined _MSC_VER && _MSC_VER >= 1400 && !defined __EDG__
#        if _MSC_VER >= 1400
#            define RTIBOOST_PP_VARIADICS 1
#            define RTIBOOST_PP_VARIADICS_MSVC 1
#        else
#            define RTIBOOST_PP_VARIADICS 0
#        endif
#    /* Wave (C/C++), GCC (C++) */
#    elif defined __WAVE__ && __WAVE_HAS_VARIADICS__ || defined __GNUC__ && __GXX_EXPERIMENTAL_CXX0X__
#        define RTIBOOST_PP_VARIADICS 1
#    /* EDG-based (C/C++), GCC (C), and unknown (C/C++) */
#    elif !defined __cplusplus && __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L
#        define RTIBOOST_PP_VARIADICS 1
#    else
#        define RTIBOOST_PP_VARIADICS 0
#    endif
# elif !RTIBOOST_PP_VARIADICS + 1 < 2
#    undef RTIBOOST_PP_VARIADICS
#    define RTIBOOST_PP_VARIADICS 1
#    if defined _MSC_VER && _MSC_VER >= 1400 && !(defined __EDG__ || defined __GCCXML__ || defined __CUDACC__ || defined __PATHSCALE__ || defined __clang__ || defined __DMC__ || defined __CODEGEARC__ || defined __BORLANDC__ || defined __MWERKS__ || defined __SUNPRO_CC || defined __HP_aCC || defined __MRC__ || defined __SC__ || defined __IBMCPP__ || defined __PGI)
#        define RTIBOOST_PP_VARIADICS_MSVC 1
#    endif
# else
#    undef RTIBOOST_PP_VARIADICS
#    define RTIBOOST_PP_VARIADICS 0
# endif
#
# endif
