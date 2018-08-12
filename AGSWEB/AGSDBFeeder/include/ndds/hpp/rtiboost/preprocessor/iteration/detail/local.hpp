# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# if !defined(RTIBOOST_PP_LOCAL_LIMITS)
#    error RTIBOOST_PP_ERROR:  local iteration boundaries are not defined
# elif !defined(RTIBOOST_PP_LOCAL_MACRO)
#    error RTIBOOST_PP_ERROR:  local iteration target macro is not defined
# else
#    if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#        define RTIBOOST_PP_LOCAL_S RTIBOOST_PP_TUPLE_ELEM(2, 0, RTIBOOST_PP_LOCAL_LIMITS)
#        define RTIBOOST_PP_LOCAL_F RTIBOOST_PP_TUPLE_ELEM(2, 1, RTIBOOST_PP_LOCAL_LIMITS)
#    else
#        define RTIBOOST_PP_VALUE RTIBOOST_PP_TUPLE_ELEM(2, 0, RTIBOOST_PP_LOCAL_LIMITS)
#        include <rtiboost/preprocessor/iteration/detail/start.hpp>
#        define RTIBOOST_PP_VALUE RTIBOOST_PP_TUPLE_ELEM(2, 1, RTIBOOST_PP_LOCAL_LIMITS)
#        include <rtiboost/preprocessor/iteration/detail/finish.hpp>
#        define RTIBOOST_PP_LOCAL_S RTIBOOST_PP_LOCAL_SE()
#        define RTIBOOST_PP_LOCAL_F RTIBOOST_PP_LOCAL_FE()
#    endif
# endif
#
# if (RTIBOOST_PP_LOCAL_S) > (RTIBOOST_PP_LOCAL_F)
#    include <rtiboost/preprocessor/iteration/detail/rlocal.hpp>
# else
#    if RTIBOOST_PP_LOCAL_C(0)
        RTIBOOST_PP_LOCAL_MACRO(0)
#    endif
#    if RTIBOOST_PP_LOCAL_C(1)
        RTIBOOST_PP_LOCAL_MACRO(1)
#    endif
#    if RTIBOOST_PP_LOCAL_C(2)
        RTIBOOST_PP_LOCAL_MACRO(2)
#    endif
#    if RTIBOOST_PP_LOCAL_C(3)
        RTIBOOST_PP_LOCAL_MACRO(3)
#    endif
#    if RTIBOOST_PP_LOCAL_C(4)
        RTIBOOST_PP_LOCAL_MACRO(4)
#    endif
#    if RTIBOOST_PP_LOCAL_C(5)
        RTIBOOST_PP_LOCAL_MACRO(5)
#    endif
#    if RTIBOOST_PP_LOCAL_C(6)
        RTIBOOST_PP_LOCAL_MACRO(6)
#    endif
#    if RTIBOOST_PP_LOCAL_C(7)
        RTIBOOST_PP_LOCAL_MACRO(7)
#    endif
#    if RTIBOOST_PP_LOCAL_C(8)
        RTIBOOST_PP_LOCAL_MACRO(8)
#    endif
#    if RTIBOOST_PP_LOCAL_C(9)
        RTIBOOST_PP_LOCAL_MACRO(9)
#    endif
#    if RTIBOOST_PP_LOCAL_C(10)
        RTIBOOST_PP_LOCAL_MACRO(10)
#    endif
#    if RTIBOOST_PP_LOCAL_C(11)
        RTIBOOST_PP_LOCAL_MACRO(11)
#    endif
#    if RTIBOOST_PP_LOCAL_C(12)
        RTIBOOST_PP_LOCAL_MACRO(12)
#    endif
#    if RTIBOOST_PP_LOCAL_C(13)
        RTIBOOST_PP_LOCAL_MACRO(13)
#    endif
#    if RTIBOOST_PP_LOCAL_C(14)
        RTIBOOST_PP_LOCAL_MACRO(14)
#    endif
#    if RTIBOOST_PP_LOCAL_C(15)
        RTIBOOST_PP_LOCAL_MACRO(15)
#    endif
#    if RTIBOOST_PP_LOCAL_C(16)
        RTIBOOST_PP_LOCAL_MACRO(16)
#    endif
#    if RTIBOOST_PP_LOCAL_C(17)
        RTIBOOST_PP_LOCAL_MACRO(17)
#    endif
#    if RTIBOOST_PP_LOCAL_C(18)
        RTIBOOST_PP_LOCAL_MACRO(18)
#    endif
#    if RTIBOOST_PP_LOCAL_C(19)
        RTIBOOST_PP_LOCAL_MACRO(19)
#    endif
#    if RTIBOOST_PP_LOCAL_C(20)
        RTIBOOST_PP_LOCAL_MACRO(20)
