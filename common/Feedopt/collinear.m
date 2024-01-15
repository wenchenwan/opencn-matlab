function [ valid ] = collinear( u, v, tol_cos )
% collinear : Check if the two vectors are collinear based on a given
% cos tolerance.
%
% Inputs :
%   u       : A vector in R^n
%   v       : A vector in R^n
%   tol_cos : A cos tolerance
%
% Outputs :
%   valid   : Boolean value, TRUE if the two vectors are collinear
%
    if ( norm( u ) < eps || norm( v ) < eps )
        valid = true;
        return;
    end
    cos_angle   = dot( u, v ) / ( MyNorm( u ) * MyNorm( v ) );
    valid       = ( cos_angle >= tol_cos );
end
