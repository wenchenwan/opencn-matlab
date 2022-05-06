//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: paramsDefaultCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 06-May-2022 16:42:15
//

// Include Files
#include "paramsDefaultCurv.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function [ params ] = paramsDefaultCurv( ~ )
//
// paramsDefaultCurv : Get default params for curv struct.
//
// Arguments    : CurveType *params_gcodeInfoStruct_Type
//                ZSpdMode *params_gcodeInfoStruct_zspdmode
//                bool *params_gcodeInfoStruct_TRAFO
//                bool *params_gcodeInfoStruct_HSC
//                double *params_gcodeInfoStruct_FeedRate
//                double *params_gcodeInfoStruct_SpindleSpeed
//                unsigned long *params_gcodeInfoStruct_gcode_source_line
//                bool *params_gcodeInfoStruct_G91
//                bool *params_gcodeInfoStruct_G91_1
//                int *params_spline_Bl_ncoeff
//                ::coder::array<double, 2U> &params_spline_Bl_breakpoints
//                unsigned long *params_spline_Bl_handle
//                int *params_spline_Bl_order
//                ::coder::array<double, 2U> &params_spline_coeff
//                ::coder::array<double, 2U> &params_spline_knots
//                double *params_spline_Ltot
//                ::coder::array<double, 2U> &params_spline_Lk
//                double params_R0[6]
//                double params_R1[6]
//                double params_Cprim[3]
//                double *params_delta
//                double params_evec[3]
//                double *params_theta
//                double *params_pitch
//                double params_CoeffP5[6]
//                double *params_Coeff
// Return Type  : void
//
namespace ocn {
void paramsDefaultCurv(
    CurveType *params_gcodeInfoStruct_Type, ZSpdMode *params_gcodeInfoStruct_zspdmode,
    bool *params_gcodeInfoStruct_TRAFO, bool *params_gcodeInfoStruct_HSC,
    double *params_gcodeInfoStruct_FeedRate, double *params_gcodeInfoStruct_SpindleSpeed,
    unsigned long *params_gcodeInfoStruct_gcode_source_line, bool *params_gcodeInfoStruct_G91,
    bool *params_gcodeInfoStruct_G91_1, int *params_spline_Bl_ncoeff,
    ::coder::array<double, 2U> &params_spline_Bl_breakpoints,
    unsigned long *params_spline_Bl_handle, int *params_spline_Bl_order,
    ::coder::array<double, 2U> &params_spline_coeff,
    ::coder::array<double, 2U> &params_spline_knots, double *params_spline_Ltot,
    ::coder::array<double, 2U> &params_spline_Lk, double params_R0[6], double params_R1[6],
    double params_Cprim[3], double *params_delta, double params_evec[3], double *params_theta,
    double *params_pitch, double params_CoeffP5[6], double *params_Coeff)
{
    static const unsigned long t0_gcode_source_line{0UL};
    // 'paramsDefaultCurv:3' R0      = zeros( 6, 1 );
    // 'paramsDefaultCurv:4' R1      = zeros( 6, 1 );
    // 'paramsDefaultCurv:5' Cprim   = zeros( 3, 1 );
    // 'paramsDefaultCurv:6' delta   = 0.0;
    // 'paramsDefaultCurv:7' evec    = zeros( 3, 1 );
    params_Cprim[0] = 0.0;
    params_evec[0] = 0.0;
    params_Cprim[1] = 0.0;
    params_evec[1] = 0.0;
    params_Cprim[2] = 0.0;
    params_evec[2] = 0.0;
    // 'paramsDefaultCurv:8' theta   = 0.0;
    // 'paramsDefaultCurv:9' pitch   = 0.0;
    // 'paramsDefaultCurv:10' CoeffP5 = zeros( 1, 6 );
    for (int i{0}; i < 6; i++) {
        params_R0[i] = 0.0;
        params_R1[i] = 0.0;
        params_CoeffP5[i] = 0.0;
    }
    // 'paramsDefaultCurv:11' Coeff   = zeros( 1, 1 );
    // 'paramsDefaultCurv:13' if( coder.target( 'MATLAB' ) && nargin > 0 )
    // 'paramsDefaultCurv:20' else
    // 'paramsDefaultCurv:21' gcodeInfoStruct = constrGcodeInfoStructType;
    // 'paramsDefaultCurv:22' spline          = constrSplineType;
    //  constrSplineType : Constructs a constrSpline with default values.
    // 'constrSplineType:4' if( nargin > 0 )
    // 'constrSplineType:6' else
    // 'constrSplineType:7' [ params ] = paramsDefaultSpline;
    //  paramsDefaultSpline : Get default params for spline.
    // 'paramsDefaultSpline:4' coeff       = zeros( 1, 1 ) ;
    // 'paramsDefaultSpline:5' knots       = zeros( 1, 1 );
    // 'paramsDefaultSpline:7' if( coder.target( 'MATLAB' ) && nargin > 0 )
    // 'paramsDefaultSpline:11' else
    // 'paramsDefaultSpline:12' BlStruct = constrBaseSplineType;
    //  constrBaseSplineType : Constructs a constrBaseSpline with default values.
    // 'constrBaseSplineType:4' if( nargin > 0 )
    // 'constrBaseSplineType:6' else
    // 'constrBaseSplineType:7' [ params ] = paramsDefaultBaseSpline;
    // 'constrBaseSplineType:10' if( coder.target( "MATLAB" ) )
    // 'constrBaseSplineType:12' else
    // 'constrBaseSplineType:13' C = constrBaseSpline( params.ncoeff, params.breakpoints, ...
    // 'constrBaseSplineType:14'         params.handle, params.order );
    //  Construct a struct base spline.
    //
    //  Inputs :
    //  ncoeff       : Number of coefficients
    //  breakpoints  : Number of breakpoints
    //  handle       : Pointer on the structure
    //  degree       : order of the spline
    //
    //  Outputs :
    //  CStrct    : The resulting structure
    // 'constrBaseSpline:14' BaseSplineStrct = struct( 'ncoeff', ncoeff,...
    // 'constrBaseSpline:15'         'breakpoints', breakpoints,...
    // 'constrBaseSpline:16'         'handle', handle,...
    // 'constrBaseSpline:17'         'order', order );
    // 'constrBaseSpline:19' if ~coder.target( 'MATLAB' )
    // 'constrBaseSpline:20' coder.varsize( 'BaseSplineStrct.breakpoints', StructTypeName.dimNBreak{
    // : } ); 'constrBaseSpline:21' coder.cstructname( BaseSplineStrct, StructTypeName.BaseSpline );
    // 'paramsDefaultSpline:15' if( coder.target( 'MATLAB' ) )
    // 'paramsDefaultSpline:17' else
    // 'paramsDefaultSpline:18' params.coeff       = coeff;
    // 'paramsDefaultSpline:19' params.knots       = knots;
    // 'paramsDefaultSpline:20' params.BlStruct    = BlStruct;
    // 'constrSplineType:10' if( coder.target( "MATLAB" ) )
    // 'constrSplineType:12' else
    // 'constrSplineType:13' C = constrSpline( params.coeff, params.knots, params.BlStruct );
    //  Construct a struct for the spline.
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
    // 'constrSpline:15' SplineStrct = struct( ...
    // 'constrSpline:16'                     'Bl', BlStruct,...
    // 'constrSpline:17'                     'coeff', coeff,...
    // 'constrSpline:18'                     'knots', knots,...
    // 'constrSpline:19'                     'Ltot', 0.0, ...
    // 'constrSpline:20'                     'Lk', knots...
    // 'constrSpline:21'                     );
    params_spline_Bl_breakpoints.set_size(1, 1);
    params_spline_Bl_breakpoints[0] = 0.0;
    params_spline_coeff.set_size(1, 1);
    params_spline_coeff[0] = 0.0;
    params_spline_knots.set_size(1, 1);
    params_spline_knots[0] = 0.0;
    params_spline_Lk.set_size(1, 1);
    params_spline_Lk[0] = 0.0;
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
    // 'paramsDefaultCurv:25' if( coder.target( 'MATLAB' ) )
    // 'paramsDefaultCurv:28' else
    // 'paramsDefaultCurv:29' params.gcodeInfoStruct = gcodeInfoStruct;
    // 'paramsDefaultCurv:30' params.spline   = spline;
    // 'paramsDefaultCurv:31' params.R0       = R0;
    // 'paramsDefaultCurv:32' params.R1       = R1;
    // 'paramsDefaultCurv:33' params.Cprim    = Cprim;
    // 'paramsDefaultCurv:34' params.delta    = delta;
    // 'paramsDefaultCurv:35' params.evec     = evec;
    // 'paramsDefaultCurv:36' params.theta    = theta;
    // 'paramsDefaultCurv:37' params.pitch    = pitch;
    // 'paramsDefaultCurv:38' params.CoeffP5  = CoeffP5;
    // 'paramsDefaultCurv:39' params.Coeff    = Coeff;
    *params_gcodeInfoStruct_Type = CurveType_Line;
    *params_gcodeInfoStruct_zspdmode = ZSpdMode_NN;
    *params_gcodeInfoStruct_TRAFO = false;
    *params_gcodeInfoStruct_HSC = false;
    *params_gcodeInfoStruct_FeedRate = 0.0;
    *params_gcodeInfoStruct_SpindleSpeed = 0.0;
    *params_gcodeInfoStruct_gcode_source_line = t0_gcode_source_line;
    *params_gcodeInfoStruct_G91 = false;
    *params_gcodeInfoStruct_G91_1 = true;
    *params_spline_Bl_ncoeff = 0;
    *params_spline_Bl_handle = 0UL;
    *params_spline_Bl_order = 0;
    *params_spline_Ltot = 0.0;
    *params_delta = 0.0;
    *params_theta = 0.0;
    *params_pitch = 0.0;
    *params_Coeff = 0.0;
}

} // namespace ocn

//
// File trailer for paramsDefaultCurv.cpp
//
// [EOF]
//
