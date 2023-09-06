//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrSplineType.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 13:36:32
//

// Include Files
#include "constrSplineType.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function [ C ] = constrSplineType( ~ )
//
// constrSplineType : Constructs a constrSpline with default values.
//
// Arguments    : double a__1
//                SplineStruct *C
// Return Type  : void
//
namespace ocn {
void constrSplineType(double, SplineStruct *C)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrSplineType:4' if( nargin > 0 )
    // 'constrSplineType:5' [ params ] = paramsDefaultSpline( StructTypeName.MEX );
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
    C->Bl.ncoeff = 0;
    C->Bl.breakpoints.set_size(1, 1);
    C->Bl.breakpoints[0] = 0.0;
    C->Bl.handle = 0UL;
    C->Bl.order = 0;
    C->coeff.set_size(1, 1);
    C->coeff[0] = 0.0;
    C->knots.set_size(1, 1);
    C->knots[0] = 0.0;
    C->Ltot = 0.0;
    C->Lk.set_size(1, 1);
    C->Lk[0] = 0.0;
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
}

} // namespace ocn

//
// File trailer for constrSplineType.cpp
//
// [EOF]
//
