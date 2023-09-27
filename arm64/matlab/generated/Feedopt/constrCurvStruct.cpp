//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStruct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

// Include Files
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, toolStruct, ...
//                       spline, R0, R1, Cprim, delta, evec, theta, pitch, ...
//                       CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  Inputs :
//  gcodeInfoStruct   : Struct containing the information from the Gcode
//  toolStruct        : Struct containing the information of the tool
//  spline            : Base spline basis
//  R0                : Vector of the pose ( position + orientation ) at starting time
//  R1                : Vector of the pose ( position + orientation ) at ending time
//  Cprim             : Corrected center for the circle
//  delta             : Difference between the radii
//  evec              : Unit vector in the linear direction for the helix
//  theta             : Rotation angle of the helix
//  pitch             : Linear step for the helix
//  CoeffP5           : Coefficient of the 5th order polynom
//  Coeff             : Coeffs of the feedrate planning
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
//                int toolStruct_toolno
//                int toolStruct_pocketno
//                const Axes *toolStruct_offset
//                double toolStruct_diameter
//                double toolStruct_frontangle
//                double toolStruct_backangle
//                int toolStruct_orientation
//                const SplineStruct *spline
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
                        bool gcodeInfoStruct_G91_1, int toolStruct_toolno, int toolStruct_pocketno,
                        const Axes *toolStruct_offset, double toolStruct_diameter,
                        double toolStruct_frontangle, double toolStruct_backangle,
                        int toolStruct_orientation, const SplineStruct *spline, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const double CoeffP5[6], CurvStruct *CStrct)
{
    // 'constrCurvStruct:24' coder.inline("never");
    // 'constrCurvStruct:26' CStrct = struct(...
    // 'constrCurvStruct:27'     'Info',                 gcodeInfoStruct, ...
    // 'constrCurvStruct:28'     'tool',                 toolStruct,...
    // 'constrCurvStruct:29'     'sp',                   spline,...
    // 'constrCurvStruct:30'     'R0',                   R0, ...
    // 'constrCurvStruct:31'     'R1',                   R1, ...
    // 'constrCurvStruct:32'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:33'     'delta',                delta, ...
    // 'constrCurvStruct:34'     'evec',                 evec,...
    // 'constrCurvStruct:35'     'theta',                theta,...
    // 'constrCurvStruct:36'     'pitch',                pitch,...
    // 'constrCurvStruct:37'     'CoeffP5',              CoeffP5,...
    // 'constrCurvStruct:38'     'sp_index',             uint32(1),...
    // 'constrCurvStruct:39'     'i_begin_sp',           int32(0),...
    // 'constrCurvStruct:40'     'i_end_sp',             int32(0),...
    // 'constrCurvStruct:41'     'index_smooth',         int32(0),...
    // 'constrCurvStruct:42'     'UseConstJerk',         false,...
    // 'constrCurvStruct:43'     'ConstJerk',            0,...
    // 'constrCurvStruct:44'     'Coeff',                Coeff,...
    // 'constrCurvStruct:45'     'a_param',              1,...
    // 'constrCurvStruct:46'     'b_param',              0 ...
    // 'constrCurvStruct:47'     );
    CStrct->Info.Type = gcodeInfoStruct_Type;
    CStrct->Info.zspdmode = gcodeInfoStruct_zspdmode;
    CStrct->Info.TRAFO = gcodeInfoStruct_TRAFO;
    CStrct->Info.HSC = gcodeInfoStruct_HSC;
    CStrct->Info.FeedRate = gcodeInfoStruct_FeedRate;
    CStrct->Info.SpindleSpeed = gcodeInfoStruct_SpindleSpeed;
    CStrct->Info.gcode_source_line = gcodeInfoStruct_gcode_source_line;
    CStrct->Info.G91 = gcodeInfoStruct_G91;
    CStrct->Info.G91_1 = gcodeInfoStruct_G91_1;
    CStrct->tool.toolno = toolStruct_toolno;
    CStrct->tool.pocketno = toolStruct_pocketno;
    CStrct->tool.offset = *toolStruct_offset;
    CStrct->tool.diameter = toolStruct_diameter;
    CStrct->tool.frontangle = toolStruct_frontangle;
    CStrct->tool.backangle = toolStruct_backangle;
    CStrct->tool.orientation = toolStruct_orientation;
    CStrct->sp = *spline;
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
    // 'constrCurvStruct:49' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:50' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:51' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:52' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:53' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } );
    // 'constrCurvStruct:55' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:56' coder.cstructname( CStrct.tool,     StructTypeName.Tool );
    // 'constrCurvStruct:57' coder.cstructname( CStrct.tool.offset, StructTypeName.Axes );
    // 'constrCurvStruct:58' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:59' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:60' coder.cstructname( CStrct,          StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, toolStruct, ...
//                       spline, R0, R1, Cprim, delta, evec, theta, pitch, ...
//                       CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  Inputs :
//  gcodeInfoStruct   : Struct containing the information from the Gcode
//  toolStruct        : Struct containing the information of the tool
//  spline            : Base spline basis
//  R0                : Vector of the pose ( position + orientation ) at starting time
//  R1                : Vector of the pose ( position + orientation ) at ending time
//  Cprim             : Corrected center for the circle
//  delta             : Difference between the radii
//  evec              : Unit vector in the linear direction for the helix
//  theta             : Rotation angle of the helix
//  pitch             : Linear step for the helix
//  CoeffP5           : Coefficient of the 5th order polynom
//  Coeff             : Coeffs of the feedrate planning
//
//  Ouputs:
//  CStrct    : The resulting structure
//
// Arguments    : const GcodeInfoStruct gcodeInfoStruct
//                const Tool *toolStruct
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
void c_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const Tool *toolStruct,
                        const SplineStruct *spline, const double R0[6], const double R1[6],
                        const double Cprim[3], double delta, const double evec[3], double theta,
                        double pitch, const double CoeffP5[6], CurvStruct *CStrct)
{
    // 'constrCurvStruct:24' coder.inline("never");
    // 'constrCurvStruct:26' CStrct = struct(...
    // 'constrCurvStruct:27'     'Info',                 gcodeInfoStruct, ...
    // 'constrCurvStruct:28'     'tool',                 toolStruct,...
    // 'constrCurvStruct:29'     'sp',                   spline,...
    // 'constrCurvStruct:30'     'R0',                   R0, ...
    // 'constrCurvStruct:31'     'R1',                   R1, ...
    // 'constrCurvStruct:32'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:33'     'delta',                delta, ...
    // 'constrCurvStruct:34'     'evec',                 evec,...
    // 'constrCurvStruct:35'     'theta',                theta,...
    // 'constrCurvStruct:36'     'pitch',                pitch,...
    // 'constrCurvStruct:37'     'CoeffP5',              CoeffP5,...
    // 'constrCurvStruct:38'     'sp_index',             uint32(1),...
    // 'constrCurvStruct:39'     'i_begin_sp',           int32(0),...
    // 'constrCurvStruct:40'     'i_end_sp',             int32(0),...
    // 'constrCurvStruct:41'     'index_smooth',         int32(0),...
    // 'constrCurvStruct:42'     'UseConstJerk',         false,...
    // 'constrCurvStruct:43'     'ConstJerk',            0,...
    // 'constrCurvStruct:44'     'Coeff',                Coeff,...
    // 'constrCurvStruct:45'     'a_param',              1,...
    // 'constrCurvStruct:46'     'b_param',              0 ...
    // 'constrCurvStruct:47'     );
    CStrct->Info = gcodeInfoStruct;
    CStrct->tool = *toolStruct;
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
    // 'constrCurvStruct:49' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:50' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:51' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:52' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:53' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } );
    // 'constrCurvStruct:55' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:56' coder.cstructname( CStrct.tool,     StructTypeName.Tool );
    // 'constrCurvStruct:57' coder.cstructname( CStrct.tool.offset, StructTypeName.Axes );
    // 'constrCurvStruct:58' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:59' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:60' coder.cstructname( CStrct,          StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, toolStruct, ...
//                       spline, R0, R1, Cprim, delta, evec, theta, pitch, ...
//                       CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  Inputs :
//  gcodeInfoStruct   : Struct containing the information from the Gcode
//  toolStruct        : Struct containing the information of the tool
//  spline            : Base spline basis
//  R0                : Vector of the pose ( position + orientation ) at starting time
//  R1                : Vector of the pose ( position + orientation ) at ending time
//  Cprim             : Corrected center for the circle
//  delta             : Difference between the radii
//  evec              : Unit vector in the linear direction for the helix
//  theta             : Rotation angle of the helix
//  pitch             : Linear step for the helix
//  CoeffP5           : Coefficient of the 5th order polynom
//  Coeff             : Coeffs of the feedrate planning
//
//  Ouputs:
//  CStrct    : The resulting structure
//
// Arguments    : const GcodeInfoStruct gcodeInfoStruct
//                const Tool *toolStruct
//                const SplineStruct *spline
//                const double R0[6]
//                const double R1[6]
//                const double Cprim[3]
//                const double evec[3]
//                const ::coder::array<double, 2U> &CoeffP5
//                CurvStruct *CStrct
// Return Type  : void
//
void c_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const Tool *toolStruct,
                        const SplineStruct *spline, const double R0[6], const double R1[6],
                        const double Cprim[3], const double evec[3],
                        const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct)
{
    int loop_ub;
    // 'constrCurvStruct:24' coder.inline("never");
    // 'constrCurvStruct:26' CStrct = struct(...
    // 'constrCurvStruct:27'     'Info',                 gcodeInfoStruct, ...
    // 'constrCurvStruct:28'     'tool',                 toolStruct,...
    // 'constrCurvStruct:29'     'sp',                   spline,...
    // 'constrCurvStruct:30'     'R0',                   R0, ...
    // 'constrCurvStruct:31'     'R1',                   R1, ...
    // 'constrCurvStruct:32'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:33'     'delta',                delta, ...
    // 'constrCurvStruct:34'     'evec',                 evec,...
    // 'constrCurvStruct:35'     'theta',                theta,...
    // 'constrCurvStruct:36'     'pitch',                pitch,...
    // 'constrCurvStruct:37'     'CoeffP5',              CoeffP5,...
    // 'constrCurvStruct:38'     'sp_index',             uint32(1),...
    // 'constrCurvStruct:39'     'i_begin_sp',           int32(0),...
    // 'constrCurvStruct:40'     'i_end_sp',             int32(0),...
    // 'constrCurvStruct:41'     'index_smooth',         int32(0),...
    // 'constrCurvStruct:42'     'UseConstJerk',         false,...
    // 'constrCurvStruct:43'     'ConstJerk',            0,...
    // 'constrCurvStruct:44'     'Coeff',                Coeff,...
    // 'constrCurvStruct:45'     'a_param',              1,...
    // 'constrCurvStruct:46'     'b_param',              0 ...
    // 'constrCurvStruct:47'     );
    CStrct->Info = gcodeInfoStruct;
    CStrct->tool = *toolStruct;
    CStrct->sp = *spline;
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
    CStrct->Coeff.set_size(1);
    CStrct->Coeff[0] = 0.0;
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:49' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:50' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:51' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:52' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:53' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } );
    // 'constrCurvStruct:55' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:56' coder.cstructname( CStrct.tool,     StructTypeName.Tool );
    // 'constrCurvStruct:57' coder.cstructname( CStrct.tool.offset, StructTypeName.Axes );
    // 'constrCurvStruct:58' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:59' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:60' coder.cstructname( CStrct,          StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, toolStruct, ...
//                       spline, R0, R1, Cprim, delta, evec, theta, pitch, ...
//                       CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  Inputs :
//  gcodeInfoStruct   : Struct containing the information from the Gcode
//  toolStruct        : Struct containing the information of the tool
//  spline            : Base spline basis
//  R0                : Vector of the pose ( position + orientation ) at starting time
//  R1                : Vector of the pose ( position + orientation ) at ending time
//  Cprim             : Corrected center for the circle
//  delta             : Difference between the radii
//  evec              : Unit vector in the linear direction for the helix
//  theta             : Rotation angle of the helix
//  pitch             : Linear step for the helix
//  CoeffP5           : Coefficient of the 5th order polynom
//  Coeff             : Coeffs of the feedrate planning
//
//  Ouputs:
//  CStrct    : The resulting structure
//
// Arguments    : const GcodeInfoStruct *gcodeInfoStruct
//                const Tool *toolStruct
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
void constrCurvStruct(const GcodeInfoStruct *gcodeInfoStruct, const Tool *toolStruct,
                      const SplineStruct *spline, const double R0[6], const double R1[6],
                      const double Cprim[3], double delta, const double evec[3], double theta,
                      double pitch, const ::coder::array<double, 2U> &CoeffP5,
                      const ::coder::array<double, 1U> &Coeff, CurvStruct *CStrct)
{
    int b_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrCurvStruct:24' coder.inline("never");
    // 'constrCurvStruct:26' CStrct = struct(...
    // 'constrCurvStruct:27'     'Info',                 gcodeInfoStruct, ...
    // 'constrCurvStruct:28'     'tool',                 toolStruct,...
    // 'constrCurvStruct:29'     'sp',                   spline,...
    // 'constrCurvStruct:30'     'R0',                   R0, ...
    // 'constrCurvStruct:31'     'R1',                   R1, ...
    // 'constrCurvStruct:32'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:33'     'delta',                delta, ...
    // 'constrCurvStruct:34'     'evec',                 evec,...
    // 'constrCurvStruct:35'     'theta',                theta,...
    // 'constrCurvStruct:36'     'pitch',                pitch,...
    // 'constrCurvStruct:37'     'CoeffP5',              CoeffP5,...
    // 'constrCurvStruct:38'     'sp_index',             uint32(1),...
    // 'constrCurvStruct:39'     'i_begin_sp',           int32(0),...
    // 'constrCurvStruct:40'     'i_end_sp',             int32(0),...
    // 'constrCurvStruct:41'     'index_smooth',         int32(0),...
    // 'constrCurvStruct:42'     'UseConstJerk',         false,...
    // 'constrCurvStruct:43'     'ConstJerk',            0,...
    // 'constrCurvStruct:44'     'Coeff',                Coeff,...
    // 'constrCurvStruct:45'     'a_param',              1,...
    // 'constrCurvStruct:46'     'b_param',              0 ...
    // 'constrCurvStruct:47'     );
    CStrct->Info = *gcodeInfoStruct;
    CStrct->tool = *toolStruct;
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
    // 'constrCurvStruct:49' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:50' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:51' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:52' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:53' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } );
    // 'constrCurvStruct:55' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:56' coder.cstructname( CStrct.tool,     StructTypeName.Tool );
    // 'constrCurvStruct:57' coder.cstructname( CStrct.tool.offset, StructTypeName.Axes );
    // 'constrCurvStruct:58' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:59' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:60' coder.cstructname( CStrct,          StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, toolStruct, ...
//                       spline, R0, R1, Cprim, delta, evec, theta, pitch, ...
//                       CoeffP5, Coeff )
//
// Construct a struct for the curves.
//
//  Inputs :
//  gcodeInfoStruct   : Struct containing the information from the Gcode
//  toolStruct        : Struct containing the information of the tool
//  spline            : Base spline basis
//  R0                : Vector of the pose ( position + orientation ) at starting time
//  R1                : Vector of the pose ( position + orientation ) at ending time
//  Cprim             : Corrected center for the circle
//  delta             : Difference between the radii
//  evec              : Unit vector in the linear direction for the helix
//  theta             : Rotation angle of the helix
//  pitch             : Linear step for the helix
//  CoeffP5           : Coefficient of the 5th order polynom
//  Coeff             : Coeffs of the feedrate planning
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
//                int toolStruct_toolno
//                int toolStruct_pocketno
//                const Axes *toolStruct_offset
//                double toolStruct_diameter
//                double toolStruct_frontangle
//                double toolStruct_backangle
//                int toolStruct_orientation
//                const SplineStruct *spline
//                const double R0[6]
//                const double R1[6]
//                const double Cprim[3]
//                const double evec[3]
//                const double CoeffP5[6][6]
//                CurvStruct *CStrct
// Return Type  : void
//
void d_constrCurvStruct(bool gcodeInfoStruct_TRAFO, bool gcodeInfoStruct_HSC,
                        double gcodeInfoStruct_FeedRate, double gcodeInfoStruct_SpindleSpeed,
                        int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                        bool gcodeInfoStruct_G91_1, int toolStruct_toolno, int toolStruct_pocketno,
                        const Axes *toolStruct_offset, double toolStruct_diameter,
                        double toolStruct_frontangle, double toolStruct_backangle,
                        int toolStruct_orientation, const SplineStruct *spline, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const double CoeffP5[6][6], CurvStruct *CStrct)
{
    // 'constrCurvStruct:24' coder.inline("never");
    // 'constrCurvStruct:26' CStrct = struct(...
    // 'constrCurvStruct:27'     'Info',                 gcodeInfoStruct, ...
    // 'constrCurvStruct:28'     'tool',                 toolStruct,...
    // 'constrCurvStruct:29'     'sp',                   spline,...
    // 'constrCurvStruct:30'     'R0',                   R0, ...
    // 'constrCurvStruct:31'     'R1',                   R1, ...
    // 'constrCurvStruct:32'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:33'     'delta',                delta, ...
    // 'constrCurvStruct:34'     'evec',                 evec,...
    // 'constrCurvStruct:35'     'theta',                theta,...
    // 'constrCurvStruct:36'     'pitch',                pitch,...
    // 'constrCurvStruct:37'     'CoeffP5',              CoeffP5,...
    // 'constrCurvStruct:38'     'sp_index',             uint32(1),...
    // 'constrCurvStruct:39'     'i_begin_sp',           int32(0),...
    // 'constrCurvStruct:40'     'i_end_sp',             int32(0),...
    // 'constrCurvStruct:41'     'index_smooth',         int32(0),...
    // 'constrCurvStruct:42'     'UseConstJerk',         false,...
    // 'constrCurvStruct:43'     'ConstJerk',            0,...
    // 'constrCurvStruct:44'     'Coeff',                Coeff,...
    // 'constrCurvStruct:45'     'a_param',              1,...
    // 'constrCurvStruct:46'     'b_param',              0 ...
    // 'constrCurvStruct:47'     );
    CStrct->Info.Type = CurveType_TransP5;
    CStrct->Info.zspdmode = ZSpdMode_NN;
    CStrct->Info.TRAFO = gcodeInfoStruct_TRAFO;
    CStrct->Info.HSC = gcodeInfoStruct_HSC;
    CStrct->Info.FeedRate = gcodeInfoStruct_FeedRate;
    CStrct->Info.SpindleSpeed = gcodeInfoStruct_SpindleSpeed;
    CStrct->Info.gcode_source_line = gcodeInfoStruct_gcode_source_line;
    CStrct->Info.G91 = gcodeInfoStruct_G91;
    CStrct->Info.G91_1 = gcodeInfoStruct_G91_1;
    CStrct->tool.toolno = toolStruct_toolno;
    CStrct->tool.pocketno = toolStruct_pocketno;
    CStrct->tool.offset = *toolStruct_offset;
    CStrct->tool.diameter = toolStruct_diameter;
    CStrct->tool.frontangle = toolStruct_frontangle;
    CStrct->tool.backangle = toolStruct_backangle;
    CStrct->tool.orientation = toolStruct_orientation;
    CStrct->sp = *spline;
    CStrct->delta = 0.0;
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->CorrectedHelixCenter[2] = Cprim[2];
    CStrct->evec[2] = evec[2];
    CStrct->theta = 0.0;
    CStrct->pitch = 0.0;
    CStrct->CoeffP5.set_size(6, 6);
    for (int i{0}; i < 6; i++) {
        CStrct->R0[i] = R0[i];
        CStrct->R1[i] = R1[i];
        for (int b_i{0}; b_i < 6; b_i++) {
            CStrct->CoeffP5[b_i + CStrct->CoeffP5.size(0) * i] = CoeffP5[i][b_i];
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
    // 'constrCurvStruct:49' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:50' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:51' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:52' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:53' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } );
    // 'constrCurvStruct:55' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:56' coder.cstructname( CStrct.tool,     StructTypeName.Tool );
    // 'constrCurvStruct:57' coder.cstructname( CStrct.tool.offset, StructTypeName.Axes );
    // 'constrCurvStruct:58' coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    // 'constrCurvStruct:59' coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    // 'constrCurvStruct:60' coder.cstructname( CStrct,          StructTypeName.Curve );
}

} // namespace ocn

//
// File trailer for constrCurvStruct.cpp
//
// [EOF]
//
