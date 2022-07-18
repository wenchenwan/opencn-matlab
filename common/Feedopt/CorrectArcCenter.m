
function [R, Cprim, delta] = CorrectArcCenter(P0, P1, C)
% CorrectArcCenter : Recompute the correct center of a given arc. This is a
% required step to minimize rounding errors.
%
% P0    : 2D vector from the origin to the starting point
% P1    : 2D vector from the origin to the ending point
% C     : 2D vector from the origin to the center of the arc
%
% R     : Radius of arc
% Cprim : Corrected Center of the arc
% delta : Numerical difference between the two centers

P10 = P1 - P0;
L10 = MyNorm( P10 );
% Compute mean of radii
R   = ( MyNorm( C - P0 ) + MyNorm( C - P1 ) ) / 2; 

% Default tolerance for considering two points as supperposed 
DEFAULT_TOL_DIST = 1e-6; 

if L10 < DEFAULT_TOL_DIST
    % Points are supperposed 
    Cprim = C; delta = 0;
else

    ep  = [P10(2); -P10(1)];        % Bisecting line (90° rotation)
    ep  = ep / MyNorm(ep);          % Unit vector on bisecting line
    
    % Dealing with limit cases...
    a = R.^2 - ( L10.^2 ) / 4;
    if  a <= 0 % Center is aligned with the two points
        d = 0;
    else
        d = mysqrt(a);
    end

    delta = a;
    
    M      = 0.5*(P0+P1);           % Midpoint
    Cprim1 = M + d*ep;              % Two choices for the center point
    Cprim2 = M - d*ep;
    
    % Determine on which side the center point lies
    if MyNorm(C-Cprim1) < MyNorm(C-Cprim2) 
        Cprim = Cprim1;
    else
        Cprim = Cprim2;
    end
end

