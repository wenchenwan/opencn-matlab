function [L, Integrand, u_mid_tilda, du_tilda]  = ...
    SplineLengthApprox(ctx, Curv, u0_tilda, u1_tilda)
% computes approximately the arc length of a parametric spline

% get the sp structure
Spline=ctx.q_splines.get(Curv.sp_index);
sp = Spline.sp;

N = ctx.cfg.NGridLengthSpline;

% the ORIGINAL spline is parametrized with u_tilda
% after cut-off, new parameter is called u.
% u=0 corresponds to the first lift-off point
% u=1 corresponds to the second lift-off point
% u is NOT used in this function

% if coder.target('matlab')
%     % derivative whith respect to u_tilda !!!
%     sp1D      = fnder(sp);
%     Knots     = sp1D.knots;
% else
    Knots = sp.knots;
% end

Idx1      = find(Knots > u0_tilda, 1);
Idx2      = find(Knots < u1_tilda, 1, 'last');


u_vec_tilda     = [u0_tilda, Knots(Idx1(1):Idx2(1)), u1_tilda];
u_tilda=zeros(1, 0);
if ~coder.target('MATLAB')
    coder.varsize('u_tilda', [1, Inf], [0, 1]);
end

% N equally spaced u_tilda values between each pair of knots
% from u0_tilda until u1_tilda
for k=1:length(u_vec_tilda)-1
    
    if  ~isempty(u_tilda)
        u_tilda=u_tilda(1:end-1);
    end
    
    u_tilda=[u_tilda linspace(u_vec_tilda(k), u_vec_tilda(k+1), N)];
    
end
 
% midpoint values
u_mid_tilda     = 0.5*(u_tilda(1:end-1)+u_tilda(2:end)); % midpoint values
du_tilda        = diff(u_tilda);

% parametric derivative calculation at each midpoint value
% with respect to u_tilda
% if coder.target('rtw') || coder.target('mex')
    [~, r1Dx] = bspline_eval_vec(sp.Bl, sp.CoeffX, u_mid_tilda);
    [~, r1Dy] = bspline_eval_vec(sp.Bl, sp.CoeffY, u_mid_tilda);
    [~, r1Dz] = bspline_eval_vec(sp.Bl, sp.CoeffZ, u_mid_tilda);
    r1D = [r1Dx; r1Dy; r1Dz];
% else
%     r1D = spval(sp1D, u_mid_tilda);
% end

% length (between u0_tilda and u1_tilda) calculation by rectangles method
Integrand = MyNorm(r1D);
L         = sum(Integrand.*du_tilda);
