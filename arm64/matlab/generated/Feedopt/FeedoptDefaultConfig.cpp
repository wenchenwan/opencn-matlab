
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptDefaultConfig.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "FeedoptDefaultConfig.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "setMachineAxisInConfig.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// function [ cfg ] = FeedoptDefaultConfig()
//
// FeedoptDefaultConfig : Create a configuration structure with the default
//  settings.
//
//  Outputs :
//  cfg   : The resulting default structure
//
//
// Arguments    : FeedoptConfig *cfg
// Return Type  : void
//
namespace ocn {
void FeedoptDefaultConfig(FeedoptConfig *cfg)
{
    static const double dv[15]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.07155, -0.1645,
                               1.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    static const double GaussLegendreW[5]{0.23692688505618911, 0.47862867049936625,
                                          0.56888888888888889, 0.47862867049936625,
                                          0.23692688505618911};
    static const double GaussLegendreX[5]{-0.90617984593866385, -0.538469310105683, 0.0,
                                          0.538469310105683, 0.90617984593866385};
    static const int iv2[6]{1500000, 1500000, 1500000, 0, 10000, 50000};
    static const short iv[6]{500, 500, 500, 0, 40, 50};
    static const short iv1[6]{15000, 15000, 15000, 0, 200, 1000};
    static const char b_cv[9]{'l', 'o', 'g', 's', '/', 'l', 'o', 'g', 's'};
    static const char kin_type[8]{'x', 'y', 'z', 'b', 'c', '_', 't', 't'};
    static const bool bv[6]{true, true, true, false, true, true};
    b_FeedoptConfig r;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'FeedoptDefaultConfig:10' coder.inline("never");
    // 'FeedoptDefaultConfig:12' tol_col_compress_deg    = 30;
    // 'FeedoptDefaultConfig:13' tol_col_smooth_deg      = 10;
    //  Computation of Gauss-Legendre knots and weights for numerical integration
    // 'FeedoptDefaultConfig:16' GaussLegendreN = 5;
    //  number of evaluation points
    // 'FeedoptDefaultConfig:17' [GaussLegendreX, GaussLegendreW] = lgwt(GaussLegendreN, -1, 1);
    //  normalized to integration interval [-1, 1]
    // 'FeedoptDefaultConfig:19' GaussLegendreX = flipud( GaussLegendreX );
    // 'FeedoptDefaultConfig:22' LP = struct(...
    // 'FeedoptDefaultConfig:23'     'Type', 'LP', ...                       % Optimisation type
    // 'FeedoptDefaultConfig:24'     'USE_JERK_CONSTRAINTS', true,...        % Use jerk constraints
    // 'FeedoptDefaultConfig:25'     'FIND_REASON_INFEASIBILITY', true,...   % Find the reason of
    // the infeasibility 'FeedoptDefaultConfig:26'     'ACC_RAMP_OVER_WINDOWS', 1.0 - 1E-3,... %
    // Acceleration ramp used in the optimisation 'FeedoptDefaultConfig:27'
    // 'VEL_RAMP_OVER_WINDOWS', 1.0 - 1E-3,... % Velocity ramp used in the optimisation
    // 'FeedoptDefaultConfig:28'     'SLACK_PENALTY', 10000, ...             % Slack penalty
    // 'FeedoptDefaultConfig:29'     'USE_LENGTH_SCALING', false, ...        % Use diagonal length
    // scaling 'FeedoptDefaultConfig:30'     'USE_LINPROG', false,...                % Use Linprog
    // solver 'FeedoptDefaultConfig:31'     'FORCE_POSITIV_COEFFS', false...        % For the use of
    // positiv coefficients 'FeedoptDefaultConfig:32'     );
    //                        % Optimisation type
    //         % Use jerk constraints
    //    % Find the reason of the infeasibility
    //  % Acceleration ramp used in the optimisation
    //  % Velocity ramp used in the optimisation
    //              % Slack penalty
    //         % Use diagonal length scaling
    //                 % Use Linprog solver
    //         % For the use of positiv coefficients
    // 'FeedoptDefaultConfig:34' if( ~coder.target('MATLAB') )
    // 'FeedoptDefaultConfig:35' coder.cstructname( LP,          StructTypeName.LPCfg );
    //  To use XSR manual CAM offset
    // 'FeedoptDefaultConfig:39' use_XSR_offset = true;
    // 'FeedoptDefaultConfig:41' if( use_XSR_offset )
    // 'FeedoptDefaultConfig:42' offM = [ 0, 0, 0 ]';
    // 'FeedoptDefaultConfig:43' offT = [ 0, 0, 0 ]';
    // 'FeedoptDefaultConfig:44' offP = [ 0.07155, -0.1645, 1.6 ]';
    // 'FeedoptDefaultConfig:45' offB = [ 0, 0, 0 ]';
    // 'FeedoptDefaultConfig:46' offC = [ 0, 0, 0 ]';
    // 'FeedoptDefaultConfig:55' kin_params  = [ offM offT offP offB offC ];
    // 'FeedoptDefaultConfig:56' kin_type    = 'xyzbc_tt';
    // 'FeedoptDefaultConfig:58' cfg = struct(...
    // 'FeedoptDefaultConfig:59'     'ENABLE_PRINT_MSG', true, ...                   % Enable
    // console msg 'FeedoptDefaultConfig:60'     'maskTot',  logical( [ 1, 1, 1, 0, 1, 1 ] ),... %
    // [X,Y,Z,A,B,C] 'FeedoptDefaultConfig:61'     'maskCart', logical( 0 ),...                    %
    // Do not modify 'FeedoptDefaultConfig:62'     'maskRot',  logical( 0 ),...                    %
    // Do not modify 'FeedoptDefaultConfig:63'     'indCart', int32( 0 ), ...                      %
    // Do not modify 'FeedoptDefaultConfig:64'     'indRot',  int32( 0 ),...                       %
    // Do not modify 'FeedoptDefaultConfig:65'     'NumberAxis', int32( 0 ), ...                   %
    // Do not modify 'FeedoptDefaultConfig:66'     'NCart',   int32( 0 ), ...                      %
    // Do not modify 'FeedoptDefaultConfig:67'     'NRot',    int32( 0 ), ...                      %
    // Do not modify 'FeedoptDefaultConfig:68'     'D', 0, ...                                     %
    // Do not modify 'FeedoptDefaultConfig:69'     'coeffD', 1, ...                                %
    // Scaling for cartesian and rotary axis 'FeedoptDefaultConfig:70'     'kin_params', reshape(
    // kin_params, [], 1 ), ... % See kinematics parameters' structure 'FeedoptDefaultConfig:71'
    // 'kin_type', kin_type, ... % Kinematics type 'FeedoptDefaultConfig:72'     'NDiscr', int32( 20
    // ),... % Number of discretization points 'FeedoptDefaultConfig:73'     'NBreak', int32( 10
    // ),... % Number of break points 'FeedoptDefaultConfig:74'     'SplitSpecialSpline', false,...
    // % Split methode specific to spline 'FeedoptDefaultConfig:75'     'ReleaseMemoryOfTheQueues',
    // true, ...  % Release memory of the queues once they're not required anymore
    // 'FeedoptDefaultConfig:76'     'UseDynamicBreakpoints',false,...       % Use a variable number
    // of breakpoints for different lengths 'FeedoptDefaultConfig:77'
    // 'UseLinearBreakpoints',true,...         % Use a linear distribution of breakpoints (else
    // sinspace) 'FeedoptDefaultConfig:78'     'DynamicBreakpointsDistance', 0.1,...   % Distance
    // between two breakpoints in mm 'FeedoptDefaultConfig:79'     'NHorz', int32( 5 ),... % Number
    // of curves used in the window for the optimisation 'FeedoptDefaultConfig:80'     'vmax',
    // [500,500,500,0, 40,50],... % Max speed per axe {[mm],[rad]} / s 'FeedoptDefaultConfig:81'
    // 'amax', [15000,15000,15000,0, 200,1000],... % Max acceleration per axe {[mm],[rad]} / s^2
    // 'FeedoptDefaultConfig:82'     'jmax', [1500000,1500000,1500000,0,10000,50000],... % Max jerk
    // per axe {[mm],[rad]} / s^3 'FeedoptDefaultConfig:83'     'LeeSplineDegree', int32( 4 ),... %
    // B Spline order used in the Lee algorithm 'FeedoptDefaultConfig:84'     'SplineDegree', int32(
    // 3 ),... % B Spline order used in the optimization 'FeedoptDefaultConfig:85'     'CutOff',
    // 1E-1,... % Length used by the transition algorithm to cut the curves
    // 'FeedoptDefaultConfig:86'     'LSplit',  3,... % Length used to cut the curves at a given
    // length 'FeedoptDefaultConfig:87'     'LSplitZero', 1,... % Length used to cut the curves for
    // a Zero start / end 'FeedoptDefaultConfig:88'     'LThresholdMax', 3,... % Maximum length used
    // in the compressing algorithm 'FeedoptDefaultConfig:89'     'LThresholdMin', 5E-1,... %
    // Minimum length used in the compressing algorithm 'FeedoptDefaultConfig:90'     'v_0', 0,
    // 'at_0', 0,... % Boundaries conditions used by the optimization 'FeedoptDefaultConfig:91'
    // 'v_1', 0, 'at_1', 0,... % Boundaries conditions used by the optimization
    // 'FeedoptDefaultConfig:92'     'dt', 1e-3, ...% Discretization time / time step
    // 'FeedoptDefaultConfig:93'     'DefaultZeroStopCount', 1,... % Number of time step passed with
    // stop 'FeedoptDefaultConfig:94'     'source', repmat(char(0), [1, 1024]),... % Path to the G
    // Code filename 'FeedoptDefaultConfig:95'     'Cusp', ... % Configuration for the CUSP step :
    // 'FeedoptDefaultConfig:96'     struct(...
    // 'FeedoptDefaultConfig:97'         'Skip', false,...       % Disable this step
    // 'FeedoptDefaultConfig:98'         'CuspThreshold', 10 ... % Cusp's threshold in degree
    // 'FeedoptDefaultConfig:99'     ),...
    // 'FeedoptDefaultConfig:100'     'Compressing', ... % Configuration for the Compressing step :
    // 'FeedoptDefaultConfig:101'     struct(...
    // 'FeedoptDefaultConfig:102'         'Skip', false,...       % Disable this step
    // 'FeedoptDefaultConfig:103'         'ColTolCosLee', cosd(tol_col_compress_deg) ... % Tolerance
    // in term of colinearity (cos of the angle) 'FeedoptDefaultConfig:104'     ),...
    // 'FeedoptDefaultConfig:105'     'Smoothing', ... % Configuration for the transition
    // 'FeedoptDefaultConfig:106'     struct( ...
    // 'FeedoptDefaultConfig:107'         'Skip', false,... % Disable this step
    // 'FeedoptDefaultConfig:108'         'ColTolCosSmooth',  cosd(tol_col_smooth_deg), ... %
    // Tolerance in term of colinearity (cos of the angle) 'FeedoptDefaultConfig:109'
    // 'ColTolSmooth',     1E-5 ... % Tolerance in term of colinearity (cos of the angle)
    // 'FeedoptDefaultConfig:110'     ), ...
    // 'FeedoptDefaultConfig:111'     'GaussLegendreN', GaussLegendreN, ... % Gauss Legendre N
    // 'FeedoptDefaultConfig:112'     'GaussLegendreX', GaussLegendreX, ... % Gauss Legendre X
    // 'FeedoptDefaultConfig:113'     'GaussLegendreW', GaussLegendreW, ... % Gauss Legendre W
    // 'FeedoptDefaultConfig:114'     'opt', LP,... % Optimisation Structure : Linear Programming
    // (LP) 'FeedoptDefaultConfig:115'     'LogFileName', 'logs/logs' ... 'FeedoptDefaultConfig:116'
    // );
    cfg->maskCart.size[0] = 1;
    cfg->maskCart.size[1] = 1;
    cfg->maskCart.data[0] = false;
    cfg->maskRot.size[0] = 1;
    cfg->maskRot.size[1] = 1;
    cfg->maskRot.data[0] = false;
    cfg->indCart.size[0] = 1;
    cfg->indCart.data[0] = 0;
    cfg->indRot.size[0] = 1;
    cfg->indRot.data[0] = 0;
    cfg->D.size[0] = 1;
    cfg->D.data[0] = 0.0;
    //                    % Enable console msg
    //  % [X,Y,Z,A,B,C]
    //                     % Do not modify
    //                       % Do not modify
    //                        % Do not modify
    //                    % Do not modify
    //                       % Do not modify
    //                                      % Do not modify
    //                                 % Scaling for cartesian and rotary axis
    //  % See kinematics parameters' structure
    //  % Kinematics type
    //  % Number of discretization points
    //  % Number of break points
    //  % Split methode specific to spline
    //   % Release memory of the queues once they're not required anymore
    //        % Use a variable number of breakpoints for different lengths
    //          % Use a linear distribution of breakpoints (else sinspace)
    //    % Distance between two breakpoints in mm
    //  % Number of curves used in the window for the optimisation
    //  % Max speed per axe {[mm],[rad]} / s
    //  % Max acceleration per axe {[mm],[rad]} / s^2
    //  % Max jerk per axe {[mm],[rad]} / s^3
    //  % B Spline order used in the Lee algorithm
    //  % B Spline order used in the optimization
    //  % Length used by the transition algorithm to cut the curves
    //  % Length used to cut the curves at a given length
    //  % Length used to cut the curves for a Zero start / end
    //  % Maximum length used in the compressing algorithm
    //  % Minimum length used in the compressing algorithm
    //  % Boundaries conditions used by the optimization
    // % Discretization time / time step
    //  % Number of time step passed with stop
    //  % Path to the G Code filename
    //  % Configuration for the CUSP step :
    //        % Disable this step
    //  % Cusp's threshold in degree
    //  % Configuration for the Compressing step :
    //        % Disable this step
    //  % Tolerance in term of colinearity (cos of the angle)
    //  % Configuration for the transition
    //  % Disable this step
    //  % Tolerance in term of colinearity (cos of the angle)
    //  % Gauss Legendre N
    //  % Gauss Legendre X
    //  % Gauss Legendre W
    //  % Optimisation Structure : Linear Programming (LP)
    // 'FeedoptDefaultConfig:118' if ~coder.target( 'MATLAB' )
    // 'FeedoptDefaultConfig:119' coder.varsize( 'cfg.indCart',       StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:120' coder.varsize( 'cfg.indRot',        StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:121' coder.varsize( 'cfg.maskTot',       StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:122' coder.varsize( 'cfg.maskCart',      StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:123' coder.varsize( 'cfg.maskRot',       StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:124' coder.varsize( 'cfg.D',             StructTypeName.dimD{ : } );
    // 'FeedoptDefaultConfig:125' coder.varsize( 'cfg.source',        StructTypeName.dimFileName{ :
    // } ); 'FeedoptDefaultConfig:126' coder.varsize( 'cfg.kin_params', StructTypeName.dimKinParams{
    // : } ); 'FeedoptDefaultConfig:127' coder.cstructname( cfg, StructTypeName.FeedoptCfg );
    // 'FeedoptDefaultConfig:130' [ cfg ] = setMachineAxisInConfig( cfg, cfg.maskTot );
    r.ENABLE_PRINT_MSG = true;
    r.maskTot.size[0] = 1;
    r.maskTot.size[1] = 6;
    for (int i{0}; i < 6; i++) {
        r.maskTot.data[i] = bv[i];
    }
    r.maskCart.size[0] = 1;
    r.maskCart.size[1] = 1;
    r.maskCart.data[0] = false;
    r.maskRot.size[0] = 1;
    r.maskRot.size[1] = 1;
    r.maskRot.data[0] = false;
    r.indCart.set_size(1);
    r.indCart[0] = 0;
    r.indRot.set_size(1);
    r.indRot[0] = 0;
    r.NumberAxis = 0;
    r.NCart = 0;
    r.NRot = 0;
    r.D.set_size(1);
    r.D[0] = 0.0;
    r.coeffD = 1.0;
    r.kin_params.size[0] = 15;
    std::copy(&dv[0], &dv[15], &r.kin_params.data[0]);
    for (int i1{0}; i1 < 8; i1++) {
        r.kin_type[i1] = kin_type[i1];
    }
    r.NDiscr = 20;
    r.NBreak = 10;
    r.SplitSpecialSpline = false;
    r.ReleaseMemoryOfTheQueues = true;
    r.UseDynamicBreakpoints = false;
    r.UseLinearBreakpoints = true;
    r.DynamicBreakpointsDistance = 0.1;
    r.NHorz = 5;
    for (int i2{0}; i2 < 6; i2++) {
        r.vmax[i2] = iv[i2];
        r.amax[i2] = iv1[i2];
        r.jmax[i2] = iv2[i2];
    }
    r.LeeSplineDegree = 4;
    r.SplineDegree = 3;
    r.CutOff = 0.1;
    r.LSplit = 3.0;
    r.LSplitZero = 1.0;
    r.LThresholdMax = 3.0;
    r.LThresholdMin = 0.5;
    r.v_0 = 0.0;
    r.at_0 = 0.0;
    r.v_1 = 0.0;
    r.at_1 = 0.0;
    r.dt = 0.001;
    r.DefaultZeroStopCount = 1.0;
    r.source.size[0] = 1;
    r.source.size[1] = 1024;
    std::memset(&r.source.data[0], 0, 1024U * sizeof(char));
    r.Cusp.Skip = false;
    r.Cusp.CuspThreshold = 10.0;
    r.Compressing.Skip = false;
    r.Compressing.ColTolCosLee = 0.86602540378443871;
    r.Smoothing.Skip = false;
    r.Smoothing.ColTolCosSmooth = 0.984807753012208;
    r.Smoothing.ColTolSmooth = 1.0E-5;
    r.GaussLegendreN = 5.0;
    for (int b_i{0}; b_i < 5; b_i++) {
        r.GaussLegendreX[b_i] = GaussLegendreX[b_i];
        r.GaussLegendreW[b_i] = GaussLegendreW[b_i];
    }
    r.opt.Type[0] = 'L';
    r.opt.Type[1] = 'P';
    r.opt.USE_JERK_CONSTRAINTS = true;
    r.opt.FIND_REASON_INFEASIBILITY = true;
    r.opt.ACC_RAMP_OVER_WINDOWS = 0.999;
    r.opt.VEL_RAMP_OVER_WINDOWS = 0.999;
    r.opt.SLACK_PENALTY = 10000.0;
    r.opt.USE_LENGTH_SCALING = false;
    r.opt.USE_LINPROG = false;
    r.opt.FORCE_POSITIV_COEFFS = false;
    for (int i3{0}; i3 < 9; i3++) {
        r.LogFileName[i3] = b_cv[i3];
    }
    b_setMachineAxisInConfig(&r, bv);
    cfg->ENABLE_PRINT_MSG = r.ENABLE_PRINT_MSG;
    cfg->maskTot.size[0] = 1;
    cfg->maskTot.size[1] = r.maskTot.size[1];
    loop_ub = r.maskTot.size[1];
    if (loop_ub - 1 >= 0) {
        std::copy(&r.maskTot.data[0], &r.maskTot.data[loop_ub], &cfg->maskTot.data[0]);
    }
    cfg->maskCart.size[0] = 1;
    cfg->maskCart.size[1] = r.maskCart.size[1];
    b_loop_ub = r.maskCart.size[1];
    if (b_loop_ub - 1 >= 0) {
        std::copy(&r.maskCart.data[0], &r.maskCart.data[b_loop_ub], &cfg->maskCart.data[0]);
    }
    cfg->maskRot.size[0] = 1;
    cfg->maskRot.size[1] = r.maskRot.size[1];
    c_loop_ub = r.maskRot.size[1];
    if (c_loop_ub - 1 >= 0) {
        std::copy(&r.maskRot.data[0], &r.maskRot.data[c_loop_ub], &cfg->maskRot.data[0]);
    }
    cfg->indCart.size[0] = r.indCart.size(0);
    d_loop_ub = r.indCart.size(0);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        cfg->indCart.data[i4] = r.indCart[i4];
    }
    cfg->indRot.size[0] = r.indRot.size(0);
    e_loop_ub = r.indRot.size(0);
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        cfg->indRot.data[i5] = r.indRot[i5];
    }
    cfg->NumberAxis = r.NumberAxis;
    cfg->NCart = r.NCart;
    cfg->NRot = r.NRot;
    cfg->D.size[0] = r.D.size(0);
    f_loop_ub = r.D.size(0);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        cfg->D.data[i6] = r.D[i6];
    }
    cfg->coeffD = r.coeffD;
    cfg->kin_params.size[0] = r.kin_params.size[0];
    g_loop_ub = r.kin_params.size[0];
    if (g_loop_ub - 1 >= 0) {
        std::copy(&r.kin_params.data[0], &r.kin_params.data[g_loop_ub], &cfg->kin_params.data[0]);
    }
    for (int i7{0}; i7 < 8; i7++) {
        cfg->kin_type[i7] = r.kin_type[i7];
    }
    cfg->NDiscr = r.NDiscr;
    cfg->NBreak = r.NBreak;
    cfg->SplitSpecialSpline = r.SplitSpecialSpline;
    cfg->ReleaseMemoryOfTheQueues = r.ReleaseMemoryOfTheQueues;
    cfg->UseDynamicBreakpoints = r.UseDynamicBreakpoints;
    cfg->UseLinearBreakpoints = r.UseLinearBreakpoints;
    cfg->DynamicBreakpointsDistance = r.DynamicBreakpointsDistance;
    cfg->NHorz = r.NHorz;
    for (int i8{0}; i8 < 6; i8++) {
        cfg->vmax[i8] = r.vmax[i8];
        cfg->amax[i8] = r.amax[i8];
        cfg->jmax[i8] = r.jmax[i8];
    }
    cfg->LeeSplineDegree = r.LeeSplineDegree;
    cfg->SplineDegree = r.SplineDegree;
    cfg->CutOff = r.CutOff;
    cfg->LSplit = r.LSplit;
    cfg->LSplitZero = r.LSplitZero;
    cfg->LThresholdMax = r.LThresholdMax;
    cfg->LThresholdMin = r.LThresholdMin;
    cfg->v_0 = r.v_0;
    cfg->at_0 = r.at_0;
    cfg->v_1 = r.v_1;
    cfg->at_1 = r.at_1;
    cfg->dt = r.dt;
    cfg->DefaultZeroStopCount = r.DefaultZeroStopCount;
    cfg->source.size[0] = 1;
    cfg->source.size[1] = r.source.size[1];
    h_loop_ub = r.source.size[1];
    if (h_loop_ub - 1 >= 0) {
        std::copy(&r.source.data[0], &r.source.data[h_loop_ub], &cfg->source.data[0]);
    }
    cfg->Cusp = r.Cusp;
    cfg->Compressing = r.Compressing;
    cfg->Smoothing = r.Smoothing;
    cfg->GaussLegendreN = r.GaussLegendreN;
    for (int c_i{0}; c_i < 5; c_i++) {
        cfg->GaussLegendreX[c_i] = r.GaussLegendreX[c_i];
        cfg->GaussLegendreW[c_i] = r.GaussLegendreW[c_i];
    }
    cfg->opt = r.opt;
    for (int i9{0}; i9 < 9; i9++) {
        cfg->LogFileName[i9] = r.LogFileName[i9];
    }
}

} // namespace ocn

//
// File trailer for FeedoptDefaultConfig.cpp
//
// [EOF]
//
