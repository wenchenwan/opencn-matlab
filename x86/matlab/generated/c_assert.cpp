//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: c_assert.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "c_assert.h"

// Function Definitions
//
// Arguments    : bool condition
// Return Type  : void
//
namespace ocn {
void b_c_assert(bool condition)
{
    static const char b_message[26]{'u', '2', ' ', 'm', 'u', 's', 't', ' ', 'b',
                                    'e', ' ', 'g', 'r', 'e', 'a', 't', 'e', 'r',
                                    ' ', 't', 'h', 'a', 'n', ' ', 'u', '1'};
    char message[26];
    if (!condition) {
        for (int i{0}; i < 26; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : bool
//
bool c_assert(bool condition)
{
    static const char b_message[16]{'e', ' ', 'c', 'r', 'o', 's', 's', ' ',
                                    'P', '0', 'P', '1', ' ', '=', ' ', '0'};
    char message[16];
    if (!condition) {
        for (int i{0}; i < 16; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
    return condition;
}

//
// Arguments    : bool condition
// Return Type  : void
//
void c_c_assert(bool condition)
{
    static const char b_message[54]{
        'u', '1', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 'g', 'r', 'e', 'a', 't', 'e', 'r',
        ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ', 't', 'h', 'a', 'n', ' ', 't', 'h', 'e',
        ' ', 'f', 'i', 'r', 's', 't', ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};
    char message[54];
    if (!condition) {
        for (int i{0}; i < 54; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : void
//
void d_c_assert(bool condition)
{
    static const char b_message[53]{
        'u', '2', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 's', 'm', 'a', 'l', 'l', 'e', 'r',
        ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ', 't', 'h', 'a', 'n', ' ', 't', 'h', 'e',
        ' ', 'l', 'a', 's', 't', ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};
    char message[53];
    if (!condition) {
        for (int i{0}; i < 53; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : void
//
void e_c_assert(bool condition)
{
    static const char b_message[50]{'C', 'a', 'l', 'c', 'Z', 'e', 'r', 'o', 'S', 't', 'a', 'r', 't',
                                    'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's', ':', ' ',
                                    'C', 'a', 'l', 'l', 'e', 'd', ' ', 'o', 'n', ' ', 'n', 'o', 'n',
                                    '-', 'c', 'o', 'n', 's', 't', ' ', 'j', 'e', 'r', 'k'};
    char message[50];
    if (!condition) {
        for (int i{0}; i < 50; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : void
//
void f_c_assert(bool condition)
{
    static const char b_message[53]{
        'u', '1', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 's', 'm', 'a', 'l', 'l', 'e', 'r',
        ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ', 't', 'h', 'a', 'n', ' ', 't', 'h', 'e',
        ' ', 'l', 'a', 's', 't', ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};
    char message[53];
    if (!condition) {
        for (int i{0}; i < 53; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : void
//
void g_c_assert(bool condition)
{
    static const char b_message[39]{'F', 'e', 'e', 'd', 'o', 'p', 't', 'P', 'l', 'a',
                                    'n', ':', ' ', 'e', 'r', 'r', 'o', 'r', ' ', 'c',
                                    'o', 'd', 'e', ' ', 'w', 'a', 's', ' ', 'n', 'o',
                                    't', ' ', 'h', 'a', 'n', 'd', 'l', 'e', 'd'};
    char message[39];
    if (!condition) {
        for (int i{0}; i < 39; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : void
//
void h_c_assert(bool condition)
{
    static const char b_message[17]{'N', 'o', 't', ' ', 'e', 'n', 'o', 'u', 'g',
                                    'h', ' ', 'p', 'o', 'i', 'n', 't', 's'};
    char message[17];
    if (!condition) {
        for (int i{0}; i < 17; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : void
//
void i_c_assert(bool condition)
{
    static const char b_message[26]{'Z', 'N', ' ', 'i', 's', ' ', 'n', 'o', 't',
                                    ' ', 'u', 's', 'i', 'n', 'g', ' ', 'c', 'o',
                                    'n', 's', 't', ' ', 'j', 'e', 'r', 'k'};
    char message[26];
    if (!condition) {
        for (int i{0}; i < 26; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : void
//
void j_c_assert(bool condition)
{
    static const char b_message[16]{'N', 'N', ' ', 'i', 's', ' ', 'u', 's',
                                    'i', 'n', 'g', ' ', 'j', 'e', 'r', 'k'};
    char message[16];
    if (!condition) {
        for (int i{0}; i < 16; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

//
// Arguments    : bool condition
// Return Type  : void
//
void k_c_assert(bool condition)
{
    static const char b_message[26]{'N', 'Z', ' ', 'i', 's', ' ', 'n', 'o', 't',
                                    ' ', 'u', 's', 'i', 'n', 'g', ' ', 'c', 'o',
                                    'n', 's', 't', ' ', 'j', 'e', 'r', 'k'};
    char message[26];
    if (!condition) {
        for (int i{0}; i < 26; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
    }
}

} // namespace ocn

//
// File trailer for c_assert.cpp
//
// [EOF]
//