#    endif
#    if RTIBOOST_PP_LOCAL_C(21)
        RTIBOOST_PP_LOCAL_MACRO(21)
#    endif
#    if RTIBOOST_PP_LOCAL_C(22)
        RTIBOOST_PP_LOCAL_MACRO(22)
#    endif
#    if RTIBOOST_PP_LOCAL_C(23)
        RTIBOOST_PP_LOCAL_MACRO(23)
#    endif
#    if RTIBOOST_PP_LOCAL_C(24)
        RTIBOOST_PP_LOCAL_MACRO(24)
#    endif
#    if RTIBOOST_PP_LOCAL_C(25)
        RTIBOOST_PP_LOCAL_MACRO(25)
#    endif
#    if RTIBOOST_PP_LOCAL_C(26)
        RTIBOOST_PP_LOCAL_MACRO(26)
#    endif
#    if RTIBOOST_PP_LOCAL_C(27)
        RTIBOOST_PP_LOCAL_MACRO(27)
#    endif
#    if RTIBOOST_PP_LOCAL_C(28)
        RTIBOOST_PP_LOCAL_MACRO(28)
#    endif
#    if RTIBOOST_PP_LOCAL_C(29)
        RTIBOOST_PP_LOCAL_MACRO(29)
#    endif
#    if RTIBOOST_PP_LOCAL_C(30)
        RTIBOOST_PP_LOCAL_MACRO(30)
#    endif
#    if RTIBOOST_PP_LOCAL_C(31)
        RTIBOOST_PP_LOCAL_MACRO(31)
#    endif
#    if RTIBOOST_PP_LOCAL_C(32)
        RTIBOOST_PP_LOCAL_MACRO(32)
#    endif
#    if RTIBOOST_PP_LOCAL_C(33)
        RTIBOOST_PP_LOCAL_MACRO(33)
#    endif
#    if RTIBOOST_PP_LOCAL_C(34)
        RTIBOOST_PP_LOCAL_MACRO(34)
#    endif
#    if RTIBOOST_PP_LOCAL_C(35)
        RTIBOOST_PP_LOCAL_MACRO(35)
#    endif
#    if RTIBOOST_PP_LOCAL_C(36)
        RTIBOOST_PP_LOCAL_MACRO(36)
#    endif
#    if RTIBOOST_PP_LOCAL_C(37)
        RTIBOOST_PP_LOCAL_MACRO(37)
#    endif
#    if RTIBOOST_PP_LOCAL_C(38)
        RTIBOOST_PP_LOCAL_MACRO(38)
#    endif
#    if RTIBOOST_PP_LOCAL_C(39)
        RTIBOOST_PP_LOCAL_MACRO(39)
#    endif
#    if RTIBOOST_PP_LOCAL_C(40)
        RTIBOOST_PP_LOCAL_MACRO(40)
#    endif
#    if RTIBOOST_PP_LOCAL_C(41)
        RTIBOOST_PP_LOCAL_MACRO(41)
#    endif
#    if RTIBOOST_PP_LOCAL_C(42)
        RTIBOOST_PP_LOCAL_MACRO(42)
#    endif
#    if RTIBOOST_PP_LOCAL_C(43)
        RTIBOOST_PP_LOCAL_MACRO(43)
#    endif
#    if RTIBOOST_PP_LOCAL_C(44)
        RTIBOOST_PP_LOCAL_MACRO(44)
#    endif
#    if RTIBOOST_PP_LOCAL_C(45)
        RTIBOOST_PP_LOCAL_MACRO(45)
#    endif
#    if RTIBOOST_PP_LOCAL_C(46)
        RTIBOOST_PP_LOCAL_MACRO(46)
#    endif
#    if RTIBOOST_PP_LOCAL_C(47)
        RTIBOOST_PP_LOCAL_MACRO(47)
#    endif
#    if RTIBOOST_PP_LOCAL_C(48)
        RTIBOOST_PP_LOCAL_MACRO(48)
#    endif
#    if RTIBOOST_PP_LOCAL_C(49)
        RTIBOOST_PP_LOCAL_MACRO(49)
#    endif
#    if RTIBOOST_PP_LOCAL_C(50)
        RTIBOOST_PP_LOCAL_MACRO(50)
#    endif
#    if RTIBOOST_PP_LOCAL_C(51)
        RTIBOOST_PP_LOCAL_MACRO(51)
#    endif
#    if RTIBOOST_PP_LOCAL_C(52)
        RTIBOOST_PP_LOCAL_MACRO(52)
#    endif
#    if RTIBOOST_PP_LOCAL_C(53)
        RTIBOOST_PP_LOCAL_MACRO(53)
#    endif
#    if RTIBOOST_PP_LOCAL_C(54)
        RTIBOOST_PP_LOCAL_MACRO(54)
