function L = SplineLengthApproxSP(sp, u0, u1)
% Computes approximately the arc length of a parametric spline

sp1D      = fnder(sp); % Derivative
Knots     = sp1D.knots;
Idx1      = find(Knots > u0, 1);
Idx2      = find(Knots < u1, 1, 'last');

u_vec     = [u0 Knots(Idx1:Idx2) u1];
u=[];

for k=1:length(u_vec)-1
    
    if  ~isempty(u)
        u=u(1:end-1);
    end
    
    u=[u linspace(u_vec(k), u_vec(k+1), 10)];
    
end

u_mid     = 0.5*(u(1:end-1)+u(2:end)); % Midpoint values
du        = diff(u);
Integrand = mysqrt(sum(spval(sp1D, u_mid).^2));
L         = sum(Integrand.*du);