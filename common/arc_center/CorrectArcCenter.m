% [R, Cprim] = CorrectArcCenter(P0, P1, C)
% recalculate the center point Cprim of an arc in the plane passing by P0 and P1,
% C being the approximate center point
function [R, Cprim] = CorrectArcCenter(P0, P1, C)
P1P0   = P1 - P0;
R      = 0.5*(norm(C-P0) + norm(C-P1)); % mean value of radius
%
if norm(P1P0) < 1e-6
    Cprim = C;                         % do nothing if P0 and P1 are extremely close
else
    l      = norm(P1P0);
    ep     = [P1P0(2);
             -P1P0(1)];                % bisecting line (90° rotation)
    ep     = ep/norm(ep);              % unit vector on bisecting line
    d      = sqrt(R^2 - (l/2)^2);
    M      = 0.5*(P0+P1);              % midpoint
    Cprim1 = M + d*ep;                 % two choices for the center point
    Cprim2 = M - d*ep;
    %
    if norm(C-Cprim1) < norm(C-Cprim2) % determine on which side the center point lies
        Cprim = Cprim1;
    else
        Cprim = Cprim2;
    end
end

