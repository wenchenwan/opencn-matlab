function [ r0D, r1D, r2D, r3D ] = EvalBSpline( spline, u_vec )
%#codegen
% EvalBSpline
%
% INPUT
% spline        : struct : Spline structure
% u_vec         :    1xn : Vector for evaluation of the curv
%
% OUTPUT
% r0D           :   nDxn : The evaluated B spline at u\_vec points
% r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec points
% r2D           :   nDxn : 2nd order parametric derivative for the B spline at u\_vec points
% r3D           :   nDxn : 3rd order parametric derivative for the B spline at u\_vec points
sp = spline.sp;
N  = length( u_vec );
M  = size( sp.coeff, 1 );

r0D = zeros( M, N ); r1D = r0D; r2D = r1D; r3D = r2D;

for j = 1 : M
    [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ... 
                            bspline_eval_vec( Bl, sp.coeff( j, : ), u_vec );
end

end
