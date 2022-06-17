//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrHelixStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

// Include Files
#include "constrHelixStruct.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "opencn_matlab_types31.h"
#include "coder_array.h"

// Function Definitions
//
// function [ CStrct ] = constrHelixStruct( gcodeInfoStruct, R0, R1, Cprim, ...
//                                          delta, evec, theta, pitch )
//
// constrHelixStructFromArcFeed : Construct a Curv struct filled with the
//  parameters of a helix. The resulting helix is the combination of a linear
//  motion along one of the three reference axis ( x, y, z ) with a circular
//  motion in the perpendicular plan ( XY, ZX, YZ ).
//
//  gcodeInfoStruct : struct containing the information from the Gcode
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
void constrHelixStruct(GcodeInfoStruct *gcodeInfoStruct, const double R0[6], const double R1[6],
                       const double Cprim[3], double delta, const double evec[3], double theta,
                       double pitch, CurvStruct *CStrct)
{
    static const uint64m_T r{
        {0U, 0U} // chunks
    };
    SplineStruct expl_temp;
    double dv[6];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrHelixStruct:20' coder.inline( "never" );
    // 'constrHelixStruct:22' gcodeInfoStruct.Type = CurveType.Helix;
    gcodeInfoStruct->Type = CurveType_Helix;
    // 'constrHelixStruct:24' spline  = constrSplineType();
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
    // 'constrHelixStruct:25' CoeffP5 = zeros( 1, 6 );
    // 'constrHelixStruct:26' Coeff   = zeros( 1, 1 );
    // 'constrHelixStruct:28' CStrct = constrCurvStruct( gcodeInfoStruct, spline, R0, R1, Cprim,
    // delta, ... 'constrHelixStruct:29'                             evec, theta, pitch, CoeffP5,
    // Coeff );
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
    expl_temp.Bl.handle = r;
    expl_temp.Bl.order = 0;
    for (int i{0}; i < 6; i++) {
        dv[i] = 0.0;
    }
    c_constrCurvStruct(*gcodeInfoStruct, &expl_temp, R0, R1, Cprim, delta, evec, theta, pitch, dv,
                       CStrct);
}

} // namespace ocn

//
// File trailer for constrHelixStruct.cpp
//
// [EOF]
//
