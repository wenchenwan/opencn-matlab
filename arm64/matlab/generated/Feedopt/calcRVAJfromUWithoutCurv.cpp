//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcRVAJfromUWithoutCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "calcRVAJfromUWithoutCurv.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &r2D
//                const ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r1D
//                const ::coder::array<double, 2U> &udd_vec
// Return Type  : void
//
namespace ocn {
void binary_expand_op(::coder::array<double, 2U> &A, const ::coder::array<double, 2U> &r2D,
                      const ::coder::array<double, 2U> &r, const ::coder::array<double, 2U> &r1D,
                      const ::coder::array<double, 2U> &udd_vec)
{
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int aux_3_1;
    int i;
    int i1;
    int i2;
    int i3;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_1;
    int stride_2_0;
    int stride_2_1;
    int stride_3_1;
    if (r1D.size(0) == 1) {
        i = r2D.size(0);
    } else {
        i = r1D.size(0);
    }
    if (udd_vec.size(1) == 1) {
        i1 = r1D.size(1);
    } else {
        i1 = udd_vec.size(1);
    }
    if (i1 == 1) {
        if (r.size(1) == 1) {
            i2 = r2D.size(1);
        } else {
            i2 = r.size(1);
        }
    } else if (udd_vec.size(1) == 1) {
        i2 = r1D.size(1);
    } else {
        i2 = udd_vec.size(1);
    }
    A.set_size(i, i2);
    stride_0_0 = (r2D.size(0) != 1);
    stride_0_1 = (r2D.size(1) != 1);
    stride_1_1 = (r.size(1) != 1);
    stride_2_0 = (r1D.size(0) != 1);
    stride_2_1 = (r1D.size(1) != 1);
    stride_3_1 = (udd_vec.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    aux_3_1 = 0;
    if (udd_vec.size(1) == 1) {
        i3 = r1D.size(1);
    } else {
        i3 = udd_vec.size(1);
    }
    if (i3 == 1) {
        if (r.size(1) == 1) {
            loop_ub = r2D.size(1);
        } else {
            loop_ub = r.size(1);
        }
    } else if (udd_vec.size(1) == 1) {
        loop_ub = r1D.size(1);
    } else {
        loop_ub = udd_vec.size(1);
    }
    for (int i4{0}; i4 < loop_ub; i4++) {
        int b_loop_ub;
        if (r1D.size(0) == 1) {
            b_loop_ub = r2D.size(0);
        } else {
            b_loop_ub = r1D.size(0);
        }
        for (int i5{0}; i5 < b_loop_ub; i5++) {
            A[i5 + A.size(0) * i4] =
                r2D[i5 * stride_0_0 + r2D.size(0) * aux_0_1] * r[aux_1_1] +
                r1D[i5 * stride_2_0 + r1D.size(0) * aux_2_1] * udd_vec[aux_3_1];
        }
        aux_3_1 += stride_3_1;
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &J
//                const ::coder::array<double, 2U> &r3D
//                const ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r2D
//                const ::coder::array<double, 2U> &ud
//                const ::coder::array<double, 2U> &udd_vec
//                const ::coder::array<double, 2U> &r1D
//                double jps
//                const unsigned int r1[2]
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &J, const ::coder::array<double, 2U> &r3D,
                      const ::coder::array<double, 2U> &r, const ::coder::array<double, 2U> &r2D,
                      const ::coder::array<double, 2U> &ud,
                      const ::coder::array<double, 2U> &udd_vec,
                      const ::coder::array<double, 2U> &r1D, double jps, const unsigned int r1[2])
{
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int aux_3_1;
    int aux_4_1;
    int aux_5_1;
    int b_unnamed_idx_1;
    int c_unnamed_idx_1;
    int d_unnamed_idx_1;
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_1;
    int stride_2_0;
    int stride_2_1;
    int stride_3_1;
    int stride_4_1;
    int stride_5_0;
    int stride_5_1;
    int unnamed_idx_1;
    unnamed_idx_1 = static_cast<int>(r1[1]);
    if (r1D.size(0) == 1) {
        if (r2D.size(0) == 1) {
            i = r3D.size(0);
        } else {
            i = r2D.size(0);
        }
    } else {
        i = r1D.size(0);
    }
    if (unnamed_idx_1 == 1) {
        b_unnamed_idx_1 = r1D.size(1);
    } else {
        b_unnamed_idx_1 = unnamed_idx_1;
    }
    if (udd_vec.size(1) == 1) {
        if (ud.size(1) == 1) {
            i1 = r2D.size(1);
        } else {
            i1 = ud.size(1);
        }
    } else {
        i1 = udd_vec.size(1);
    }
    if (b_unnamed_idx_1 == 1) {
        if (i1 == 1) {
            if (r.size(1) == 1) {
                c_unnamed_idx_1 = r3D.size(1);
            } else {
                c_unnamed_idx_1 = r.size(1);
            }
        } else if (udd_vec.size(1) == 1) {
            if (ud.size(1) == 1) {
                c_unnamed_idx_1 = r2D.size(1);
            } else {
                c_unnamed_idx_1 = ud.size(1);
            }
        } else {
            c_unnamed_idx_1 = udd_vec.size(1);
        }
    } else if (unnamed_idx_1 == 1) {
        c_unnamed_idx_1 = r1D.size(1);
    } else {
        c_unnamed_idx_1 = unnamed_idx_1;
    }
    J.set_size(i, c_unnamed_idx_1);
    stride_0_0 = (r3D.size(0) != 1);
    stride_0_1 = (r3D.size(1) != 1);
    stride_1_1 = (r.size(1) != 1);
    stride_2_0 = (r2D.size(0) != 1);
    stride_2_1 = (r2D.size(1) != 1);
    stride_3_1 = (ud.size(1) != 1);
    stride_4_1 = (udd_vec.size(1) != 1);
    stride_5_0 = (r1D.size(0) != 1);
    stride_5_1 = (r1D.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    aux_3_1 = 0;
    aux_4_1 = 0;
    aux_5_1 = 0;
    if (unnamed_idx_1 == 1) {
        d_unnamed_idx_1 = r1D.size(1);
    } else {
        d_unnamed_idx_1 = unnamed_idx_1;
    }
    if (d_unnamed_idx_1 == 1) {
        int i2;
        if (udd_vec.size(1) == 1) {
            if (ud.size(1) == 1) {
                i2 = r2D.size(1);
            } else {
                i2 = ud.size(1);
            }
        } else {
            i2 = udd_vec.size(1);
        }
        if (i2 == 1) {
            if (r.size(1) == 1) {
                loop_ub = r3D.size(1);
            } else {
                loop_ub = r.size(1);
            }
        } else if (udd_vec.size(1) == 1) {
            if (ud.size(1) == 1) {
                loop_ub = r2D.size(1);
            } else {
                loop_ub = ud.size(1);
            }
        } else {
            loop_ub = udd_vec.size(1);
        }
    } else if (unnamed_idx_1 == 1) {
        loop_ub = r1D.size(1);
    } else {
        loop_ub = unnamed_idx_1;
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
        int b_loop_ub;
        if (r1D.size(0) == 1) {
            if (r2D.size(0) == 1) {
                b_loop_ub = r3D.size(0);
            } else {
                b_loop_ub = r2D.size(0);
            }
        } else {
            b_loop_ub = r1D.size(0);
        }
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            J[i4 + J.size(0) * i3] = (r3D[i4 * stride_0_0 + r3D.size(0) * aux_0_1] * r[aux_1_1] +
                                      3.0 * r2D[i4 * stride_2_0 + r2D.size(0) * aux_2_1] *
                                          ud[aux_3_1] * udd_vec[aux_4_1]) +
                                     r1D[i4 * stride_5_0 + r1D.size(0) * aux_5_1] * jps;
        }
        aux_5_1 += stride_5_1;
        aux_4_1 += stride_4_1;
        aux_3_1 += stride_3_1;
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

} // namespace ocn

//
// File trailer for calcRVAJfromUWithoutCurv.cpp
//
// [EOF]
//
