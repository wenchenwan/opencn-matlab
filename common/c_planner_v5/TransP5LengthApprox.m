function L = TransP5LengthApprox(CurvStruct)
% Computes approximately the arc length of a parametric spline
p5    = CurvStruct.CoeffP5;
p5_1D = mypolyder(p5); % Derivative
u_vec     = linspace(0,1,10);
u_mid     = 0.5*(u_vec(1:end-1) +u_vec(2:end)); % Midpoint values
du        = diff(u_vec);
Integrand = mysqrt(sum(mypolyval(p5_1D, u_mid).^2));
L         = sum(Integrand.*du);