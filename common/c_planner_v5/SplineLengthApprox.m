function [L, Integrand, u_mid_tilda, du_tilda]  = SplineLengthApprox(ctx, Curv, u0, u1)
% computes approximately the arc length of a parametric spline / RHG / BR


Spline=ctx.q_splines.get(Curv.sp_index);
sp = Spline.sp;

a = Curv.a_param;
b = Curv.b_param;

u0_tilda = a*u0+b;
u1_tilda = a*u1+b;

if coder.target('matlab')
    sp1D      = fnder(sp); % derivative
    Knots     = sp1D.knots;
else
    Knots = sp.knots;
end

Idx1      = find(Knots > u0_tilda, 1);
Idx2      = find(Knots < u1_tilda, 1, 'last');


u_vec_tilda     = [u0_tilda, Knots(Idx1(1):Idx2(1)), u1_tilda];

u_tilda=zeros(1, 0);
coder.varsize('u_tilda', [1, Inf], [0, 1]);

for k=1:length(u_vec_tilda)-1
    
    if  ~isempty(u_tilda)
        u_tilda=u_tilda(1:end-1);
    end
    
    u_tilda=[u_tilda linspace(u_vec_tilda(k), u_vec_tilda(k+1), 100)];
    
end

u_mid_tilda     = 0.5*(u_tilda(1:end-1)+u_tilda(2:end)); % midpoint values
du_tilda        = diff(u_tilda);

if coder.target('rtw') || coder.target('mex')
    [~, r1Dx] = bspline_eval_vec(sp.Bl, sp.CoeffX, u_mid_tilda);
    [~, r1Dy] = bspline_eval_vec(sp.Bl, sp.CoeffY, u_mid_tilda);
    [~, r1Dz] = bspline_eval_vec(sp.Bl, sp.CoeffZ, u_mid_tilda);
    r1D = [r1Dx; r1Dy; r1Dz];
else
    r1D = spval(sp1D, u_mid_tilda);
end

r1D = a.*r1D;

Integrand = MyNorm(r1D);
L         = sum(Integrand.*du_tilda);
