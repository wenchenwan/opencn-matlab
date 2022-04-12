//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalPosition.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:51:01
//

// Include Files
#include "EvalPosition.h"
#include "EvalBSplineNoCtx.h"
#include "EvalHelix.h"
#include "EvalLine.h"
#include "EvalTransP5.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"
#include <stdio.h>

// Function Definitions
//
// function r0D = EvalPosition(Curv, Spline, u)
//
// Arguments    : const CurvStruct *Curv
//                const CurvStruct *Spline
//                double u
//                double r0D[3]
// Return Type  : void
//
namespace ocn {
void EvalPosition(const CurvStruct *Curv, const CurvStruct *Spline, double u, double r0D[3])
{
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double u_vec;
    double u_vec_tilda;
    char message[30];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'EvalPosition:2' coder.inline("never");
    // 'EvalPosition:3' coder.varsize('r0D', [3, 1], [0,0]);
    // 'EvalPosition:4' r0D = EvalCurvStructNoCtx(Curv, Spline ,u(1));
    u_vec = u;
    // 'EvalCurvStructNoCtx:2' if any(u_vec > 1.0)
    if (u > 1.0) {
        // 'EvalCurvStructNoCtx:3' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:5' else
        // 'EvalCurvStructNoCtx:6' fprintf('EvalCurvStruct: u_vec > 1\n');
        printf("EvalCurvStruct: u_vec > 1\n");
        fflush(stdout);
        // 'EvalCurvStructNoCtx:8' u_vec(u_vec > 1.0) = 1.0;
        u_vec = 1.0;
    }
    // 'EvalCurvStructNoCtx:11' if any(u_vec < 0.0)
    if (u_vec < 0.0) {
        // 'EvalCurvStructNoCtx:12' fprintf('EvalCurvStruct: u_vec < 0\n');
        printf("EvalCurvStruct: u_vec < 0\n");
        fflush(stdout);
        // 'EvalCurvStructNoCtx:13' u_vec(u_vec < 0.0) = 0.0;
        u_vec = 0.0;
    }
    //
    // 'EvalCurvStructNoCtx:17' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStructNoCtx:19' N = numel(u_vec);
    // 'EvalCurvStructNoCtx:20' r0D = zeros(3, N);
    r0D[0] = 0.0;
    r0D[1] = 0.0;
    r0D[2] = 0.0;
    // 'EvalCurvStructNoCtx:21' r1D = zeros(3, N);
    // 'EvalCurvStructNoCtx:22' r2D = zeros(3, N);
    // 'EvalCurvStructNoCtx:23' r3D = zeros(3, N);
    // 'EvalCurvStructNoCtx:25' a=CurvStruct.a_param;
    // 'EvalCurvStructNoCtx:26' b=CurvStruct.b_param;
    // 'EvalCurvStructNoCtx:28' u_vec_tilda = a*u_vec+b;
    u_vec_tilda = Curv->a_param * u_vec + Curv->b_param;
    // 'EvalCurvStructNoCtx:30' switch Type
    switch (Curv->Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:31' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStructNoCtx:32' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(Curv->P0, Curv->P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStructNoCtx:33' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:34' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(Curv->P0, Curv->CorrectedHelixCenter, Curv->evec, Curv->theta, Curv->pitch,
                  u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:35' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStructNoCtx:36' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(Curv->CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStructNoCtx:37' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStructNoCtx:38' [r0D, r1D, r2D, r3D] = EvalBSplineNoCtx(CurvSpline,
        // u_vec_tilda);
        EvalBSplineNoCtx(Spline->sp.CoeffX, Spline->sp.CoeffY, Spline->sp.CoeffZ,
                         Spline->sp.Bl.handle, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        // 'EvalCurvStructNoCtx:39' otherwise
        // 'EvalCurvStructNoCtx:40' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStructNoCtx:43' r1D = a.*r1D;
    // 'EvalCurvStructNoCtx:44' r2D = a^2.*r2D;
    // 'EvalCurvStructNoCtx:45' r3D = a^3.*r3D;
}

} // namespace ocn

//
// File trailer for EvalPosition.cpp
//
// [EOF]
//