#    endif
#    if RTIBOOST_PP_LOCAL_C(55)
        RTIBOOST_PP_LOCAL_MACRO(55)
#    endif
#    if RTIBOOST_PP_LOCAL_C(56)
        RTIBOOST_PP_LOCAL_MACRO(56)
#    endif
#    if RTIBOOST_PP_LOCAL_C(57)
        RTIBOOST_PP_LOCAL_MACRO(57)
#    endif
#    if RTIBOOST_PP_LOCAL_C(58)
        RTIBOOST_PP_LOCAL_MACRO(58)
#    endif
#    if RTIBOOST_PP_LOCAL_C(59)
        RTIBOOST_PP_LOCAL_MACRO(59)
#    endif
#    if RTIBOOST_PP_LOCAL_C(60)
        RTIBOOST_PP_LOCAL_MACRO(60)
#    endif
#    if RTIBOOST_PP_LOCAL_C(61)
        RTIBOOST_PP_LOCAL_MACRO(61)
#    endif
#    if RTIBOOST_PP_LOCAL_C(62)
        RTIBOOST_PP_LOCAL_MACRO(62)
#    endif
#    if RTIBOOST_PP_LOCAL_C(63)
        RTIBOOST_PP_LOCAL_MACRO(63)
#    endif
#    if RTIBOOST_PP_LOCAL_C(64)
        RTIBOOST_PP_LOCAL_MACRO(64)
#    endif
#    if RTIBOOST_PP_LOCAL_C(65)
        RTIBOOST_PP_LOCAL_MACRO(65)
#    endif
#    if RTIBOOST_PP_LOCAL_C(66)
        RTIBOOST_PP_LOCAL_MACRO(66)
#    endif
#    if RTIBOOST_PP_LOCAL_C(67)
        RTIBOOST_PP_LOCAL_MACRO(67)
#    endif
#    if RTIBOOST_PP_LOCAL_C(68)
        RTIBOOST_PP_LOCAL_MACRO(68)
#    endif
#    if RTIBOOST_PP_LOCAL_C(69)
        RTIBOOST_PP_LOCAL_MACRO(69)
#    endif
#    if RTIBOOST_PP_LOCAL_C(70)
        RTIBOOST_PP_LOCAL_MACRO(70)
#    endif
#    if RTIBOOST_PP_LOCAL_C(71)
        RTIBOOST_PP_LOCAL_MACRO(71)
#    endif
#    if RTIBOOST_PP_LOCAL_C(72)
        RTIBOOST_PP_LOCAL_MACRO(72)
#    endif
#    if RTIBOOST_PP_LOCAL_C(73)
        RTIBOOST_PP_LOCAL_MACRO(73)
#    endif
#    if RTIBOOST_PP_LOCAL_C(74)
        RTIBOOST_PP_LOCAL_MACRO(74)
#    endif
#    if RTIBOOST_PP_LOCAL_C(75)
        RTIBOOST_PP_LOCAL_MACRO(75)
#    endif
#    if RTIBOOST_PP_LOCAL_C(76)
        RTIBOOST_PP_LOCAL_MACRO(76)
#    endif
#    if RTIBOOST_PP_LOCAL_C(77)
        RTIBOOST_PP_LOCAL_MACRO(77)
#    endif
#    if RTIBOOST_PP_LOCAL_C(78)
        RTIBOOST_PP_LOCAL_MACRO(78)
#    endif
#    if RTIBOOST_PP_LOCAL_C(79)
        RTIBOOST_PP_LOCAL_MACRO(79)
#    endif
#    if RTIBOOST_PP_LOCAL_C(80)
        RTIBOOST_PP_LOCAL_MACRO(80)
#    endif
#    if RTIBOOST_PP_LOCAL_C(81)
        RTIBOOST_PP_LOCAL_MACRO(81)
#    endif
#    if RTIBOOST_PP_LOCAL_C(82)
        RTIBOOST_PP_LOCAL_MACRO(82)
#    endif
#    if RTIBOOST_PP_LOCAL_C(83)
        RTIBOOST_PP_LOCAL_MACRO(83)
#    endif
#    if RTIBOOST_PP_LOCAL_C(84)
        RTIBOOST_PP_LOCAL_MACRO(84)
#    endif
#    if RTIBOOST_PP_LOCAL_C(85)
        RTIBOOST_PP_LOCAL_MACRO(85)
#    endif
#    if RTIBOOST_PP_LOCAL_C(86)
        RTIBOOST_PP_LOCAL_MACRO(86)
#    endif
#    if RTIBOOST_PP_LOCAL_C(87)
        RTIBOOST_PP_LOCAL_MACRO(87)
#    endif
#    if RTIBOOST_PP_LOCAL_C(88)
        RTIBOOST_PP_LOCAL_MACRO(88)
