//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_base_eval.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:48:06
//

// Include Files
#include "bspline_base_eval.h"
#include "opencn_matlab_types11.h"
#include "coder_array.h"
#include "src/c_spline.h"

// Function Definitions
//
// function [BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr] = bspline_base_eval(Bl,
// xvec)
//
// Arguments    : int Bl_ncoeff
//                const uint64m_T Bl_handle
//                const ::coder::array<double, 2U> &xvec
//                ::coder::array<double, 2U> &BasisVal
//                ::coder::array<double, 2U> &BasisValD
// Return Type  : void
//
namespace ocn {
void bspline_base_eval(int Bl_ncoeff, const uint64m_T Bl_handle,
                       const ::coder::array<double, 2U> &xvec, ::coder::array<double, 2U> &BasisVal,
                       ::coder::array<double, 2U> &BasisValD)
{
    ::coder::array<double, 2U> BasisValDD;
    ::coder::array<double, 2U> BasisValDDD;
    ::coder::array<double, 1U> BasisIntegr;
    // 'bspline_base_eval:2' if coder.target('rtw') || coder.target('mex')
    //  n, bspline_n
    // 'bspline_base_eval:4' samples = int32(numel(xvec));
    // 'bspline_base_eval:5' BasisVal = zeros(samples, Bl.ncoeff);
    BasisVal.set_size(xvec.size(1), Bl_ncoeff);
    // 'bspline_base_eval:6' BasisValD = BasisVal;
    BasisValD.set_size(xvec.size(1), Bl_ncoeff);
    // 'bspline_base_eval:7' BasisValDD = BasisVal;
    BasisValDD.set_size(xvec.size(1), Bl_ncoeff);
    // 'bspline_base_eval:8' BasisValDDD = BasisVal;
    BasisValDDD.set_size(xvec.size(1), Bl_ncoeff);
    // 'bspline_base_eval:9' BasisIntegr = BasisVal(1, :)';
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
    // 'bspline_base_eval:11' coder.updateBuildInfo('addSourceFiles','c_spline.c',
    // '$(START_DIR)/src'); 'bspline_base_eval:12' coder.updateBuildInfo('addLinkFlags',
    // LibInfo.gsl.lflags); 'bspline_base_eval:13' coder.cinclude('src/c_spline.h');
    // 'bspline_base_eval:14' coder.ceval('c_bspline_base_eval', coder.rref(Bl.handle), samples,
    // coder.rref(xvec), ..., 'bspline_base_eval:15'             coder.ref(BasisVal),
    // coder.ref(BasisValD), coder.ref(BasisValDD),coder.ref(BasisValDDD),... 'bspline_base_eval:16'
    // coder.ref(BasisIntegr));
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
