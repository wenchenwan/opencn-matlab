
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrHelixStruct.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "constrHelixStruct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Function Definitions
//
// function [ CStrct ] = constrHelixStruct( gcodeInfoStruct, tool, R0, R1, ...
//                                         Cprim, delta, evec, theta, pitch )
//
// constrHelixStructFromArcFeed : Construct a Curv struct filled with the
//  parameters of a helix. The resulting helix is the combination of a linear
//  motion along one of the three reference axis ( x, y, z ) with a circular
//  motion in the perpendicular plan ( XY, ZX, YZ ).
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  tool      : Struct containing the information of the tool
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//  Cprim     : Corrected center of the helix
//  rotation  : Number of rotation to realize (positive ; Clockwise |
//              negative ; Counterclockwise | zero ; pure translation)
//  evec      : Unit vector orthogonal to the planned of the projected circle
//  theta     : The rotation angle of the skrew motion
//  pitch     : Travelled distance along the skrew axis
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : ZSpdMode gcodeInfoStruct_zspdmode
//                bool gcodeInfoStruct_TRAFO
//                bool gcodeInfoStruct_HSC
//                double gcodeInfoStruct_FeedRate
//                double gcodeInfoStruct_SpindleSpeed
//                int gcodeInfoStruct_gcode_source_line
//                bool gcodeInfoStruct_G91
//                bool gcodeInfoStruct_G91_1
//                int tool_toolno
//                int tool_pocketno
//                const Axes *tool_offset
//                double tool_diameter
//                double tool_frontangle
//                double tool_backangle
//                int tool_orientation
//                const double R0[6]
//                const double R1[6]
//                const double Cprim[3]
//                double delta
//                const double evec[3]
//                double theta
//                double pitch
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void b_constrHelixStruct(ZSpdMode gcodeInfoStruct_zspdmode, bool gcodeInfoStruct_TRAFO,
                         bool gcodeInfoStruct_HSC, double gcodeInfoStruct_FeedRate,
                         double gcodeInfoStruct_SpindleSpeed, int gcodeInfoStruct_gcode_source_line,
                         bool gcodeInfoStruct_G91, bool gcodeInfoStruct_G91_1, int tool_toolno,
                         int tool_pocketno, const Axes *tool_offset, double tool_diameter,
                         double tool_frontangle, double tool_backangle, int tool_orientation,
                         const double R0[6], const double R1[6], const double Cprim[3],
                         double delta, const double evec[3], double theta, double pitch,
                         CurvStruct *CStrct)
{
    SplineStruct expl_temp;
    b_CurvStruct b_expl_temp;
    int b_loop_ub;
    int c_loop_ub;
    int e_loop_ub;
    int loop_ub;
    // 'constrHelixStruct:21' coder.inline( "never" );
    // 'constrHelixStruct:23' gcodeInfoStruct.Type = CurveType.Helix;
    // 'constrHelixStruct:25' spline  = constrSplineType();
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
    // 'constrHelixStruct:26' CoeffP5 = zeros( 1, 6 );
    // 'constrHelixStruct:27' Coeff   = zeros( 1, 1 );
    // 'constrHelixStruct:29' CStrct = constrCurvStruct( gcodeInfoStruct, tool, spline, R0, R1,
    // Cprim, ... 'constrHelixStruct:30'                             delta,evec, theta, pitch,
    // CoeffP5, Coeff );
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
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
    expl_temp.Lk.set_size(1, 1);
    expl_temp.Lk[0] = 0.0;
    expl_temp.Ltot = 0.0;
    expl_temp.knots.set_size(1, 1);
    expl_temp.knots[0] = 0.0;
    expl_temp.coeff.set_size(1, 1);
    expl_temp.coeff[0] = 0.0;
    expl_temp.Bl.ncoeff = 0;
    expl_temp.Bl.breakpoints.set_size(1, 1);
    expl_temp.Bl.breakpoints[0] = 0.0;
    expl_temp.Bl.handle = 0UL;
    expl_temp.Bl.order = 0;
    d_constrCurvStruct(gcodeInfoStruct_zspdmode, gcodeInfoStruct_TRAFO, gcodeInfoStruct_HSC,
                       gcodeInfoStruct_FeedRate, gcodeInfoStruct_SpindleSpeed,
                       gcodeInfoStruct_gcode_source_line, gcodeInfoStruct_G91,
                       gcodeInfoStruct_G91_1, tool_toolno, tool_pocketno, tool_offset,
                       tool_diameter, tool_frontangle, tool_backangle, tool_orientation, &expl_temp,
                       R0, R1, Cprim, delta, evec, theta, pitch, &b_expl_temp);
    CStrct->Info = b_expl_temp.Info;
    CStrct->tool = b_expl_temp.tool;
    CStrct->sp = b_expl_temp.sp;
    CStrct->R0.set_size(b_expl_temp.R0.size[0]);
    loop_ub = b_expl_temp.R0.size[0];
    for (int i{0}; i < loop_ub; i++) {
        CStrct->R0[i] = b_expl_temp.R0.data[i];
    }
    CStrct->R1.set_size(b_expl_temp.R1.size[0]);
    b_loop_ub = b_expl_temp.R1.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        CStrct->R1[i1] = b_expl_temp.R1.data[i1];
    }
    CStrct->delta = b_expl_temp.delta;
    CStrct->CorrectedHelixCenter[0] = b_expl_temp.CorrectedHelixCenter[0];
    CStrct->evec[0] = b_expl_temp.evec[0];
    CStrct->CorrectedHelixCenter[1] = b_expl_temp.CorrectedHelixCenter[1];
    CStrct->evec[1] = b_expl_temp.evec[1];
    CStrct->CorrectedHelixCenter[2] = b_expl_temp.CorrectedHelixCenter[2];
    CStrct->evec[2] = b_expl_temp.evec[2];
    CStrct->theta = b_expl_temp.theta;
    CStrct->pitch = b_expl_temp.pitch;
    CStrct->CoeffP5.set_size(b_expl_temp.CoeffP5.size(0), b_expl_temp.CoeffP5.size(1));
    c_loop_ub = b_expl_temp.CoeffP5.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = b_expl_temp.CoeffP5.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            CStrct->CoeffP5[i3 + CStrct->CoeffP5.size(0) * i2] =
                b_expl_temp.CoeffP5[i3 + b_expl_temp.CoeffP5.size(0) * i2];
        }
    }
    CStrct->sp_index = b_expl_temp.sp_index;
    CStrct->i_begin_sp = b_expl_temp.i_begin_sp;
    CStrct->i_end_sp = b_expl_temp.i_end_sp;
    CStrct->index_smooth = b_expl_temp.index_smooth;
    CStrct->UseConstJerk = b_expl_temp.UseConstJerk;
    CStrct->ConstJerk = b_expl_temp.ConstJerk;
    CStrct->Coeff.set_size(b_expl_temp.Coeff.size(0));
    e_loop_ub = b_expl_temp.Coeff.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        CStrct->Coeff[i4] = b_expl_temp.Coeff[i4];
    }
    CStrct->a_param = b_expl_temp.a_param;
    CStrct->b_param = b_expl_temp.b_param;
}