#    endif
#    if RTIBOOST_PP_LOCAL_C(89)
        RTIBOOST_PP_LOCAL_MACRO(89)
#    endif
#    if RTIBOOST_PP_LOCAL_C(90)
        RTIBOOST_PP_LOCAL_MACRO(90)
#    endif
#    if RTIBOOST_PP_LOCAL_C(91)
        RTIBOOST_PP_LOCAL_MACRO(91)
#    endif
#    if RTIBOOST_PP_LOCAL_C(92)
        RTIBOOST_PP_LOCAL_MACRO(92)
#    endif
#    if RTIBOOST_PP_LOCAL_C(93)
        RTIBOOST_PP_LOCAL_MACRO(93)
#    endif
#    if RTIBOOST_PP_LOCAL_C(94)
        RTIBOOST_PP_LOCAL_MACRO(94)
#    endif
#    if RTIBOOST_PP_LOCAL_C(95)
        RTIBOOST_PP_LOCAL_MACRO(95)
#    endif
#    if RTIBOOST_PP_LOCAL_C(96)
        RTIBOOST_PP_LOCAL_MACRO(96)
#    endif
#    if RTIBOOST_PP_LOCAL_C(97)
        RTIBOOST_PP_LOCAL_MACRO(97)
#    endif
#    if RTIBOOST_PP_LOCAL_C(98)
        RTIBOOST_PP_LOCAL_MACRO(98)
#    endif
#    if RTIBOOST_PP_LOCAL_C(99)
        RTIBOOST_PP_LOCAL_MACRO(99)
#    endif
#    if RTIBOOST_PP_LOCAL_C(100)
        RTIBOOST_PP_LOCAL_MACRO(100)
#    endif
#    if RTIBOOST_PP_LOCAL_C(101)
        RTIBOOST_PP_LOCAL_MACRO(101)
#    endif
#    if RTIBOOST_PP_LOCAL_C(102)
        RTIBOOST_PP_LOCAL_MACRO(102)
#    endif
#    if RTIBOOST_PP_LOCAL_C(103)
        RTIBOOST_PP_LOCAL_MACRO(103)
#    endif
#    if RTIBOOST_PP_LOCAL_C(104)
        RTIBOOST_PP_LOCAL_MACRO(104)
#    endif
#    if RTIBOOST_PP_LOCAL_C(105)
        RTIBOOST_PP_LOCAL_MACRO(105)
#    endif
#    if RTIBOOST_PP_LOCAL_C(106)
        RTIBOOST_PP_LOCAL_MACRO(106)
#    endif
#    if RTIBOOST_PP_LOCAL_C(107)
        RTIBOOST_PP_LOCAL_MACRO(107)
#    endif
#    if RTIBOOST_PP_LOCAL_C(108)
        RTIBOOST_PP_LOCAL_MACRO(108)
#    endif
#    if RTIBOOST_PP_LOCAL_C(109)
        RTIBOOST_PP_LOCAL_MACRO(109)
#    endif
#    if RTIBOOST_PP_LOCAL_C(110)
        RTIBOOST_PP_LOCAL_MACRO(110)
#    endif
#    if RTIBOOST_PP_LOCAL_C(111)
        RTIBOOST_PP_LOCAL_MACRO(111)
#    endif
#    if RTIBOOST_PP_LOCAL_C(112)
        RTIBOOST_PP_LOCAL_MACRO(112)
#    endif
#    if RTIBOOST_PP_LOCAL_C(113)
        RTIBOOST_PP_LOCAL_MACRO(113)
#    endif
#    if RTIBOOST_PP_LOCAL_C(114)
        RTIBOOST_PP_LOCAL_MACRO(114)
#    endif
#    if RTIBOOST_PP_LOCAL_C(115)
        RTIBOOST_PP_LOCAL_MACRO(115)
#    endif
#    if RTIBOOST_PP_LOCAL_C(116)
        RTIBOOST_PP_LOCAL_MACRO(116)
#    endif
#    if RTIBOOST_PP_LOCAL_C(117)
        RTIBOOST_PP_LOCAL_MACRO(117)
#    endif
#    if RTIBOOST_PP_LOCAL_C(118)
        RTIBOOST_PP_LOCAL_MACRO(118)
#    endif
#    if RTIBOOST_PP_LOCAL_C(119)
        RTIBOOST_PP_LOCAL_MACRO(119)
#    endif
#    if RTIBOOST_PP_LOCAL_C(120)
        RTIBOOST_PP_LOCAL_MACRO(120)
#    endif
#    if RTIBOOST_PP_LOCAL_C(121)
        RTIBOOST_PP_LOCAL_MACRO(121)
#    endif
#    if RTIBOOST_PP_LOCAL_C(122)
        RTIBOOST_PP_LOCAL_MACRO(122)
