// Generated by Flexc++ V2.07.07 on Sat, 16 May 2020 16:56:43 -44156756

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

// $insert class_ih
#include <zapata/json/JSONLexerimpl.h>

// $insert namespace-open
namespace zpt {

// s_ranges_: use (unsigned) characters as index to obtain
//           that character's range-number.
//           The range for EOF is defined in a constant in the
//           class header file
size_t const JSONLexerBase::s_ranges_[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  4,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
    5,  5,  5,  5,  5,  5,  5,  5,  6,  7,  8,  9,  9,  9,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18,
    19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 23, 24, 25, 25,
    25, 26, 27, 28, 29, 30, 31, 32, 32, 33, 34, 34, 35, 36, 37, 38, 38, 38, 39, 40, 41, 42, 43, 43,
    43, 43, 43, 44, 45, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
    47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
    47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
    47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
    47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
    47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
};

// $insert startcondinfo
// s_dfa_ contains the rows of *all* DFAs ordered by start state.  The
// enum class StartCondition_is defined in the baseclass header.
// StartCondition_::INITIAL is always 0.  Each entry defines the row to
// transit to if the column's character range was sensed. Row numbers are
// relative to the used DFA, and d_dfaBase_ is set to the first row of
// the subset to use.  The row's final two values are respectively the
// rule that may be matched at this state, and the rule's FINAL flag. If
// the final value equals FINAL (= 1) then, if there's no continuation,
// the rule is matched. If the BOL flag (8) is also set (so FINAL + BOL (=
// 9) is set) then the rule only matches when d_atBOL is also true.
int const JSONLexerBase::s_dfa_[][51] = {
    // INITIAL
    { -1, 1,  1,  -1, 1,  -1, 1,  -1, 2,  -1, 3,  -1, -1, -1, -1, 4,  5,
      -1, 6,  5,  7,  -1, 8,  -1, 9,  -1, -1, -1, -1, -1, -1, 10, -1, -1,
      -1, 11, -1, 12, -1, -1, -1, 13, 14, -1, 15, -1, 16, -1, -1, -1, -1 }, // 0
    { -1, 1,  1,  -1, 1,  -1, 1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  -1 }, // 1
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, -1 }, // 2
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1 }, // 3
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, -1 }, // 4
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1 }, // 5
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1 }, // 6
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1 }, // 7
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8,  -1 }, // 8
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 9,  -1 }, // 9
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 10
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 11
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1 }, // 12
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 13
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 14
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6,  -1 }, // 15
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7,  -1 }, // 16
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, 22, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 17
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, 23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 18
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, 24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 19
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, -1, -1, -1 }, // 20
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 21
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 22
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 23
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 24
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 25
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 26
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 32, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 27
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 28
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3,  -1 }, // 29
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1,  -1 }, // 30
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 34, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 31
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2,  -1 }, // 32
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 33
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 36,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 34
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 37, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 35
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, 38, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 36
    { 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, -1, 39, 39, 39, 39,
      39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
      39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, -1, -1, -1 }, // 37
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 38
    { 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 41, 39, 39, 39, 39,
      39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
      39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, -1, -1, -1 }, // 39
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 42, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 40
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5,  -1 }, // 41
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4,  -1 }, // 42
                                                                            // string
    { 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  3,  1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1 }, // 0
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1 }, // 1
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1 }, // 2
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1 }, // 3
                                                                            // string_single
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  3,  1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1 }, // 0
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 22, -1 }, // 1
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1 }, // 2
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1 }, // 3
                                                                            // escaped
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2,  1, 1,
      1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 4, 1, 5, 1, 6, 7, 1, 1, 1, 1, 1, -1, -1, -1 }, // 0
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 32, -1 }, // 1
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, -1 }, // 2
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1 }, // 3
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26, -1 }, // 4
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1 }, // 5
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27, -1 }, // 6
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30, -1 }, // 7
                                                                            // unicode
    { 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1, 1,
      1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1 }, // 0
    { 2, 2, -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2, 2,
      2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1 }, // 1
    { 3, 3, -1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  3,  3, 3,
      3, 3, 3,  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, -1, -1, -1 }, // 2
    { 4, 4, -1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  4,  4, 4,
      4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1, -1, -1 }, // 3
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1 }, // 4
                                                                            // number
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  -1, -1,
      0,  -1, 0,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1 }, // 0
                                                                            // regexp
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,  3,  1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1 }, // 0
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1 }, // 1
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, -1 }, // 2
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 24, -1 }, // 3
};