//
// function [ CStrct ] = constrHelixStruct( gcodeInfoStruct, tool, R0, R1, ...
//                                         Cprim, delta, evec, theta, pitch )
//
// constrHelixStructFromArcFeed : Construct a Curv struct filled with the
//  parameters of a helix. The resulting helix is the combination of a linear
//  motion along one of the three reference axis ( x, y, z ) with a circular
//  motion in the perpendicular plan ( XY, ZX, YZ ).
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  tool      : Struct containing the information of the tool
//  R0        : Starting pose of the helix P0
//  R1        : Ending pose of the helix P0
//  Cprim     : Corrected center of the helix
//  rotation  : Number of rotation to realize (positive ; Clockwise |
//              negative ; Counterclockwise | zero ; pure translation)
//  evec      : Unit vector orthogonal to the planned of the projected circle
//  theta     : The rotation angle of the skrew motion
//  pitch     : Travelled distance along the skrew axis
//
//  CStrct    : The resulting CurvStruct
//
// Arguments    : GcodeInfoStruct *gcodeInfoStruct
//                const Tool *tool
//                const double R0_data[]
//                const int R0_size[1]
//                const double R1_data[]
//                const int R1_size[1]
//                const double Cprim[3]
//                double delta
//                const double evec[3]
//                double theta
//                double pitch
//                CurvStruct *CStrct
// Return Type  : void
//
void constrHelixStruct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool, const double R0_data[],
                       const int R0_size[1], const double R1_data[], const int R1_size[1],
                       const double Cprim[3], double delta, const double evec[3], double theta,
                       double pitch, CurvStruct *CStrct)
{
    SplineStruct expl_temp;
    b_CurvStruct b_expl_temp;
    double dv[6];
    int b_loop_ub;
    int c_loop_ub;
    int e_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrHelixStruct:21' coder.inline( "never" );
    // 'constrHelixStruct:23' gcodeInfoStruct.Type = CurveType.Helix;
    gcodeInfoStruct->Type = CurveType_Helix;
    // 'constrHelixStruct:25' spline  = constrSplineType();
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
    // 'constrHelixStruct:26' CoeffP5 = zeros( 1, 6 );
    // 'constrHelixStruct:27' Coeff   = zeros( 1, 1 );
    // 'constrHelixStruct:29' CStrct = constrCurvStruct( gcodeInfoStruct, tool, spline, R0, R1,
    // Cprim, ... 'constrHelixStruct:30'                             delta,evec, theta, pitch,
    // CoeffP5, Coeff );
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
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
    expl_temp.Lk.set_size(1, 1);
    expl_temp.Lk[0] = 0.0;
    expl_temp.Ltot = 0.0;
    expl_temp.knots.set_size(1, 1);
    expl_temp.knots[0] = 0.0;
    expl_temp.coeff.set_size(1, 1);
    expl_temp.coeff[0] = 0.0;
    expl_temp.Bl.ncoeff = 0;
    expl_temp.Bl.breakpoints.set_size(1, 1);
    expl_temp.Bl.breakpoints[0] = 0.0;
    expl_temp.Bl.handle = 0UL;
    expl_temp.Bl.order = 0;
    for (int i{0}; i < 6; i++) {
        dv[i] = 0.0;
    }
    c_constrCurvStruct(*gcodeInfoStruct, tool, &expl_temp, R0_data, R0_size[0], R1_data, R1_size[0],
                       Cprim, delta, evec, theta, pitch, dv, &b_expl_temp);
    CStrct->Info = b_expl_temp.Info;
    CStrct->tool = b_expl_temp.tool;
    CStrct->sp = b_expl_temp.sp;
    CStrct->R0.set_size(b_expl_temp.R0.size[0]);
    loop_ub = b_expl_temp.R0.size[0];
    for (int i1{0}; i1 < loop_ub; i1++) {
        CStrct->R0[i1] = b_expl_temp.R0.data[i1];
    }
    CStrct->R1.set_size(b_expl_temp.R1.size[0]);
    b_loop_ub = b_expl_temp.R1.size[0];
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        CStrct->R1[i2] = b_expl_temp.R1.data[i2];
    }
    CStrct->delta = b_expl_temp.delta;
    CStrct->CorrectedHelixCenter[0] = b_expl_temp.CorrectedHelixCenter[0];
    CStrct->evec[0] = b_expl_temp.evec[0];
    CStrct->CorrectedHelixCenter[1] = b_expl_temp.CorrectedHelixCenter[1];
    CStrct->evec[1] = b_expl_temp.evec[1];
    CStrct->CorrectedHelixCenter[2] = b_expl_temp.CorrectedHelixCenter[2];
    CStrct->evec[2] = b_expl_temp.evec[2];
    CStrct->theta = b_expl_temp.theta;
    CStrct->pitch = b_expl_temp.pitch;
    CStrct->CoeffP5.set_size(b_expl_temp.CoeffP5.size(0), b_expl_temp.CoeffP5.size(1));
    c_loop_ub = b_expl_temp.CoeffP5.size(1);
    for (int i3{0}; i3 < c_loop_ub; i3++) {
        int d_loop_ub;
        d_loop_ub = b_expl_temp.CoeffP5.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            CStrct->CoeffP5[i4 + CStrct->CoeffP5.size(0) * i3] =
                b_expl_temp.CoeffP5[i4 + b_expl_temp.CoeffP5.size(0) * i3];
        }
    }
    CStrct->sp_index = b_expl_temp.sp_index;
    CStrct->i_begin_sp = b_expl_temp.i_begin_sp;
    CStrct->i_end_sp = b_expl_temp.i_end_sp;
    CStrct->index_smooth = b_expl_temp.index_smooth;
    CStrct->UseConstJerk = b_expl_temp.UseConstJerk;
    CStrct->ConstJerk = b_expl_temp.ConstJerk;
    CStrct->Coeff.set_size(b_expl_temp.Coeff.size(0));
    e_loop_ub = b_expl_temp.Coeff.size(0);
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        CStrct->Coeff[i5] = b_expl_temp.Coeff[i5];
    }
    CStrct->a_param = b_expl_temp.a_param;
    CStrct->b_param = b_expl_temp.b_param;
}

} // namespace ocn

//
// File trailer for constrHelixStruct.cpp
//
// [EOF]
//
