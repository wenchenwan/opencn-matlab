//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: paramsDefaultCurv.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:17:01
//

// Include Files
#include "paramsDefaultCurv.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types2.h"
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
//                int *params_gcodeInfoStruct_gcode_source_line
//                bool *params_gcodeInfoStruct_G91
//                bool *params_gcodeInfoStruct_G91_1
//                int *params_tool_toolno
//                int *params_tool_pocketno
//                Axes *params_tool_offset
//                double *params_tool_diameter
//                double *params_tool_frontangle
//                double *params_tool_backangle
//                int *params_tool_orientation
//                SplineStruct *params_spline
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
    int *params_gcodeInfoStruct_gcode_source_line, bool *params_gcodeInfoStruct_G91,
    bool *params_gcodeInfoStruct_G91_1, int *params_tool_toolno, int *params_tool_pocketno,
    Axes *params_tool_offset, double *params_tool_diameter, double *params_tool_frontangle,
    double *params_tool_backangle, int *params_tool_orientation, SplineStruct *params_spline,
    double params_R0[6], double params_R1[6], double params_Cprim[3], double *params_delta,
    double params_evec[3], double *params_theta, double *params_pitch, double params_CoeffP5[6],
    double *params_Coeff)
{
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
    // 'paramsDefaultCurv:21' else
    // 'paramsDefaultCurv:22' gcodeInfoStruct = constrGcodeInfoStructType;
    // 'paramsDefaultCurv:23' toolStruct      = constrToolStructType;
    // 'paramsDefaultCurv:24' spline          = constrSplineType;
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
    params_spline->Bl.ncoeff = 0;
    params_spline->Bl.breakpoints.set_size(1, 1);
    params_spline->Bl.breakpoints[0] = 0.0;
    params_spline->Bl.handle = 0UL;
    params_spline->Bl.order = 0;
    params_spline->coeff.set_size(1, 1);
    params_spline->coeff[0] = 0.0;
    params_spline->knots.set_size(1, 1);
    params_spline->knots[0] = 0.0;
    params_spline->Ltot = 0.0;
    params_spline->Lk.set_size(1, 1);
    params_spline->Lk[0] = 0.0;
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
    // 'paramsDefaultCurv:27' if( coder.target( 'MATLAB' ) )
    // 'paramsDefaultCurv:30' else
    // 'paramsDefaultCurv:31' params.gcodeInfoStruct  = gcodeInfoStruct;
    // 'paramsDefaultCurv:32' params.tool             = toolStruct;
    params_tool_offset->x = 0.0;
    params_tool_offset->y = 0.0;
    params_tool_offset->z = 0.0;
    params_tool_offset->a = 0.0;
    params_tool_offset->b = 0.0;
    params_tool_offset->c = 0.0;
    params_tool_offset->u = 0.0;
    params_tool_offset->v = 0.0;
    params_tool_offset->w = 0.0;
    // 'paramsDefaultCurv:33' params.spline           = spline;
    // 'paramsDefaultCurv:34' params.R0               = R0;
    // 'paramsDefaultCurv:35' params.R1               = R1;
    // 'paramsDefaultCurv:36' params.Cprim            = Cprim;
    // 'paramsDefaultCurv:37' params.delta            = delta;
    // 'paramsDefaultCurv:38' params.evec             = evec;
    // 'paramsDefaultCurv:39' params.theta            = theta;
    // 'paramsDefaultCurv:40' params.pitch            = pitch;
    // 'paramsDefaultCurv:41' params.CoeffP5          = CoeffP5;
    // 'paramsDefaultCurv:42' params.Coeff            = Coeff;
    *params_gcodeInfoStruct_Type = CurveType_Line;
    *params_gcodeInfoStruct_zspdmode = ZSpdMode_NN;
    *params_gcodeInfoStruct_TRAFO = false;
    *params_gcodeInfoStruct_HSC = false;
    *params_gcodeInfoStruct_FeedRate = 0.0;
    *params_gcodeInfoStruct_SpindleSpeed = 0.0;
    *params_gcodeInfoStruct_gcode_source_line = 0;
    *params_gcodeInfoStruct_G91 = false;
    *params_gcodeInfoStruct_G91_1 = true;
    *params_tool_toolno = 0;
    *params_tool_pocketno = 0;
    *params_tool_diameter = 0.0;
    *params_tool_frontangle = 0.0;
    *params_tool_backangle = 0.0;
    *params_tool_orientation = 0;
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