int const (*JSONLexerBase::s_dfaBase_[])[51] = {
    s_dfa_ + 0, s_dfa_ + 43, s_dfa_ + 47, s_dfa_ + 51, s_dfa_ + 59, s_dfa_ + 64, s_dfa_ + 65,
};

size_t JSONLexerBase::s_istreamNr = 0;

// $insert inputImplementation
JSONLexerBase::Input::Input()
  : d_in(0)
  , d_lineNr(1) {}

JSONLexerBase::Input::Input(std::istream* iStream, size_t lineNr)
  : d_in(iStream)
  , d_lineNr(lineNr) {}

size_t
JSONLexerBase::Input::get() {
    switch (size_t ch = next()) // get the next input char
    {
        case '\n':
            ++d_lineNr;
            [[fallthrough]];

        default:
            return ch;
    }
}

size_t
JSONLexerBase::Input::next() {
    size_t ch;

    if (d_deque.empty()) // deque empty: next char fm d_in
    {
        if (d_in == 0)
            return AT_EOF;
        ch = d_in->get();
        return *d_in ? ch : static_cast<size_t>(AT_EOF);
    }

    ch = d_deque.front();
    d_deque.pop_front();

    return ch;
}

void
JSONLexerBase::Input::reRead(size_t ch) {
    if (ch < 0x100) {
        if (ch == '\n')
            --d_lineNr;
        d_deque.push_front(ch);
    }
}

void
JSONLexerBase::Input::reRead(std::string const& str, size_t fm) {
    for (size_t idx = str.size(); idx-- > fm;)
        reRead(str[idx]);
}

JSONLexerBase::JSONLexerBase(std::istream& in, std::ostream& out)
  : d_filename("-")
  , d_out(new std::ostream(out.rdbuf()))
  ,
  // $insert interactiveInit
  d_in(0)
  , d_input(new std::istream(in.rdbuf()))
  , d_dfaBase_(s_dfa_) {}

void
JSONLexerBase::switchStream_(std::istream& in, size_t lineNr) {
    d_input.close();
    d_input = Input(new std::istream(in.rdbuf()), lineNr);
}

JSONLexerBase::JSONLexerBase(std::string const& infilename, std::string const& outfilename)
  : d_filename(infilename)
  , d_out(outfilename == "-" ? new std::ostream(std::cout.rdbuf())
                             : outfilename == "" ? new std::ostream(std::cerr.rdbuf())
                                                 : new std::ofstream(outfilename))
  , d_input(new std::ifstream(infilename))
  , d_dfaBase_(s_dfa_) {}

void
JSONLexerBase::switchStreams(std::istream& in, std::ostream& out) {
    switchStream_(in, 1);
    switchOstream(out);
}

void
JSONLexerBase::switchOstream(std::ostream& out) {
    *d_out << std::flush;
    d_out.reset(new std::ostream(out.rdbuf()));
}

// $insert debugFunctions
void
JSONLexerBase::setDebug(bool onOff) {}

bool
JSONLexerBase::debug() const {
    return false;
}

void
JSONLexerBase::redo(size_t nChars) {
    size_t from = nChars >= length() ? 0 : length() - nChars;
    d_input.reRead(d_matched, from);
    d_matched.resize(from);
}

void
JSONLexerBase::switchOstream(std::string const& outfilename) {
    *d_out << std::flush;
    d_out.reset(outfilename == "-" ? new std::ostream(std::cout.rdbuf())
                                   : outfilename == "" ? new std::ostream(std::cerr.rdbuf())
                                                       : new std::ofstream(outfilename));
}

