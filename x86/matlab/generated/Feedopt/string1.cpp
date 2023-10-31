
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: string1.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "string1.h"
#include "opencn_matlab_types.h"
#include "coder_bounded_array.h"

// Type Definitions
namespace ocn {
struct cell_wrap_8 {
    ::coder::bounded_array<char, 2142U, 2U> f1;
};

} // namespace ocn

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace ocn {
namespace coder {
void rtString::b_init()
{
    static const char b_cv[19]{'S', 'e', 'c', 'o', 'n', 'd', ' ', 'L', 'P', ' ',
                               'f', 'a', 'i', 'l', 'e', 'd', '.', '.', '.'};
    Value.size[0] = 1;
    Value.size[1] = 19;
    for (int i{0}; i < 19; i++) {
        Value.data[i] = b_cv[i];
    }
}

//
// Arguments    : void
// Return Type  : void
//
void rtString::init()
{
    static const char b_cv[18]{'F', 'i', 'r', 's', 't', ' ', 'L', 'P', ' ',
                               'f', 'a', 'i', 'l', 'e', 'd', '.', '.', '.'};
    Value.size[0] = 1;
    Value.size[1] = 18;
    for (int i{0}; i < 18; i++) {
        Value.data[i] = b_cv[i];
    }
}

//
// Arguments    : Fopt val
// Return Type  : void
//
void rtString::init(Fopt val)
{
    static const char cv2[8]{'C', 'o', 'm', 'p', 'r', 'e', 's', 's'};
    static const char cv5[8]{'F', 'i', 'n', 'i', 's', 'h', 'e', 'd'};
    static const char cv3[6]{'S', 'm', 'o', 'o', 't', 'h'};
    static const char b_cv[5]{'G', 'C', 'o', 'd', 'e'};
    static const char cv1[5]{'C', 'h', 'e', 'c', 'k'};
    static const char cv4[5]{'S', 'p', 'l', 'i', 't'};
    static const Fopt enumVals[8]{Fopt_Init,   Fopt_GCode, Fopt_Check, Fopt_Compress,
                                  Fopt_Smooth, Fopt_Split, Fopt_Opt,   Fopt_Finished};
    ::coder::bounded_array<char, 2142U, 2U> b_f1;
    ::coder::bounded_array<char, 2142U, 2U> c_f1;
    ::coder::bounded_array<char, 2142U, 2U> d_f1;
    ::coder::bounded_array<char, 2142U, 2U> e_f1;
    ::coder::bounded_array<char, 2142U, 2U> f1;
    ::coder::bounded_array<char, 2142U, 2U> f_f1;
    ::coder::bounded_array<char, 2142U, 2U> g_f1;
    ::coder::bounded_array<char, 2142U, 2U> h_f1;
    cell_wrap_8 rv[8];
    int enumIdx;
    int k;
    int loop_ub;
    bool exitg1;
    f1.size[0] = 1;
    f1.size[1] = 4;
    f1.data[0] = 'I';
    f1.data[1] = 'n';
    f1.data[2] = 'i';
    f1.data[3] = 't';
    b_f1.size[0] = 1;
    b_f1.size[1] = 5;
    c_f1.size[0] = 1;
    c_f1.size[1] = 5;
    for (int i{0}; i < 5; i++) {
        b_f1.data[i] = b_cv[i];
        c_f1.data[i] = cv1[i];
    }
    d_f1.size[0] = 1;
    d_f1.size[1] = 8;
    for (int i1{0}; i1 < 8; i1++) {
        d_f1.data[i1] = cv2[i1];
    }
    e_f1.size[0] = 1;
    e_f1.size[1] = 6;
    for (int i2{0}; i2 < 6; i2++) {
        e_f1.data[i2] = cv3[i2];
    }
    f_f1.size[0] = 1;
    f_f1.size[1] = 5;
    for (int i3{0}; i3 < 5; i3++) {
        f_f1.data[i3] = cv4[i3];
    }
    g_f1.size[0] = 1;
    g_f1.size[1] = 3;
    g_f1.data[0] = 'O';
    g_f1.data[1] = 'p';
    g_f1.data[2] = 't';
    h_f1.size[0] = 1;
    h_f1.size[1] = 8;
    for (int i4{0}; i4 < 8; i4++) {
        h_f1.data[i4] = cv5[i4];
    }
    enumIdx = -1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
        if (val == enumVals[k]) {
            enumIdx = k;
            exitg1 = true;
        } else {
            k++;
        }
    }
    rv[0].f1 = f1;
    rv[1].f1 = b_f1;
    rv[2].f1 = c_f1;
    rv[3].f1 = d_f1;
    rv[4].f1 = e_f1;
    rv[5].f1 = f_f1;
    rv[6].f1 = g_f1;
    rv[7].f1 = h_f1;
    Value.size[0] = 1;
    Value.size[1] = rv[enumIdx].f1.size[1];
    loop_ub = rv[enumIdx].f1.size[1];
    for (int i5{0}; i5 < loop_ub; i5++) {
        Value.data[i5] = rv[enumIdx].f1.data[i5];
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for string1.cpp
//
// [EOF]
//
