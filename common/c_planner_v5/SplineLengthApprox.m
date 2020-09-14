function L = SplineLengthApprox(ctx, Curv, u0, u1)
% computes approximately the arc length of a parametric spline / RHG / BR


Spline=ctx.q_splines.get(Curv.sp_index);
sp = Spline.sp;

if coder.target('matlab')
    sp1D      = fnder(sp); % derivative
    Knots     = sp1D.knots;
else
    Knots = sp.knots;
end

Idx1      = find(Knots > u0, 1);
Idx2      = find(Knots < u1, 1, 'last');


u_vec     = [u0, Knots(Idx1(1):Idx2(1)), u1];

u=zeros(1, 0);
coder.varsize('u', [1, Inf], [0, 1]);

for k=1:length(u_vec)-1
    
    if  ~isempty(u)
        u=u(1:end-1);
    end
    
    u=[u linspace(u_vec(k), u_vec(k+1), 10)];
    
end

u_mid     = 0.5*(u(1:end-1)+u(2:end)); % midpoint values
du        = diff(u);

if coder.target('rtw') || coder.target('mex')
    [~, r1Dx] = bspline_eval_vec(sp.Bl, sp.CoeffX, u_mid);
    [~, r1Dy] = bspline_eval_vec(sp.Bl, sp.CoeffY, u_mid);
    [~, r1Dz] = bspline_eval_vec(sp.Bl, sp.CoeffZ, u_mid);
    r1D = [r1Dx; r1Dy; r1Dz];
else
    r1D = spval(sp1D, u_mid);
end

Integrand = mysqrt(sum(r1D.^2));
L         = sum(Integrand.*du);