void
JSONLexerBase::switchIstream(std::string const& infilename) {
    d_input.close();
    d_filename = infilename;
    d_input = Input(new std::ifstream(infilename));
    d_atBOL = true;
}

void
JSONLexerBase::switchStreams(std::string const& infilename, std::string const& outfilename) {
    switchOstream(outfilename);
    switchIstream(infilename);
}

void
JSONLexerBase::pushStream(std::istream& istr) {
    std::istream* streamPtr = new std::istream(istr.rdbuf());
    p_pushStream("(istream)", streamPtr);
}

void
JSONLexerBase::pushStream(std::string const& name) {
    std::istream* streamPtr = new std::ifstream(name);
    if (!*streamPtr) {
        delete streamPtr;
        throw std::runtime_error("Cannot read " + name);
    }
    p_pushStream(name, streamPtr);
}

void
JSONLexerBase::p_pushStream(std::string const& name, std::istream* streamPtr) {
    if (d_streamStack.size() == s_maxSizeofStreamStack_) {
        delete streamPtr;
        throw std::length_error("Max stream stack size exceeded");
    }

    d_streamStack.push_back(StreamStruct{ d_filename, d_input });
    d_filename = name;
    d_input = Input(streamPtr);
    d_atBOL = true;
}

bool
JSONLexerBase::popStream() {
    d_input.close();

    if (d_streamStack.empty())
        return false;

    StreamStruct& top = d_streamStack.back();

    d_input = top.pushedInput;
    d_filename = top.pushedName;
    d_streamStack.pop_back();

    return true;
}

// See the manual's section `Run-time operations' section for an explanation
// of this member.
JSONLexerBase::ActionType_
JSONLexerBase::actionType_(size_t range) {
    d_nextState = d_dfaBase_[d_state][range];

    if (d_nextState != -1) // transition is possible
        return ActionType_::CONTINUE;

    if (knownFinalState()) // FINAL state reached
        return ActionType_::MATCH;

    if (d_matched.size())
        return ActionType_::ECHO_FIRST; // no match, echo the 1st char

    return range != s_rangeOfEOF_ ? ActionType_::ECHO_CH : ActionType_::RETURN;
}

void
JSONLexerBase::accept(size_t nChars) // old name: less
{
    if (nChars < d_matched.size()) {
        d_input.reRead(d_matched, nChars);
        d_matched.resize(nChars);
    }
}

void
JSONLexerBase::setMatchedSize(size_t length) {
    d_input.reRead(d_matched, length); // reread the tail section
    d_matched.resize(length);          // return what's left
}

// At this point a rule has been matched.  The next character is not part of
// the matched rule and is sent back to the input.  The final match length
// is determined, the index of the matched rule is determined, and then
// d_atBOL is updated. Finally the rule's index is returned.
// The numbers behind the finalPtr assignments are explained in the
// manual's `Run-time operations' section.
size_t
JSONLexerBase::matched_(size_t ch) {
    d_input.reRead(ch);

    FinalData* finalPtr;

    if (not d_atBOL)             // not at BOL
        finalPtr = &d_final.std; // then use the std rule (3, 4)

    // at BOL
    else if (not available(d_final.std.rule)) // only a BOL rule avail.
        finalPtr = &d_final.bol;              // use the BOL rule (6)

    else if (not available(d_final.bol.rule)) // only a std rule is avail.
        finalPtr = &d_final.std;              // use the std rule (7)

    else if (               // Both are available (8)
      d_final.bol.length != // check lengths of matched texts
      d_final.std.length    // unequal lengths, use the rule
      )                     // having the longer match length
        finalPtr = d_final.bol.length > d_final.std.length ? &d_final.bol : &d_final.std;

    else // lengths are equal: use 1st rule
        finalPtr = d_final.bol.rule < d_final.std.rule ? &d_final.bol : &d_final.std;

    setMatchedSize(finalPtr->length);

    d_atBOL = d_matched.back() == '\n';

    return finalPtr->rule;
}

