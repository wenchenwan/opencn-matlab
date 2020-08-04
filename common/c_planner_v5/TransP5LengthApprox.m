function L = TransP5LengthApprox(CurvStruct)
% computes approximately the arc length of a parametric spline / RHG
p5    = CurvStruct.CoeffP5;
p5_1D = mypolyder(p5); % derivative
u_vec     = linspace(0,1,10);
u_mid     = 0.5*(u_vec(1:end-1) +u_vec(2:end)); % midpoint values
du        = diff(u_vec);
Integrand = sqrt(sum(mypolyval(p5_1D, u_mid).^2));
L         = sum(Integrand.*du);