#    endif
#    if RTIBOOST_PP_LOCAL_C(123)
        RTIBOOST_PP_LOCAL_MACRO(123)
#    endif
#    if RTIBOOST_PP_LOCAL_C(124)
        RTIBOOST_PP_LOCAL_MACRO(124)
#    endif
#    if RTIBOOST_PP_LOCAL_C(125)
        RTIBOOST_PP_LOCAL_MACRO(125)
#    endif
#    if RTIBOOST_PP_LOCAL_C(126)
        RTIBOOST_PP_LOCAL_MACRO(126)
#    endif
#    if RTIBOOST_PP_LOCAL_C(127)
        RTIBOOST_PP_LOCAL_MACRO(127)
#    endif
#    if RTIBOOST_PP_LOCAL_C(128)
        RTIBOOST_PP_LOCAL_MACRO(128)
#    endif
#    if RTIBOOST_PP_LOCAL_C(129)
        RTIBOOST_PP_LOCAL_MACRO(129)
#    endif
#    if RTIBOOST_PP_LOCAL_C(130)
        RTIBOOST_PP_LOCAL_MACRO(130)
#    endif
#    if RTIBOOST_PP_LOCAL_C(131)
        RTIBOOST_PP_LOCAL_MACRO(131)
#    endif
#    if RTIBOOST_PP_LOCAL_C(132)
        RTIBOOST_PP_LOCAL_MACRO(132)
#    endif
#    if RTIBOOST_PP_LOCAL_C(133)
        RTIBOOST_PP_LOCAL_MACRO(133)
#    endif
#    if RTIBOOST_PP_LOCAL_C(134)
        RTIBOOST_PP_LOCAL_MACRO(134)
#    endif
#    if RTIBOOST_PP_LOCAL_C(135)
        RTIBOOST_PP_LOCAL_MACRO(135)
#    endif
#    if RTIBOOST_PP_LOCAL_C(136)
        RTIBOOST_PP_LOCAL_MACRO(136)
#    endif
#    if RTIBOOST_PP_LOCAL_C(137)
        RTIBOOST_PP_LOCAL_MACRO(137)
#    endif
#    if RTIBOOST_PP_LOCAL_C(138)
        RTIBOOST_PP_LOCAL_MACRO(138)
#    endif
#    if RTIBOOST_PP_LOCAL_C(139)
        RTIBOOST_PP_LOCAL_MACRO(139)
#    endif
#    if RTIBOOST_PP_LOCAL_C(140)
        RTIBOOST_PP_LOCAL_MACRO(140)
#    endif
#    if RTIBOOST_PP_LOCAL_C(141)
        RTIBOOST_PP_LOCAL_MACRO(141)
#    endif
#    if RTIBOOST_PP_LOCAL_C(142)
        RTIBOOST_PP_LOCAL_MACRO(142)
#    endif
#    if RTIBOOST_PP_LOCAL_C(143)
        RTIBOOST_PP_LOCAL_MACRO(143)
#    endif
#    if RTIBOOST_PP_LOCAL_C(144)
        RTIBOOST_PP_LOCAL_MACRO(144)
#    endif
#    if RTIBOOST_PP_LOCAL_C(145)
        RTIBOOST_PP_LOCAL_MACRO(145)
#    endif
#    if RTIBOOST_PP_LOCAL_C(146)
        RTIBOOST_PP_LOCAL_MACRO(146)
#    endif
#    if RTIBOOST_PP_LOCAL_C(147)
        RTIBOOST_PP_LOCAL_MACRO(147)
#    endif
#    if RTIBOOST_PP_LOCAL_C(148)
        RTIBOOST_PP_LOCAL_MACRO(148)
#    endif
#    if RTIBOOST_PP_LOCAL_C(149)
        RTIBOOST_PP_LOCAL_MACRO(149)
#    endif
#    if RTIBOOST_PP_LOCAL_C(150)
        RTIBOOST_PP_LOCAL_MACRO(150)
#    endif
#    if RTIBOOST_PP_LOCAL_C(151)
        RTIBOOST_PP_LOCAL_MACRO(151)
#    endif
#    if RTIBOOST_PP_LOCAL_C(152)
        RTIBOOST_PP_LOCAL_MACRO(152)
#    endif
#    if RTIBOOST_PP_LOCAL_C(153)
        RTIBOOST_PP_LOCAL_MACRO(153)
#    endif
#    if RTIBOOST_PP_LOCAL_C(154)
        RTIBOOST_PP_LOCAL_MACRO(154)
#    endif
#    if RTIBOOST_PP_LOCAL_C(155)
        RTIBOOST_PP_LOCAL_MACRO(155)
#    endif
#    if RTIBOOST_PP_LOCAL_C(156)
        RTIBOOST_PP_LOCAL_MACRO(156)
