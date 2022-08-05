//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:02:16
//

// Include Files
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, spline, R0, R1, ...
//                       Cprim, delta, evec, theta, pitch, CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  gcodeInfoStruct  : struct containing the information from the Gcode
//  Inputs :
//  R0        : vector of the pose ( position + orientation ) at starting time
//  R1        : vector of the pose ( position + orientation ) at ending time
//  Cprim     : Corrected center for the circle
//  delta     : Difference between the radii
//  evec      : Unit vector in the linear direction for the helix
//  theta     : Rotation angle of the helix
//  pitch     : Linear step for the helix
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  Ouputs:
//  CStrct    : The resulting structure
//
// Arguments    : CurveType gcodeInfoStruct_Type
//                ZSpdMode gcodeInfoStruct_zspdmode
//                bool gcodeInfoStruct_TRAFO
//                bool gcodeInfoStruct_HSC
//                double gcodeInfoStruct_FeedRate
//                double gcodeInfoStruct_SpindleSpeed
//                int gcodeInfoStruct_gcode_source_line
//                bool gcodeInfoStruct_G91
//                bool gcodeInfoStruct_G91_1
//                int spline_Bl_ncoeff
//                const ::coder::array<double, 2U> &spline_Bl_breakpoints
//                unsigned long spline_Bl_handle
//                int spline_Bl_order
//                const ::coder::array<double, 2U> &spline_coeff
//                const ::coder::array<double, 2U> &spline_knots
//                double spline_Ltot
//                const ::coder::array<double, 2U> &spline_Lk
//                const double R0[6]
//                const double R1[6]
//                const double Cprim[3]
//                const double evec[3]
//                const double CoeffP5[6]
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void b_constrCurvStruct(CurveType gcodeInfoStruct_Type, ZSpdMode gcodeInfoStruct_zspdmode,
                        bool gcodeInfoStruct_TRAFO, bool gcodeInfoStruct_HSC,
                        double gcodeInfoStruct_FeedRate, double gcodeInfoStruct_SpindleSpeed,
                        int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                        bool gcodeInfoStruct_G91_1, int spline_Bl_ncoeff,
                        const ::coder::array<double, 2U> &spline_Bl_breakpoints,
                        unsigned long spline_Bl_handle, int spline_Bl_order,
                        const ::coder::array<double, 2U> &spline_coeff,
                        const ::coder::array<double, 2U> &spline_knots, double spline_Ltot,
                        const ::coder::array<double, 2U> &spline_Lk, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const double CoeffP5[6], CurvStruct *CStrct)
{
    int b_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int loop_ub;
    // 'constrCurvStruct:20' coder.inline("never");
    // 'constrCurvStruct:22' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:23'     'sp', spline,...
    // 'constrCurvStruct:24'     'R0', R0, ...
    // 'constrCurvStruct:25'     'R1', R1, ...
    // 'constrCurvStruct:26'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:27'     'delta', delta, ...
    // 'constrCurvStruct:28'     'evec', evec,...
    // 'constrCurvStruct:29'     'theta', theta,...
    // 'constrCurvStruct:30'     'pitch', pitch,...
    // 'constrCurvStruct:31'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:32'     'sp_index', uint32(1),...
    // 'constrCurvStruct:33'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:34'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:35'     'index_smooth', int32(0),...
    // 'constrCurvStruct:36'     'UseConstJerk', false,...
    // 'constrCurvStruct:37'     'ConstJerk', 0,...
    // 'constrCurvStruct:38'     'Coeff', Coeff,...
    // 'constrCurvStruct:39'     'a_param', 1,...
    // 'constrCurvStruct:40'     'b_param', 0 ...
    // 'constrCurvStruct:41'     );
    CStrct->Info.Type = gcodeInfoStruct_Type;
    CStrct->Info.zspdmode = gcodeInfoStruct_zspdmode;
    CStrct->Info.TRAFO = gcodeInfoStruct_TRAFO;
    CStrct->Info.HSC = gcodeInfoStruct_HSC;
    CStrct->Info.FeedRate = gcodeInfoStruct_FeedRate;
    CStrct->Info.SpindleSpeed = gcodeInfoStruct_SpindleSpeed;
    CStrct->Info.gcode_source_line = gcodeInfoStruct_gcode_source_line;
    CStrct->Info.G91 = gcodeInfoStruct_G91;
    CStrct->Info.G91_1 = gcodeInfoStruct_G91_1;
    CStrct->sp.Bl.ncoeff = spline_Bl_ncoeff;
    CStrct->sp.Bl.breakpoints.set_size(1, spline_Bl_breakpoints.size(1));
    loop_ub = spline_Bl_breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        CStrct->sp.Bl.breakpoints[i] = spline_Bl_breakpoints[i];
    }
    CStrct->sp.Bl.handle = spline_Bl_handle;
    CStrct->sp.Bl.order = spline_Bl_order;
    CStrct->sp.coeff.set_size(spline_coeff.size(0), spline_coeff.size(1));
    b_loop_ub = spline_coeff.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        int c_loop_ub;
        c_loop_ub = spline_coeff.size(0);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            CStrct->sp.coeff[i2 + CStrct->sp.coeff.size(0) * i1] =
                spline_coeff[i2 + spline_coeff.size(0) * i1];
        }
    }
    CStrct->sp.knots.set_size(1, spline_knots.size(1));
    d_loop_ub = spline_knots.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        CStrct->sp.knots[i3] = spline_knots[i3];
    }
    CStrct->sp.Ltot = spline_Ltot;
    CStrct->sp.Lk.set_size(1, spline_Lk.size(1));
    e_loop_ub = spline_Lk.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        CStrct->sp.Lk[i4] = spline_Lk[i4];
    }
    CStrct->delta = 0.0;
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->CorrectedHelixCenter[2] = Cprim[2];
    CStrct->evec[2] = evec[2];
    CStrct->theta = 0.0;
    CStrct->pitch = 0.0;
    CStrct->CoeffP5.set_size(1, 6);
    for (int b_i{0}; b_i < 6; b_i++) {
        CStrct->R0[b_i] = R0[b_i];
        CStrct->R1[b_i] = R1[b_i];
        CStrct->CoeffP5[CStrct->CoeffP5.size(0) * b_i] = CoeffP5[b_i];
    }
    CStrct->sp_index = 1U;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(1);
    CStrct->Coeff[0] = 0.0;
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:43' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:46' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:47' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:48' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:49' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:50' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:51' coder.cstructname( CStrct, StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, spline, R0, R1, ...
//                       Cprim, delta, evec, theta, pitch, CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  gcodeInfoStruct  : struct containing the information from the Gcode
//  Inputs :
//  R0        : vector of the pose ( position + orientation ) at starting time
//  R1        : vector of the pose ( position + orientation ) at ending time
//  Cprim     : Corrected center for the circle
//  delta     : Difference between the radii
//  evec      : Unit vector in the linear direction for the helix
//  theta     : Rotation angle of the helix
//  pitch     : Linear step for the helix
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  Ouputs:
//  CStrct    : The resulting structure
//
// Arguments    : const GcodeInfoStruct gcodeInfoStruct
//                const SplineStruct *spline
//                const double R0[6]
//                const double R1[6]
//                const double Cprim[3]
//                double delta
//                const double evec[3]
//                double theta
//                double pitch
//                const double CoeffP5[6]
//                CurvStruct *CStrct
// Return Type  : void
//
void c_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const SplineStruct *spline,
                        const double R0[6], const double R1[6], const double Cprim[3], double delta,
                        const double evec[3], double theta, double pitch, const double CoeffP5[6],
                        CurvStruct *CStrct)
{
    // 'constrCurvStruct:20' coder.inline("never");
    // 'constrCurvStruct:22' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:23'     'sp', spline,...
    // 'constrCurvStruct:24'     'R0', R0, ...
    // 'constrCurvStruct:25'     'R1', R1, ...
    // 'constrCurvStruct:26'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:27'     'delta', delta, ...
    // 'constrCurvStruct:28'     'evec', evec,...
    // 'constrCurvStruct:29'     'theta', theta,...
    // 'constrCurvStruct:30'     'pitch', pitch,...
    // 'constrCurvStruct:31'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:32'     'sp_index', uint32(1),...
    // 'constrCurvStruct:33'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:34'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:35'     'index_smooth', int32(0),...
    // 'constrCurvStruct:36'     'UseConstJerk', false,...
    // 'constrCurvStruct:37'     'ConstJerk', 0,...
    // 'constrCurvStruct:38'     'Coeff', Coeff,...
    // 'constrCurvStruct:39'     'a_param', 1,...
    // 'constrCurvStruct:40'     'b_param', 0 ...
    // 'constrCurvStruct:41'     );
    CStrct->Info = gcodeInfoStruct;
    CStrct->sp = *spline;
    CStrct->delta = delta;
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->CorrectedHelixCenter[2] = Cprim[2];
    CStrct->evec[2] = evec[2];
    CStrct->theta = theta;
    CStrct->pitch = pitch;
    CStrct->CoeffP5.set_size(1, 6);
    for (int i{0}; i < 6; i++) {
        CStrct->R0[i] = R0[i];
        CStrct->R1[i] = R1[i];
        CStrct->CoeffP5[CStrct->CoeffP5.size(0) * i] = CoeffP5[i];
    }
    CStrct->sp_index = 1U;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(1);
    CStrct->Coeff[0] = 0.0;
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:43' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:46' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:47' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:48' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:49' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:50' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:51' coder.cstructname( CStrct, StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, spline, R0, R1, ...
//                       Cprim, delta, evec, theta, pitch, CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  gcodeInfoStruct  : struct containing the information from the Gcode
//  Inputs :
//  R0        : vector of the pose ( position + orientation ) at starting time
//  R1        : vector of the pose ( position + orientation ) at ending time
//  Cprim     : Corrected center for the circle
//  delta     : Difference between the radii
//  evec      : Unit vector in the linear direction for the helix
//  theta     : Rotation angle of the helix
//  pitch     : Linear step for the helix
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  Ouputs:
//  CStrct    : The resulting structure
//
// Arguments    : const GcodeInfoStruct gcodeInfoStruct
//                int spline_Bl_ncoeff
//                const ::coder::array<double, 2U> &spline_Bl_breakpoints
//                unsigned long spline_Bl_handle
//                int spline_Bl_order
//                const ::coder::array<double, 2U> &spline_coeff
//                const ::coder::array<double, 2U> &spline_knots
//                double spline_Ltot
//                const ::coder::array<double, 2U> &spline_Lk
//                const double R0[6]
//                const double R1[6]
//                const double Cprim[3]
//                const double evec[3]
//                const ::coder::array<double, 2U> &CoeffP5
//                CurvStruct *CStrct
// Return Type  : void
//
void c_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, int spline_Bl_ncoeff,
                        const ::coder::array<double, 2U> &spline_Bl_breakpoints,
                        unsigned long spline_Bl_handle, int spline_Bl_order,
                        const ::coder::array<double, 2U> &spline_coeff,
                        const ::coder::array<double, 2U> &spline_knots, double spline_Ltot,
                        const ::coder::array<double, 2U> &spline_Lk, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct)
{
    int b_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int loop_ub;
    // 'constrCurvStruct:20' coder.inline("never");
    // 'constrCurvStruct:22' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:23'     'sp', spline,...
    // 'constrCurvStruct:24'     'R0', R0, ...
    // 'constrCurvStruct:25'     'R1', R1, ...
    // 'constrCurvStruct:26'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:27'     'delta', delta, ...
    // 'constrCurvStruct:28'     'evec', evec,...
    // 'constrCurvStruct:29'     'theta', theta,...
    // 'constrCurvStruct:30'     'pitch', pitch,...
    // 'constrCurvStruct:31'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:32'     'sp_index', uint32(1),...
    // 'constrCurvStruct:33'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:34'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:35'     'index_smooth', int32(0),...
    // 'constrCurvStruct:36'     'UseConstJerk', false,...
    // 'constrCurvStruct:37'     'ConstJerk', 0,...
    // 'constrCurvStruct:38'     'Coeff', Coeff,...
    // 'constrCurvStruct:39'     'a_param', 1,...
    // 'constrCurvStruct:40'     'b_param', 0 ...
    // 'constrCurvStruct:41'     );
    CStrct->Info = gcodeInfoStruct;
    CStrct->sp.Bl.ncoeff = spline_Bl_ncoeff;
    CStrct->sp.Bl.breakpoints.set_size(1, spline_Bl_breakpoints.size(1));
    loop_ub = spline_Bl_breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        CStrct->sp.Bl.breakpoints[i] = spline_Bl_breakpoints[i];
    }
    CStrct->sp.Bl.handle = spline_Bl_handle;
    CStrct->sp.Bl.order = spline_Bl_order;
    CStrct->sp.coeff.set_size(spline_coeff.size(0), spline_coeff.size(1));
    b_loop_ub = spline_coeff.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        int c_loop_ub;
        c_loop_ub = spline_coeff.size(0);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            CStrct->sp.coeff[i2 + CStrct->sp.coeff.size(0) * i1] =
                spline_coeff[i2 + spline_coeff.size(0) * i1];
        }
    }
    CStrct->sp.knots.set_size(1, spline_knots.size(1));
    d_loop_ub = spline_knots.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        CStrct->sp.knots[i3] = spline_knots[i3];
    }
    CStrct->sp.Ltot = spline_Ltot;
    CStrct->sp.Lk.set_size(1, spline_Lk.size(1));
    e_loop_ub = spline_Lk.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        CStrct->sp.Lk[i4] = spline_Lk[i4];
    }
    CStrct->delta = 0.0;
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->CorrectedHelixCenter[2] = Cprim[2];
    CStrct->evec[2] = evec[2];
    CStrct->theta = 0.0;
    CStrct->pitch = 0.0;
    CStrct->CoeffP5.set_size(CoeffP5.size(0), 6);
    f_loop_ub = CoeffP5.size(0);
    for (int b_i{0}; b_i < 6; b_i++) {
        CStrct->R0[b_i] = R0[b_i];
        CStrct->R1[b_i] = R1[b_i];
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            CStrct->CoeffP5[i5 + CStrct->CoeffP5.size(0) * b_i] =
                CoeffP5[i5 + CoeffP5.size(0) * b_i];
        }
    }
    CStrct->sp_index = 1U;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(1);
    CStrct->Coeff[0] = 0.0;
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:43' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:46' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:47' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:48' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:49' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:50' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:51' coder.cstructname( CStrct, StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, spline, R0, R1, ...
//                       Cprim, delta, evec, theta, pitch, CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  gcodeInfoStruct  : struct containing the information from the Gcode
//  Inputs :
//  R0        : vector of the pose ( position + orientation ) at starting time
//  R1        : vector of the pose ( position + orientation ) at ending time
//  Cprim     : Corrected center for the circle
//  delta     : Difference between the radii
//  evec      : Unit vector in the linear direction for the helix
//  theta     : Rotation angle of the helix
//  pitch     : Linear step for the helix
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  Ouputs:
//  CStrct    : The resulting structure
//
// Arguments    : const GcodeInfoStruct *gcodeInfoStruct
//                const SplineStruct *spline
//                const double R0[6]
//                const double R1[6]
//                const double Cprim[3]
//                double delta
//                const double evec[3]
//                double theta
//                double pitch
//                const ::coder::array<double, 2U> &CoeffP5
//                const ::coder::array<double, 1U> &Coeff
//                CurvStruct *CStrct
// Return Type  : void
//
void constrCurvStruct(const GcodeInfoStruct *gcodeInfoStruct, const SplineStruct *spline,
                      const double R0[6], const double R1[6], const double Cprim[3], double delta,
                      const double evec[3], double theta, double pitch,
                      const ::coder::array<double, 2U> &CoeffP5,
                      const ::coder::array<double, 1U> &Coeff, CurvStruct *CStrct)
{
    int b_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrCurvStruct:20' coder.inline("never");
    // 'constrCurvStruct:22' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:23'     'sp', spline,...
    // 'constrCurvStruct:24'     'R0', R0, ...
    // 'constrCurvStruct:25'     'R1', R1, ...
    // 'constrCurvStruct:26'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:27'     'delta', delta, ...
    // 'constrCurvStruct:28'     'evec', evec,...
    // 'constrCurvStruct:29'     'theta', theta,...
    // 'constrCurvStruct:30'     'pitch', pitch,...
    // 'constrCurvStruct:31'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:32'     'sp_index', uint32(1),...
    // 'constrCurvStruct:33'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:34'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:35'     'index_smooth', int32(0),...
    // 'constrCurvStruct:36'     'UseConstJerk', false,...
    // 'constrCurvStruct:37'     'ConstJerk', 0,...
    // 'constrCurvStruct:38'     'Coeff', Coeff,...
    // 'constrCurvStruct:39'     'a_param', 1,...
    // 'constrCurvStruct:40'     'b_param', 0 ...
    // 'constrCurvStruct:41'     );
    CStrct->Info = *gcodeInfoStruct;
    CStrct->sp = *spline;
    CStrct->delta = delta;
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->CorrectedHelixCenter[2] = Cprim[2];
    CStrct->evec[2] = evec[2];
    CStrct->theta = theta;
    CStrct->pitch = pitch;
    CStrct->CoeffP5.set_size(CoeffP5.size(0), 6);
    loop_ub = CoeffP5.size(0);
    for (int i{0}; i < 6; i++) {
        CStrct->R0[i] = R0[i];
        CStrct->R1[i] = R1[i];
        for (int b_i{0}; b_i < loop_ub; b_i++) {
            CStrct->CoeffP5[b_i + CStrct->CoeffP5.size(0) * i] = CoeffP5[b_i + CoeffP5.size(0) * i];
        }
    }
    CStrct->sp_index = 1U;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(Coeff.size(0));
    b_loop_ub = Coeff.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        CStrct->Coeff[i1] = Coeff[i1];
    }
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:43' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:46' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:47' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:48' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:49' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:50' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:51' coder.cstructname( CStrct, StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, spline, R0, R1, ...
//                       Cprim, delta, evec, theta, pitch, CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  gcodeInfoStruct  : struct containing the information from the Gcode
//  Inputs :
//  R0        : vector of the pose ( position + orientation ) at starting time
//  R1        : vector of the pose ( position + orientation ) at ending time
//  Cprim     : Corrected center for the circle
//  delta     : Difference between the radii
//  evec      : Unit vector in the linear direction for the helix
//  theta     : Rotation angle of the helix
//  pitch     : Linear step for the helix
//  CoeffP5   : Coefficient of the 5th order polynom
//
//  Ouputs:
//  CStrct    : The resulting structure
//
// Arguments    : bool gcodeInfoStruct_TRAFO
//                bool gcodeInfoStruct_HSC
//                double gcodeInfoStruct_FeedRate
//                double gcodeInfoStruct_SpindleSpeed
//                int gcodeInfoStruct_gcode_source_line
//                bool gcodeInfoStruct_G91
//                bool gcodeInfoStruct_G91_1
//                int spline_Bl_ncoeff
//                const ::coder::array<double, 2U> &spline_Bl_breakpoints
//                unsigned long spline_Bl_handle
//                int spline_Bl_order
//                const ::coder::array<double, 2U> &spline_coeff
//                const ::coder::array<double, 2U> &spline_knots
//                double spline_Ltot
//                const ::coder::array<double, 2U> &spline_Lk
//                const double R0[6]
//                const double R1[6]
//                const double Cprim[3]
//                const double evec[3]
//                const double CoeffP5[6][5]
//                CurvStruct *CStrct
// Return Type  : void
//
void d_constrCurvStruct(bool gcodeInfoStruct_TRAFO, bool gcodeInfoStruct_HSC,
                        double gcodeInfoStruct_FeedRate, double gcodeInfoStruct_SpindleSpeed,
                        int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                        bool gcodeInfoStruct_G91_1, int spline_Bl_ncoeff,
                        const ::coder::array<double, 2U> &spline_Bl_breakpoints,
                        unsigned long spline_Bl_handle, int spline_Bl_order,
                        const ::coder::array<double, 2U> &spline_coeff,
                        const ::coder::array<double, 2U> &spline_knots, double spline_Ltot,
                        const ::coder::array<double, 2U> &spline_Lk, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const double CoeffP5[6][5], CurvStruct *CStrct)
{
    int b_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int loop_ub;
    // 'constrCurvStruct:20' coder.inline("never");
    // 'constrCurvStruct:22' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:23'     'sp', spline,...
    // 'constrCurvStruct:24'     'R0', R0, ...
    // 'constrCurvStruct:25'     'R1', R1, ...
    // 'constrCurvStruct:26'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:27'     'delta', delta, ...
    // 'constrCurvStruct:28'     'evec', evec,...
    // 'constrCurvStruct:29'     'theta', theta,...
    // 'constrCurvStruct:30'     'pitch', pitch,...
    // 'constrCurvStruct:31'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:32'     'sp_index', uint32(1),...
    // 'constrCurvStruct:33'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:34'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:35'     'index_smooth', int32(0),...
    // 'constrCurvStruct:36'     'UseConstJerk', false,...
    // 'constrCurvStruct:37'     'ConstJerk', 0,...
    // 'constrCurvStruct:38'     'Coeff', Coeff,...
    // 'constrCurvStruct:39'     'a_param', 1,...
    // 'constrCurvStruct:40'     'b_param', 0 ...
    // 'constrCurvStruct:41'     );
    CStrct->Info.Type = CurveType_TransP5;
    CStrct->Info.zspdmode = ZSpdMode_NN;
    CStrct->Info.TRAFO = gcodeInfoStruct_TRAFO;
    CStrct->Info.HSC = gcodeInfoStruct_HSC;
    CStrct->Info.FeedRate = gcodeInfoStruct_FeedRate;
    CStrct->Info.SpindleSpeed = gcodeInfoStruct_SpindleSpeed;
    CStrct->Info.gcode_source_line = gcodeInfoStruct_gcode_source_line;
    CStrct->Info.G91 = gcodeInfoStruct_G91;
    CStrct->Info.G91_1 = gcodeInfoStruct_G91_1;
    CStrct->sp.Bl.ncoeff = spline_Bl_ncoeff;
    CStrct->sp.Bl.breakpoints.set_size(1, spline_Bl_breakpoints.size(1));
    loop_ub = spline_Bl_breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        CStrct->sp.Bl.breakpoints[i] = spline_Bl_breakpoints[i];
    }
    CStrct->sp.Bl.handle = spline_Bl_handle;
    CStrct->sp.Bl.order = spline_Bl_order;
    CStrct->sp.coeff.set_size(spline_coeff.size(0), spline_coeff.size(1));
    b_loop_ub = spline_coeff.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        int c_loop_ub;
        c_loop_ub = spline_coeff.size(0);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            CStrct->sp.coeff[i2 + CStrct->sp.coeff.size(0) * i1] =
                spline_coeff[i2 + spline_coeff.size(0) * i1];
        }
    }
    CStrct->sp.knots.set_size(1, spline_knots.size(1));
    d_loop_ub = spline_knots.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        CStrct->sp.knots[i3] = spline_knots[i3];
    }
    CStrct->sp.Ltot = spline_Ltot;
    CStrct->sp.Lk.set_size(1, spline_Lk.size(1));
    e_loop_ub = spline_Lk.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        CStrct->sp.Lk[i4] = spline_Lk[i4];
    }
    CStrct->delta = 0.0;
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->CorrectedHelixCenter[2] = Cprim[2];
    CStrct->evec[2] = evec[2];
    CStrct->theta = 0.0;
    CStrct->pitch = 0.0;
    CStrct->CoeffP5.set_size(5, 6);
    for (int b_i{0}; b_i < 6; b_i++) {
        CStrct->R0[b_i] = R0[b_i];
        CStrct->R1[b_i] = R1[b_i];
        for (int i5{0}; i5 < 5; i5++) {
            CStrct->CoeffP5[i5 + CStrct->CoeffP5.size(0) * b_i] = CoeffP5[b_i][i5];
        }
    }
    CStrct->sp_index = 1U;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(1);
    CStrct->Coeff[0] = 0.0;
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:43' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:46' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:47' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:48' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:49' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:50' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:51' coder.cstructname( CStrct, StructTypeName.Curve );
}

} // namespace ocn

//
// File trailer for constrCurvStruct.cpp
//
// [EOF]
//
