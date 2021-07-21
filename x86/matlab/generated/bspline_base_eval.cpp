//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_base_eval.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "bspline_base_eval.h"
#include "coder_array.h"
#include "src/c_spline.h"

// Function Definitions
//
// Arguments    : int Bl_ncoeff
//                unsigned long Bl_handle
//                const ::coder::array<double, 2U> &xvec
//                ::coder::array<double, 2U> &BasisVal
//                ::coder::array<double, 2U> &BasisValD
//                ::coder::array<double, 2U> &BasisValDD
//                ::coder::array<double, 2U> &BasisValDDD
//                ::coder::array<double, 1U> &BasisIntegr
// Return Type  : void
//
namespace ocn {
void bspline_base_eval(int Bl_ncoeff, unsigned long Bl_handle,
                       const ::coder::array<double, 2U> &xvec, ::coder::array<double, 2U> &BasisVal,
                       ::coder::array<double, 2U> &BasisValD,
                       ::coder::array<double, 2U> &BasisValDD,
                       ::coder::array<double, 2U> &BasisValDDD,
                       ::coder::array<double, 1U> &BasisIntegr)
{
    //  n, bspline_n
    BasisVal.set_size(xvec.size(1), Bl_ncoeff);
    BasisValD.set_size(xvec.size(1), Bl_ncoeff);
    BasisValDD.set_size(xvec.size(1), Bl_ncoeff);
    BasisValDDD.set_size(xvec.size(1), Bl_ncoeff);
    BasisIntegr.set_size(Bl_ncoeff);
    for (int i{0}; i < Bl_ncoeff; i++) {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int loop_ub;
        loop_ub = xvec.size(1);
        for (int i1{0}; i1 < loop_ub; i1++) {
            BasisVal[i1 + BasisVal.size(0) * i] = 0.0;
        }
        b_loop_ub = xvec.size(1);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            BasisValD[i2 + BasisValD.size(0) * i] = 0.0;
        }
        c_loop_ub = xvec.size(1);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            BasisValDD[i3 + BasisValDD.size(0) * i] = 0.0;
        }
        d_loop_ub = xvec.size(1);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            BasisValDDD[i4 + BasisValDDD.size(0) * i] = 0.0;
        }
        BasisIntegr[i] = 0.0;
    }
    c_bspline_base_eval(&Bl_handle, xvec.size(1), &xvec[0], &BasisVal[0], &BasisValD[0],
                        &BasisValDD[0], &BasisValDDD[0], &(BasisIntegr.data())[0]);
    // ,
}

//
// Arguments    : int Bl_ncoeff
//                unsigned long Bl_handle
//                const ::coder::array<double, 2U> &xvec
//                ::coder::array<double, 2U> &BasisVal
//                ::coder::array<double, 2U> &BasisValD
// Return Type  : void
//
void bspline_base_eval(int Bl_ncoeff, unsigned long Bl_handle,
                       const ::coder::array<double, 2U> &xvec, ::coder::array<double, 2U> &BasisVal,
                       ::coder::array<double, 2U> &BasisValD)
{
    ::coder::array<double, 2U> BasisValDD;
    ::coder::array<double, 2U> BasisValDDD;
    ::coder::array<double, 1U> BasisIntegr;
    //  n, bspline_n
    BasisVal.set_size(xvec.size(1), Bl_ncoeff);
    BasisValD.set_size(xvec.size(1), Bl_ncoeff);
    BasisValDD.set_size(xvec.size(1), Bl_ncoeff);
    BasisValDDD.set_size(xvec.size(1), Bl_ncoeff);
    BasisIntegr.set_size(Bl_ncoeff);
    for (int i{0}; i < Bl_ncoeff; i++) {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int loop_ub;
        loop_ub = xvec.size(1);
        for (int i1{0}; i1 < loop_ub; i1++) {
            BasisVal[i1 + BasisVal.size(0) * i] = 0.0;
        }
        b_loop_ub = xvec.size(1);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            BasisValD[i2 + BasisValD.size(0) * i] = 0.0;
        }
        c_loop_ub = xvec.size(1);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            BasisValDD[i3 + BasisValDD.size(0) * i] = 0.0;
        }
        d_loop_ub = xvec.size(1);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            BasisValDDD[i4 + BasisValDDD.size(0) * i] = 0.0;
        }
        BasisIntegr[i] = 0.0;
    }
    c_bspline_base_eval(&Bl_handle, xvec.size(1), &xvec[0], &BasisVal[0], &BasisValD[0],
                        &BasisValDD[0], &BasisValDDD[0], &(BasisIntegr.data())[0]);
    // ,
}

} // namespace ocn

//
// File trailer for bspline_base_eval.cpp
//
// [EOF]
//
