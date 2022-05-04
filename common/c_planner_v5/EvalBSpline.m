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
<<<<<<< HEAD
    
    nD = ctx.cfg.NCart + ctx.cfg.NRot;
% if coder.target('rtw') || coder.target('mex')
    Spline=ctx.q_splines.get(CurvStruct.sp_index);
    sp = Spline.sp;
%     sp = CurvStruct.sp; % pour tester 
    Bl = sp.Bl;
    [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
    [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
    [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
    if nD == 5
        [r0Db, r1Db, r2Db, r3Db] = bspline_eval_vec(Bl, sp.CoeffB, uvec);
        [r0Dc, r1Dc, r2Dc, r3Dc] = bspline_eval_vec(Bl, sp.CoeffC, uvec);
    else 
        r0Db = 0; r1Db = 0; r2Db = 0; r3Db = 0;
        r0Dc = 0; r1Dc = 0; r2Dc = 0; r3Dc = 0;
    end
    
    r0D = [r0Dx; r0Dy; r0Dz];
    r1D = [r1Dx; r1Dy; r1Dz];
    r2D = [r2Dx; r2Dy; r2Dz];
    r3D = [r3Dx; r3Dy; r3Dz];
    if nD == 5
        r0D = [r0Dx; r0Dy; r0Dz; r0Db; r0Dc];
        r1D = [r1Dx; r1Dy; r1Dz; r1Db; r1Dc];
        r2D = [r2Dx; r2Dy; r2Dz; r2Db; r2Dc];
        r3D = [r3Dx; r3Dy; r3Dz; r3Db; r3Dc];
    end
% else
%     Spline=ctx.q_splines.get(CurvStruct.sp_index);
%     sp = Spline.sp;
%     r0D = spval(sp, uvec);
% 
%     sp1D = fnder(sp, 1);
%     r1D = spval(sp1D, uvec);
% 
%     sp2D = fnder(sp, 2);
%     r2D = spval(sp2D, uvec);
% 
%     sp3D = fnder(sp, 3);
%     r3D = spval(sp3D, uvec);
% end
=======
sp = spline.sp;
N  = length( u_vec );
M  = size( sp.coeff, 1 );

r0D = zeros( M, N ); r1D = r0D; r2D = r1D; r3D = r2D;

for j = 1 : M
    [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ... 
                            bspline_eval_vec( Bl, sp.coeff( j, : ), u_vec );
end
>>>>>>> 628ddae114382a1f0119d134e8f35f84e6768ef4

end