//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "find.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : int Idx2_data[]
//                int Idx2_size[2]
//                const CurvStruct *expl_temp
//                const double u1_tilda_data[]
//                const int u1_tilda_size[2]
// Return Type  : void
//
namespace ocn {
void b_binary_expand_op(int Idx2_data[], int Idx2_size[2], const CurvStruct *expl_temp,
                        const double u1_tilda_data[], const int u1_tilda_size[2])
{
    ::coder::array<bool, 2U> b_expl_temp;
    int b_u1_tilda_size;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (u1_tilda_size[1] == 1) {
        b_u1_tilda_size = expl_temp->sp.knots.size(1);
    } else {
        b_u1_tilda_size = u1_tilda_size[1];
    }
    b_expl_temp.set_size(1, b_u1_tilda_size);
    stride_0_1 = (expl_temp->sp.knots.size(1) != 1);
    stride_1_1 = (u1_tilda_size[1] != 1);
    if (u1_tilda_size[1] == 1) {
        loop_ub = expl_temp->sp.knots.size(1);
    } else {
        loop_ub = u1_tilda_size[1];
    }
    for (int i{0}; i < loop_ub; i++) {
        b_expl_temp[i] = (expl_temp->sp.knots[i * stride_0_1] < u1_tilda_data[i * stride_1_1]);
    }
    coder::b_eml_find(b_expl_temp, Idx2_data, Idx2_size);
}

//
// Arguments    : int Idx2_data[]
//                int Idx2_size[2]
//                const CurvStruct *expl_temp
//                const double u0_tilda_data[]
//                const int u0_tilda_size[2]
// Return Type  : void
//
void binary_expand_op(int Idx2_data[], int Idx2_size[2], const CurvStruct *expl_temp,
                      const double u0_tilda_data[], const int u0_tilda_size[2])
{
    ::coder::array<bool, 2U> b_expl_temp;
    int b_u0_tilda_size;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (u0_tilda_size[1] == 1) {
        b_u0_tilda_size = expl_temp->sp.knots.size(1);
    } else {
        b_u0_tilda_size = u0_tilda_size[1];
    }
    b_expl_temp.set_size(1, b_u0_tilda_size);
    stride_0_1 = (expl_temp->sp.knots.size(1) != 1);
    stride_1_1 = (u0_tilda_size[1] != 1);
    if (u0_tilda_size[1] == 1) {
        loop_ub = expl_temp->sp.knots.size(1);
    } else {
        loop_ub = u0_tilda_size[1];
    }
    for (int i{0}; i < loop_ub; i++) {
        b_expl_temp[i] = (expl_temp->sp.knots[i * stride_0_1] > u0_tilda_data[i * stride_1_1]);
    }
    coder::eml_find(b_expl_temp, Idx2_data, Idx2_size);
}

//
// Arguments    : const ::coder::array<bool, 2U> &x
//                int i_data[]
//                int i_size[2]
// Return Type  : void
//
namespace coder {
void b_eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2])
{
    int idx;
    int ii;
    int k;
    bool exitg1;
    k = (1 <= x.size(1));
    ii = x.size(1);
    idx = 0;
    i_size[0] = 1;
    i_size[1] = k;
    exitg1 = false;
    while ((!exitg1) && (ii > 0)) {
        if (x[ii - 1]) {
            idx = 1;
            i_data[0] = ii;
            exitg1 = true;
        } else {
            ii--;
        }
    }
    if (k == 1) {
        if (idx == 0) {
            i_size[0] = 1;
            i_size[1] = 0;
        }
    } else {
        i_size[1] = (1 <= idx);
    }
}

//
// Arguments    : const bool x_data[]
//                int x_size
//                int i_data[]
//                int *i_size
// Return Type  : void
//
void c_eml_find(const bool x_data[], int x_size, int i_data[], int *i_size)
{
    int idx;
    int ii;
    bool exitg1;
    idx = 0;
    *i_size = x_size;
    ii = 0;
    exitg1 = false;
    while ((!exitg1) && (ii <= x_size - 1)) {
        if (x_data[ii]) {
            idx++;
            i_data[idx - 1] = ii + 1;
            if (idx >= x_size) {
                exitg1 = true;
            } else {
                ii++;
            }
        } else {
            ii++;
        }
    }
    if (x_size == 1) {
        if (idx == 0) {
            *i_size = 0;
        }
    } else if (1 > idx) {
        *i_size = 0;
    } else {
        *i_size = idx;
    }
}

//
// Arguments    : const ::coder::array<bool, 2U> &x
//                int i_data[]
//                int i_size[2]
// Return Type  : void
//
void eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2])
{
    int idx;
    int ii;
    int k;
    bool exitg1;
    k = (1 <= x.size(1));
    idx = 0;
    i_size[0] = 1;
    i_size[1] = k;
    ii = 0;
    exitg1 = false;
    while ((!exitg1) && (ii <= x.size(1) - 1)) {
        if (x[ii]) {
            idx = 1;
            i_data[0] = ii + 1;
            exitg1 = true;
        } else {
            ii++;
        }
    }
    if (k == 1) {
        if (idx == 0) {
            i_size[0] = 1;
            i_size[1] = 0;
        }
    } else {
        i_size[1] = (1 <= idx);
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for find.cpp
//
// [EOF]
//
