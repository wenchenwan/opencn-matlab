function [ r0D, r1D, r2D, r3D ] = EvalSpline( CurvStruct, u_vec, q_spline )
%#codegen
% EvalSpline :
%
% Input 
% CurvStruct    : struct : CurvStruct of type spline
% u_vec         :    1xn : Vector for evaluation of the curv
% q_spline      :        : Queue of the spline
%
% Output
% r0D           :   nDxn : Evaluation of the line at u\_vec points
% r1D           :   nDxn : 1rst order parametric derivative for the line at u\_vec points
% r2D           :   nDxn : 2nd order parametric derivative for the line at u\_vec points
% r3D           :   nDxn : 3rd order parametric derivative for the line at u\_vec points

ptr    = CurvStruct.sp_index;
spline = q_spline.get( ptr );

[ r0D, r1D, r2D, r3D ] = EvalBSpline( spline, u_vec );