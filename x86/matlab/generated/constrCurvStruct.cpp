//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:31:27
//

// Include Files
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"

// Function Definitions
//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, R0, R1, Cprim, ...
//                       delta, evec, theta, pitch, CoeffP5, Coeff )
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
// Arguments    : CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void b_constrCurvStruct(CurvStruct *CStrct)
{
    static const unsigned long t0_G91_1{0UL};
    // 'constrCurvStruct:19' coder.inline("never");
    // 'constrCurvStruct:21' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:22'     'R0', R0, ...
    // 'constrCurvStruct:23'     'R1', R1, ...
    // 'constrCurvStruct:24'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:25'     'delta', delta, ...
    // 'constrCurvStruct:26'     'evec', evec,...
    // 'constrCurvStruct:27'     'theta', theta,...
    // 'constrCurvStruct:28'     'pitch', pitch,...
    // 'constrCurvStruct:29'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:30'     'sp_index', int32(1),...
    // 'constrCurvStruct:31'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:32'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:33'     'index_smooth', int32(0),...
    // 'constrCurvStruct:34'     'UseConstJerk', false,...
    // 'constrCurvStruct:35'     'ConstJerk', 0,...
    // 'constrCurvStruct:36'     'Coeff', Coeff,...
    // 'constrCurvStruct:37'     'a_param', 1,...
    // 'constrCurvStruct:38'     'b_param', 0 ...
    // 'constrCurvStruct:39'     );
    CStrct->Info.Type = CurveType_Line;
    CStrct->Info.zspdmode = ZSpdMode_NN;
    CStrct->Info.TRAFO = false;
    CStrct->Info.HSC = false;
    CStrct->Info.FeedRate = false;
    CStrct->Info.SpindleSpeed = true;
    CStrct->Info.gcode_source_line = 0.0;
    CStrct->Info.G91 = 0.0;
    CStrct->Info.G91_1 = t0_G91_1;
    CStrct->R0.set_size(1);
    CStrct->R0[0] = 0.0;
    CStrct->R1.set_size(1);
    CStrct->R1[0] = 0.0;
    CStrct->delta = 0.0;
    CStrct->CorrectedHelixCenter[0] = 0.0;
    CStrct->evec[0] = 0.0;
    CStrct->CorrectedHelixCenter[1] = 0.0;
    CStrct->evec[1] = 0.0;
    CStrct->CorrectedHelixCenter[2] = 0.0;
    CStrct->evec[2] = 0.0;
    CStrct->theta = 0.0;
    CStrct->pitch = 0.0;
    CStrct->CoeffP5.set_size(1, 6);
    for (int i{0}; i < 6; i++) {
        CStrct->CoeffP5[CStrct->CoeffP5.size(0) * i] = 0.0;
    }
    CStrct->sp_index = 1;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(1);
    CStrct->Coeff[0] = 0.0;
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:41' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:42' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:43' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:46' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:47' coder.cstructname( CStrct, StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, R0, R1, Cprim, ...
//                       delta, evec, theta, pitch, CoeffP5, Coeff )
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
//                const ::coder::array<double, 1U> &R0
//                const ::coder::array<double, 1U> &R1
//                const double Cprim[3]
//                double delta
//                const double evec[3]
//                double theta
//                double pitch
//                CurvStruct *CStrct
// Return Type  : void
//
void b_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const ::coder::array<double, 1U> &R0,
                        const ::coder::array<double, 1U> &R1, const double Cprim[3], double delta,
                        const double evec[3], double theta, double pitch, CurvStruct *CStrct)
{
    int b_loop_ub;
    int loop_ub;
    // 'constrCurvStruct:19' coder.inline("never");
    // 'constrCurvStruct:21' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:22'     'R0', R0, ...
    // 'constrCurvStruct:23'     'R1', R1, ...
    // 'constrCurvStruct:24'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:25'     'delta', delta, ...
    // 'constrCurvStruct:26'     'evec', evec,...
    // 'constrCurvStruct:27'     'theta', theta,...
    // 'constrCurvStruct:28'     'pitch', pitch,...
    // 'constrCurvStruct:29'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:30'     'sp_index', int32(1),...
    // 'constrCurvStruct:31'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:32'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:33'     'index_smooth', int32(0),...
    // 'constrCurvStruct:34'     'UseConstJerk', false,...
    // 'constrCurvStruct:35'     'ConstJerk', 0,...
    // 'constrCurvStruct:36'     'Coeff', Coeff,...
    // 'constrCurvStruct:37'     'a_param', 1,...
    // 'constrCurvStruct:38'     'b_param', 0 ...
    // 'constrCurvStruct:39'     );
    CStrct->Info = gcodeInfoStruct;
    CStrct->R0.set_size(R0.size(0));
    loop_ub = R0.size(0);
    for (int i{0}; i < loop_ub; i++) {
        CStrct->R0[i] = R0[i];
    }
    CStrct->R1.set_size(R1.size(0));
    b_loop_ub = R1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        CStrct->R1[i1] = R1[i1];
    }
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
    for (int i2{0}; i2 < 6; i2++) {
        CStrct->CoeffP5[CStrct->CoeffP5.size(0) * i2] = 0.0;
    }
    CStrct->sp_index = 1;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(1);
    CStrct->Coeff[0] = 0.0;
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:41' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:42' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:43' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:46' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:47' coder.cstructname( CStrct, StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, R0, R1, Cprim, ...
//                       delta, evec, theta, pitch, CoeffP5, Coeff )
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
//                const ::coder::array<double, 1U> &R0
//                const ::coder::array<double, 1U> &R1
//                const ::coder::array<double, 2U> &CoeffP5
//                CurvStruct *CStrct
// Return Type  : void
//
void b_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const ::coder::array<double, 1U> &R0,
                        const ::coder::array<double, 1U> &R1,
                        const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct)
{
    int b_loop_ub;
    int c_loop_ub;
    int loop_ub;
    // 'constrCurvStruct:19' coder.inline("never");
    // 'constrCurvStruct:21' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:22'     'R0', R0, ...
    // 'constrCurvStruct:23'     'R1', R1, ...
    // 'constrCurvStruct:24'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:25'     'delta', delta, ...
    // 'constrCurvStruct:26'     'evec', evec,...
    // 'constrCurvStruct:27'     'theta', theta,...
    // 'constrCurvStruct:28'     'pitch', pitch,...
    // 'constrCurvStruct:29'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:30'     'sp_index', int32(1),...
    // 'constrCurvStruct:31'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:32'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:33'     'index_smooth', int32(0),...
    // 'constrCurvStruct:34'     'UseConstJerk', false,...
    // 'constrCurvStruct:35'     'ConstJerk', 0,...
    // 'constrCurvStruct:36'     'Coeff', Coeff,...
    // 'constrCurvStruct:37'     'a_param', 1,...
    // 'constrCurvStruct:38'     'b_param', 0 ...
    // 'constrCurvStruct:39'     );
    CStrct->Info = gcodeInfoStruct;
    CStrct->R0.set_size(R0.size(0));
    loop_ub = R0.size(0);
    for (int i{0}; i < loop_ub; i++) {
        CStrct->R0[i] = R0[i];
    }
    CStrct->R1.set_size(R1.size(0));
    b_loop_ub = R1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        CStrct->R1[i1] = R1[i1];
    }
    CStrct->delta = 0.0;
    CStrct->CorrectedHelixCenter[0] = 0.0;
    CStrct->evec[0] = 0.0;
    CStrct->CorrectedHelixCenter[1] = 0.0;
    CStrct->evec[1] = 0.0;
    CStrct->CorrectedHelixCenter[2] = 0.0;
    CStrct->evec[2] = 0.0;
    CStrct->theta = 0.0;
    CStrct->pitch = 0.0;
    CStrct->CoeffP5.set_size(CoeffP5.size(0), 6);
    c_loop_ub = CoeffP5.size(0);
    for (int i2{0}; i2 < 6; i2++) {
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            CStrct->CoeffP5[i3 + CStrct->CoeffP5.size(0) * i2] = CoeffP5[i3 + CoeffP5.size(0) * i2];
        }
    }
    CStrct->sp_index = 1;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(1);
    CStrct->Coeff[0] = 0.0;
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:41' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:42' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:43' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:46' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:47' coder.cstructname( CStrct, StructTypeName.Curve );
}