size_t
JSONLexerBase::getRange_(int ch) // using int to prevent casts
{
    return ch == AT_EOF ? as<size_t>(s_rangeOfEOF_) : s_ranges_[ch];
}

// At this point d_nextState contains the next state and continuation is
// possible. The just read char. is appended to d_match
void
JSONLexerBase::continue_(int ch) {
    d_state = d_nextState;

    if (ch != AT_EOF)
        d_matched += ch;
}

void
JSONLexerBase::echoCh_(size_t ch) {
    *d_out << as<char>(ch);
    d_atBOL = ch == '\n';
}

// At this point there is no continuation. The last character is
// pushed back into the input stream as well as all but the first char. in
// the buffer. The first char. in the buffer is echoed to stderr.
// If there isn't any 1st char yet then the current char doesn't fit any
// rules and that char is then echoed
void
JSONLexerBase::echoFirst_(size_t ch) {
    d_input.reRead(ch);
    d_input.reRead(d_matched, 1);
    echoCh_(d_matched[0]);
}

// Update the rules associated with the current state, do this separately
// for BOL and std rules.
// If a rule was set, update the rule index and the current d_matched
// length.
void
JSONLexerBase::updateFinals_() {
    size_t len = d_matched.size();

    int const* rf = d_dfaBase_[d_state] + s_finIdx_;

    if (rf[0] != -1) // update to the latest std rule
    {
        d_final.std = FinalData{ as<size_t>(rf[0]), len };
    }

    if (rf[1] != -1) // update to the latest bol rule
    {
        d_final.bol = FinalData{ as<size_t>(rf[1]), len };
    }
}

void
JSONLexerBase::reset_() {
    d_final = Final{ FinalData{ s_unavailable, 0 }, FinalData{ s_unavailable, 0 } };

    d_state = 0;
    d_return = true;

    if (!d_more)
        d_matched.clear();

    d_more = false;
}