#    endif
#    if RTIBOOST_PP_LOCAL_C(157)
        RTIBOOST_PP_LOCAL_MACRO(157)
#    endif
#    if RTIBOOST_PP_LOCAL_C(158)
        RTIBOOST_PP_LOCAL_MACRO(158)
#    endif
#    if RTIBOOST_PP_LOCAL_C(159)
        RTIBOOST_PP_LOCAL_MACRO(159)
#    endif
#    if RTIBOOST_PP_LOCAL_C(160)
        RTIBOOST_PP_LOCAL_MACRO(160)
#    endif
#    if RTIBOOST_PP_LOCAL_C(161)
        RTIBOOST_PP_LOCAL_MACRO(161)
#    endif
#    if RTIBOOST_PP_LOCAL_C(162)
        RTIBOOST_PP_LOCAL_MACRO(162)
#    endif
#    if RTIBOOST_PP_LOCAL_C(163)
        RTIBOOST_PP_LOCAL_MACRO(163)
#    endif
#    if RTIBOOST_PP_LOCAL_C(164)
        RTIBOOST_PP_LOCAL_MACRO(164)
#    endif
#    if RTIBOOST_PP_LOCAL_C(165)
        RTIBOOST_PP_LOCAL_MACRO(165)
#    endif
#    if RTIBOOST_PP_LOCAL_C(166)
        RTIBOOST_PP_LOCAL_MACRO(166)
#    endif
#    if RTIBOOST_PP_LOCAL_C(167)
        RTIBOOST_PP_LOCAL_MACRO(167)
#    endif
#    if RTIBOOST_PP_LOCAL_C(168)
        RTIBOOST_PP_LOCAL_MACRO(168)
#    endif
#    if RTIBOOST_PP_LOCAL_C(169)
        RTIBOOST_PP_LOCAL_MACRO(169)
#    endif
#    if RTIBOOST_PP_LOCAL_C(170)
        RTIBOOST_PP_LOCAL_MACRO(170)
#    endif
#    if RTIBOOST_PP_LOCAL_C(171)
        RTIBOOST_PP_LOCAL_MACRO(171)
#    endif
#    if RTIBOOST_PP_LOCAL_C(172)
        RTIBOOST_PP_LOCAL_MACRO(172)
#    endif
#    if RTIBOOST_PP_LOCAL_C(173)
        RTIBOOST_PP_LOCAL_MACRO(173)
#    endif
#    if RTIBOOST_PP_LOCAL_C(174)
        RTIBOOST_PP_LOCAL_MACRO(174)
#    endif
#    if RTIBOOST_PP_LOCAL_C(175)
        RTIBOOST_PP_LOCAL_MACRO(175)
#    endif
#    if RTIBOOST_PP_LOCAL_C(176)
        RTIBOOST_PP_LOCAL_MACRO(176)
#    endif
#    if RTIBOOST_PP_LOCAL_C(177)
        RTIBOOST_PP_LOCAL_MACRO(177)
#    endif
#    if RTIBOOST_PP_LOCAL_C(178)
        RTIBOOST_PP_LOCAL_MACRO(178)
#    endif
#    if RTIBOOST_PP_LOCAL_C(179)
        RTIBOOST_PP_LOCAL_MACRO(179)
#    endif
#    if RTIBOOST_PP_LOCAL_C(180)
        RTIBOOST_PP_LOCAL_MACRO(180)
#    endif
#    if RTIBOOST_PP_LOCAL_C(181)
        RTIBOOST_PP_LOCAL_MACRO(181)
#    endif
#    if RTIBOOST_PP_LOCAL_C(182)
        RTIBOOST_PP_LOCAL_MACRO(182)
#    endif
#    if RTIBOOST_PP_LOCAL_C(183)
        RTIBOOST_PP_LOCAL_MACRO(183)
#    endif
#    if RTIBOOST_PP_LOCAL_C(184)
        RTIBOOST_PP_LOCAL_MACRO(184)
#    endif
#    if RTIBOOST_PP_LOCAL_C(185)
        RTIBOOST_PP_LOCAL_MACRO(185)
#    endif
#    if RTIBOOST_PP_LOCAL_C(186)
        RTIBOOST_PP_LOCAL_MACRO(186)
#    endif
#    if RTIBOOST_PP_LOCAL_C(187)
        RTIBOOST_PP_LOCAL_MACRO(187)
#    endif
#    if RTIBOOST_PP_LOCAL_C(188)
        RTIBOOST_PP_LOCAL_MACRO(188)
#    endif
#    if RTIBOOST_PP_LOCAL_C(189)
        RTIBOOST_PP_LOCAL_MACRO(189)
#    endif
#    if RTIBOOST_PP_LOCAL_C(190)
        RTIBOOST_PP_LOCAL_MACRO(190)