//
// function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, R0, R1, Cprim, ...
//                       delta, evec, theta, pitch, CoeffP5, Coeff )
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
//                const ::coder::array<double, 1U> &R0
//                const ::coder::array<double, 1U> &R1
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
void constrCurvStruct(const GcodeInfoStruct *gcodeInfoStruct, const ::coder::array<double, 1U> &R0,
                      const ::coder::array<double, 1U> &R1, const double Cprim[3], double delta,
                      const double evec[3], double theta, double pitch,
                      const ::coder::array<double, 2U> &CoeffP5,
                      const ::coder::array<double, 1U> &Coeff, CurvStruct *CStrct)
{
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrCurvStruct:19' coder.inline("never");
    // 'constrCurvStruct:21' CStrct = struct('Info', gcodeInfoStruct, ...
    // 'constrCurvStruct:22'     'R0', R0, ...
    // 'constrCurvStruct:23'     'R1', R1, ...
    // 'constrCurvStruct:24'     'CorrectedHelixCenter', Cprim, ...
    // 'constrCurvStruct:25'     'delta', delta, ...
    // 'constrCurvStruct:26'     'evec', evec,...
    // 'constrCurvStruct:27'     'theta', theta,...
    // 'constrCurvStruct:28'     'pitch', pitch,...
    // 'constrCurvStruct:29'     'CoeffP5', CoeffP5,...
    // 'constrCurvStruct:30'     'sp_index', int32(1),...
    // 'constrCurvStruct:31'     'i_begin_sp', int32(0),...
    // 'constrCurvStruct:32'     'i_end_sp', int32(0),...
    // 'constrCurvStruct:33'     'index_smooth', int32(0),...
    // 'constrCurvStruct:34'     'UseConstJerk', false,...
    // 'constrCurvStruct:35'     'ConstJerk', 0,...
    // 'constrCurvStruct:36'     'Coeff', Coeff,...
    // 'constrCurvStruct:37'     'a_param', 1,...
    // 'constrCurvStruct:38'     'b_param', 0 ...
    // 'constrCurvStruct:39'     );
    CStrct->Info = *gcodeInfoStruct;
    CStrct->R0.set_size(R0.size(0));
    loop_ub = R0.size(0);
    for (int i{0}; i < loop_ub; i++) {
        CStrct->R0[i] = R0[i];
    }
    CStrct->R1.set_size(R1.size(0));
    b_loop_ub = R1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        CStrct->R1[i1] = R1[i1];
    }
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
    c_loop_ub = CoeffP5.size(0);
    for (int i2{0}; i2 < 6; i2++) {
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            CStrct->CoeffP5[i3 + CStrct->CoeffP5.size(0) * i2] = CoeffP5[i3 + CoeffP5.size(0) * i2];
        }
    }
    CStrct->sp_index = 1;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->Coeff.set_size(Coeff.size(0));
    d_loop_ub = Coeff.size(0);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        CStrct->Coeff[i4] = Coeff[i4];
    }
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    // 'constrCurvStruct:41' if ~coder.target( 'MATLAB' )
    // 'constrCurvStruct:42' coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    // 'constrCurvStruct:43' coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    // 'constrCurvStruct:44' coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } ) ;
    // 'constrCurvStruct:45' coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } ) ;
    // 'constrCurvStruct:46' coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    // 'constrCurvStruct:47' coder.cstructname( CStrct, StructTypeName.Curve );
}

} // namespace ocn

//
// File trailer for constrCurvStruct.cpp
//
// [EOF]
//