int
JSONLexer::executeAction_(size_t ruleIdx) try {
    switch (ruleIdx) {
        // $insert actions
        case 1: {
            return 258;
        } break;
        case 2: {
            return 258;
        } break;
        case 3: {
            return 261;
        } break;
        case 4: {
            return 261;
        } break;
        case 5: {
            return 262;
        } break;
        case 6: {
            return 264;
        } break;
        case 7: {
            return 265;
        } break;
        case 8: {
            return 266;
        } break;
        case 9: {
            return 267;
        } break;
        case 10: {
            return 268;
        } break;
        case 11: {
            return 269;
        } break;
        case 12: {
            {
                more();
                begin(StartCondition_::number);
            }
        } break;
        case 13: {
            {
                begin(StartCondition_::string);
            }
        } break;
        case 14: {
            {
                begin(StartCondition_::string_single);
            }
        } break;
        case 15: {
            {
                begin(StartCondition_::regexp);
            }
        } break;
        case 16: {
            {
                begin(StartCondition_::INITIAL);
                if (matched().find(".") != std::string::npos ||
                    matched().find("e+") != std::string::npos) {
                    return 260;
                }
                else {
                    return 259;
                }
            }
        } break;
        case 17: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                setMatched(_out);
                begin(StartCondition_::INITIAL);
                return 257;
            }
        } break;
        case 18: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                setMatched(_out);
                more();
                d_intermediate_state = StartCondition_::string;
                begin(StartCondition_::escaped);
            }
        } break;
        case 19: {
            {
                more();
            }
        } break;
        case 20: {
            {

                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                setMatched(_out);
                begin(StartCondition_::INITIAL);
                return 257;
            }
        } break;
        case 21: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                setMatched(_out);
                more();
                d_intermediate_state = StartCondition_::string_single;
                begin(StartCondition_::escaped);
            }
        } break;
        case 22: {
            {
                more();
            }
        } break;
        case 23: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                setMatched(_out);
                begin(StartCondition_::INITIAL);
                return 263;
            }
        } break;
        case 24: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                setMatched(_out);
                more();
                d_intermediate_state = StartCondition_::regexp;
                begin(StartCondition_::escaped);
            }
        } break;
        case 25: {
            {
                more();
            }
        } break;
        case 26: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                _out.insert(_out.length(), "\n");
                setMatched(_out);
                more();
                begin(d_intermediate_state);
            }
        } break;
        case 27: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                _out.insert(_out.length(), "\t");
                setMatched(_out);
                more();
                begin(d_intermediate_state);
            }
        } break;
        case 28: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                _out.insert(_out.length(), "\r");
                setMatched(_out);
                more();
                begin(d_intermediate_state);
            }
        } break;
        case 29: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                _out.insert(_out.length(), "\f");
                setMatched(_out);
                more();
                begin(d_intermediate_state);
            }
        } break;
        case 30: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                setMatched(_out);
                more();
                begin(StartCondition_::unicode);
            }
        } break;
        case 31: {
            {
                std::string _out(matched());
                _out.erase(_out.length() - 1, 1);
                _out.insert(_out.length(), "\\");
                setMatched(_out);
                more();
                begin(d_intermediate_state);
            }
        } break;
        case 32: {
            {
                more();
                begin(d_intermediate_state);
            }
        } break;
        case 33: {
            {
                std::string _out(matched());

                std::stringstream ss;
                ss << _out[_out.length() - 4] << _out[_out.length() - 3] << _out[_out.length() - 2]
                   << _out[_out.length() - 1];
                int c;
                ss >> std::hex >> c;

                wchar_t w = (wchar_t)c;
                std::string dest("");

                if (w <= 0x7f) {
                    dest.insert(dest.begin(), w);
                }
                else if (w <= 0x7ff) {
                    dest.insert(dest.end(), 0xc0 | ((w >> 6) & 0x1f));
                    dest.insert(dest.end(), 0x80 | (w & 0x3f));
                }
                else if (w <= 0xffff) {
                    dest.insert(dest.end(), 0xe0 | ((w >> 12) & 0x0f));
                    dest.insert(dest.end(), 0x80 | ((w >> 6) & 0x3f));
                    dest.insert(dest.end(), 0x80 | (w & 0x3f));
                }
                else if (w <= 0x10ffff) {
                    dest.insert(dest.end(), 0xf0 | ((w >> 18) & 0x07));
                    dest.insert(dest.end(), 0x80 | ((w >> 12) & 0x3f));
                    dest.insert(dest.end(), 0x80 | ((w >> 6) & 0x3f));
                    dest.insert(dest.end(), 0x80 | (w & 0x3f));
                }
                else {
                    dest.insert(dest.end(), '?');
                }

                _out.assign(_out.substr(0, _out.length() - 4));
                _out.insert(_out.length(), dest);
                setMatched(_out);
                more();

                begin(d_intermediate_state);
            }
        } break;
    }
    noReturn_();
    return 0;
}
catch (Leave_ value) {
    return static_cast<int>(value);
}

int
JSONLexer::lex_() {
    reset_();
    preCode();

    while (true) {
        size_t ch = get_();           // fetch next char
        size_t range = getRange_(ch); // determine the range

        updateFinals_(); // update the state's Final info

        switch (actionType_(range)) // determine the action
        {
            case ActionType_::CONTINUE:
                continue_(ch);
                continue;

            case ActionType_::MATCH: {
                d_token_ = executeAction_(matched_(ch));
                if (return_()) {
                    print();
                    postCode(PostEnum_::RETURN);
                    return d_token_;
                }
                break;
            }

            case ActionType_::ECHO_FIRST:
                echoFirst_(ch);
                break;

            case ActionType_::ECHO_CH:
                echoCh_(ch);
                break;

            case ActionType_::RETURN:
                if (!popStream()) {
                    postCode(PostEnum_::END);
                    return 0;
                }
                postCode(PostEnum_::POP);
                continue;
        } // switch

        postCode(PostEnum_::WIP);

        reset_();
        preCode();
    } // while
}

void
JSONLexerBase::print_() const {}

// $insert namespace-close
}