#    endif
#    if RTIBOOST_PP_LOCAL_C(191)
        RTIBOOST_PP_LOCAL_MACRO(191)
#    endif
#    if RTIBOOST_PP_LOCAL_C(192)
        RTIBOOST_PP_LOCAL_MACRO(192)
#    endif
#    if RTIBOOST_PP_LOCAL_C(193)
        RTIBOOST_PP_LOCAL_MACRO(193)
#    endif
#    if RTIBOOST_PP_LOCAL_C(194)
        RTIBOOST_PP_LOCAL_MACRO(194)
#    endif
#    if RTIBOOST_PP_LOCAL_C(195)
        RTIBOOST_PP_LOCAL_MACRO(195)
#    endif
#    if RTIBOOST_PP_LOCAL_C(196)
        RTIBOOST_PP_LOCAL_MACRO(196)
#    endif
#    if RTIBOOST_PP_LOCAL_C(197)
        RTIBOOST_PP_LOCAL_MACRO(197)
#    endif
#    if RTIBOOST_PP_LOCAL_C(198)
        RTIBOOST_PP_LOCAL_MACRO(198)
#    endif
#    if RTIBOOST_PP_LOCAL_C(199)
        RTIBOOST_PP_LOCAL_MACRO(199)
#    endif
#    if RTIBOOST_PP_LOCAL_C(200)
        RTIBOOST_PP_LOCAL_MACRO(200)
#    endif
#    if RTIBOOST_PP_LOCAL_C(201)
        RTIBOOST_PP_LOCAL_MACRO(201)
#    endif
#    if RTIBOOST_PP_LOCAL_C(202)
        RTIBOOST_PP_LOCAL_MACRO(202)
#    endif
#    if RTIBOOST_PP_LOCAL_C(203)
        RTIBOOST_PP_LOCAL_MACRO(203)
#    endif
#    if RTIBOOST_PP_LOCAL_C(204)
        RTIBOOST_PP_LOCAL_MACRO(204)
#    endif
#    if RTIBOOST_PP_LOCAL_C(205)
        RTIBOOST_PP_LOCAL_MACRO(205)
#    endif
#    if RTIBOOST_PP_LOCAL_C(206)
        RTIBOOST_PP_LOCAL_MACRO(206)
#    endif
#    if RTIBOOST_PP_LOCAL_C(207)
        RTIBOOST_PP_LOCAL_MACRO(207)
#    endif
#    if RTIBOOST_PP_LOCAL_C(208)
        RTIBOOST_PP_LOCAL_MACRO(208)
#    endif
#    if RTIBOOST_PP_LOCAL_C(209)
        RTIBOOST_PP_LOCAL_MACRO(209)
#    endif
#    if RTIBOOST_PP_LOCAL_C(210)
        RTIBOOST_PP_LOCAL_MACRO(210)
#    endif
#    if RTIBOOST_PP_LOCAL_C(211)
        RTIBOOST_PP_LOCAL_MACRO(211)
#    endif
#    if RTIBOOST_PP_LOCAL_C(212)
        RTIBOOST_PP_LOCAL_MACRO(212)
#    endif
#    if RTIBOOST_PP_LOCAL_C(213)
        RTIBOOST_PP_LOCAL_MACRO(213)
#    endif
#    if RTIBOOST_PP_LOCAL_C(214)
        RTIBOOST_PP_LOCAL_MACRO(214)
#    endif
#    if RTIBOOST_PP_LOCAL_C(215)
        RTIBOOST_PP_LOCAL_MACRO(215)
#    endif
#    if RTIBOOST_PP_LOCAL_C(216)
        RTIBOOST_PP_LOCAL_MACRO(216)
#    endif
#    if RTIBOOST_PP_LOCAL_C(217)
        RTIBOOST_PP_LOCAL_MACRO(217)
#    endif
#    if RTIBOOST_PP_LOCAL_C(218)
        RTIBOOST_PP_LOCAL_MACRO(218)
#    endif
#    if RTIBOOST_PP_LOCAL_C(219)
        RTIBOOST_PP_LOCAL_MACRO(219)
#    endif
#    if RTIBOOST_PP_LOCAL_C(220)
        RTIBOOST_PP_LOCAL_MACRO(220)
#    endif
#    if RTIBOOST_PP_LOCAL_C(221)
        RTIBOOST_PP_LOCAL_MACRO(221)
#    endif
#    if RTIBOOST_PP_LOCAL_C(222)
        RTIBOOST_PP_LOCAL_MACRO(222)
#    endif
#    if RTIBOOST_PP_LOCAL_C(223)
        RTIBOOST_PP_LOCAL_MACRO(223)
#    endif
#    if RTIBOOST_PP_LOCAL_C(224)
        RTIBOOST_PP_LOCAL_MACRO(224)
