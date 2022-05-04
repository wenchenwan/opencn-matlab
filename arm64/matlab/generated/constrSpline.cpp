//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrSpline.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-May-2022 15:12:49
//

// Include Files
#include "constrSpline.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function [ SplineStrct ] = constrSpline( coeff, knots, BlStruct )
//
// Construct a struct for the spline.
//
//  Inputs :
//  BlStruct     : Base Spline structure
//  coeff        : [ NDim x ncoeff ] Coefficient of the spline
//  knots        : Knots of the spline
//  Other fields:
//  Ltot         : Total length of the spline
//  Lk           : Individual length between two knots
//
//  Outputs :
//  SplineStrct    : The resulting structure
//
// Arguments    : const ::coder::array<double, 2U> &coeff
//                const ::coder::array<double, 2U> &knots
//                const BaseSplineStruct *BlStruct
//                SplineStruct *SplineStrct
// Return Type  : void
//
namespace ocn {
void constrSpline(const ::coder::array<double, 2U> &coeff, const ::coder::array<double, 2U> &knots,
                  const BaseSplineStruct *BlStruct, SplineStruct *SplineStrct)
{
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrSpline:15' SplineStrct = struct( ...
    // 'constrSpline:16'                     'Bl', BlStruct,...
    // 'constrSpline:17'                     'coeff', coeff,...
    // 'constrSpline:18'                     'knots', knots,...
    // 'constrSpline:19'                     'Ltot', 0.0, ...
    // 'constrSpline:20'                     'Lk', knots...
    // 'constrSpline:21'                     );
    SplineStrct->Bl = *BlStruct;
    SplineStrct->coeff.set_size(coeff.size(0), coeff.size(1));
    loop_ub = coeff.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = coeff.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            SplineStrct->coeff[i1 + SplineStrct->coeff.size(0) * i] = coeff[i1 + coeff.size(0) * i];
        }
    }
    SplineStrct->knots.set_size(1, knots.size(1));
    c_loop_ub = knots.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        SplineStrct->knots[i2] = knots[i2];
    }
    SplineStrct->Ltot = 0.0;
    SplineStrct->Lk.set_size(1, knots.size(1));
    d_loop_ub = knots.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        SplineStrct->Lk[i3] = knots[i3];
    }
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
}

} // namespace ocn

//
// File trailer for constrSpline.cpp
//
// [EOF]
//
