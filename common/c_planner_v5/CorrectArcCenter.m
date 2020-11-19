% [R, Cprim] = CorrectArcCenter(P0, P1, C)
% recalculate the center point Cprim of an arc in the plane passing by P0 and P1,
% C being the approximate center point
function [R, Cprim, delta] = CorrectArcCenter(P0, P1, C)

P1P0   = P1 - P0;
R      = 0.5*(MyNorm(C-P0) + MyNorm(C-P1)); % mean value of radius
%
if MyNorm(P1P0) < 1e-6
    Cprim = C;                         % do nothing if P0 and P1 are extremely close
    delta = 0;
else
    l      = MyNorm(P1P0);
    delta = R^2 - (l/2)^2;
    c_assert(R-l/2 > -1e-9, 'Helix center correction error !');
    
    ep     = [P1P0(2);
             -P1P0(1)];                % bisecting line (90° rotation)
    ep     = ep/MyNorm(ep);              % unit vector on bisecting line
    
    % dealing with limit cases...
    if R-l/2 < 0
        d = 0;
    else
        d = mysqrt(R^2 - (l/2)^2);
    end
    
    M      = 0.5*(P0+P1);              % midpoint
    Cprim1 = M + d*ep;                 % two choices for the center point
    Cprim2 = M - d*ep;
    %
    if MyNorm(C-Cprim1) < MyNorm(C-Cprim2) % determine on which side the center point lies
        Cprim = Cprim1;
    else
        Cprim = Cprim2;
    end
end