#    endif
#    if RTIBOOST_PP_LOCAL_C(225)
        RTIBOOST_PP_LOCAL_MACRO(225)
#    endif
#    if RTIBOOST_PP_LOCAL_C(226)
        RTIBOOST_PP_LOCAL_MACRO(226)
#    endif
#    if RTIBOOST_PP_LOCAL_C(227)
        RTIBOOST_PP_LOCAL_MACRO(227)
#    endif
#    if RTIBOOST_PP_LOCAL_C(228)
        RTIBOOST_PP_LOCAL_MACRO(228)
#    endif
#    if RTIBOOST_PP_LOCAL_C(229)
        RTIBOOST_PP_LOCAL_MACRO(229)
#    endif
#    if RTIBOOST_PP_LOCAL_C(230)
        RTIBOOST_PP_LOCAL_MACRO(230)
#    endif
#    if RTIBOOST_PP_LOCAL_C(231)
        RTIBOOST_PP_LOCAL_MACRO(231)
#    endif
#    if RTIBOOST_PP_LOCAL_C(232)
        RTIBOOST_PP_LOCAL_MACRO(232)
#    endif
#    if RTIBOOST_PP_LOCAL_C(233)
        RTIBOOST_PP_LOCAL_MACRO(233)
#    endif
#    if RTIBOOST_PP_LOCAL_C(234)
        RTIBOOST_PP_LOCAL_MACRO(234)
#    endif
#    if RTIBOOST_PP_LOCAL_C(235)
        RTIBOOST_PP_LOCAL_MACRO(235)
#    endif
#    if RTIBOOST_PP_LOCAL_C(236)
        RTIBOOST_PP_LOCAL_MACRO(236)
#    endif

#    if RTIBOOST_PP_LOCAL_C(237)
        RTIBOOST_PP_LOCAL_MACRO(237)
#    endif
#    if RTIBOOST_PP_LOCAL_C(238)
        RTIBOOST_PP_LOCAL_MACRO(238)
#    endif
#    if RTIBOOST_PP_LOCAL_C(239)
        RTIBOOST_PP_LOCAL_MACRO(239)
#    endif
#    if RTIBOOST_PP_LOCAL_C(240)
        RTIBOOST_PP_LOCAL_MACRO(240)
#    endif
#    if RTIBOOST_PP_LOCAL_C(241)
        RTIBOOST_PP_LOCAL_MACRO(241)
#    endif
#    if RTIBOOST_PP_LOCAL_C(242)
        RTIBOOST_PP_LOCAL_MACRO(242)
#    endif
#    if RTIBOOST_PP_LOCAL_C(243)
        RTIBOOST_PP_LOCAL_MACRO(243)
#    endif
#    if RTIBOOST_PP_LOCAL_C(244)
        RTIBOOST_PP_LOCAL_MACRO(244)
#    endif
#    if RTIBOOST_PP_LOCAL_C(245)
        RTIBOOST_PP_LOCAL_MACRO(245)
#    endif
#    if RTIBOOST_PP_LOCAL_C(246)
        RTIBOOST_PP_LOCAL_MACRO(246)
#    endif
#    if RTIBOOST_PP_LOCAL_C(247)
        RTIBOOST_PP_LOCAL_MACRO(247)
#    endif
#    if RTIBOOST_PP_LOCAL_C(248)
        RTIBOOST_PP_LOCAL_MACRO(248)
#    endif
#    if RTIBOOST_PP_LOCAL_C(249)
        RTIBOOST_PP_LOCAL_MACRO(249)
#    endif
#    if RTIBOOST_PP_LOCAL_C(250)
        RTIBOOST_PP_LOCAL_MACRO(250)
#    endif
#    if RTIBOOST_PP_LOCAL_C(251)
        RTIBOOST_PP_LOCAL_MACRO(251)
#    endif
#    if RTIBOOST_PP_LOCAL_C(252)
        RTIBOOST_PP_LOCAL_MACRO(252)
#    endif
#    if RTIBOOST_PP_LOCAL_C(253)
        RTIBOOST_PP_LOCAL_MACRO(253)
#    endif
#    if RTIBOOST_PP_LOCAL_C(254)
        RTIBOOST_PP_LOCAL_MACRO(254)
#    endif
#    if RTIBOOST_PP_LOCAL_C(255)
        RTIBOOST_PP_LOCAL_MACRO(255)
#    endif
#    if RTIBOOST_PP_LOCAL_C(256)
        RTIBOOST_PP_LOCAL_MACRO(256)
#    endif
# endif
#
# undef RTIBOOST_PP_LOCAL_LIMITS
#
# undef RTIBOOST_PP_LOCAL_S
# undef RTIBOOST_PP_LOCAL_F
#
# undef RTIBOOST_PP_LOCAL_MACRO
