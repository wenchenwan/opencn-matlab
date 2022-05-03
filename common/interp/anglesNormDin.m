function [ angles_deg ] = anglesNormDin( A0_deg, A1_deg, A1_mode, G90 ) 
%#codegen
% anglesNormDin : Compute the given vector of angles expressed in degree
% ( A1_deg ) based on the Din norm for the angle used by Beckhoff.
%
% A0_deg    : Vector of angles expressed in degree ( Starting angle )
% A1_deg    : Vector of angles expressed in degree ( End angle )
% A1_mode   : Vector mode based on the sign before the value
% G90       : (boolean) Is the absolute mode enable

if( G90 )   % Absolute mode : Recompute the correct angle
    angles_deg = recompute_angles( A0_deg, A1_deg, A1_mode );
else        % Incremental   : The angle is already correct
    angles_deg = A1_deg;
end

end

function [ angles_deg ] = recompute_angles( A0_deg, A1_deg, A1_mode )
% recompute_angles : Recompute the angles bases on the Din norm.
%       - CW        : CLockwise movement        (wrapped)
%       - CCW       : Counterclockwise movement (wrapped)
%       - Shortest  : Shorter distance          (wrapped)
% A0_deg    : See headers
% A1_deg    : See headers
% A1_mode   : See headers
%
% angles_deg : Correct angle to reach
MAX_DEGREE = 360; % Maximum value in degree

angles_deg      = A0_deg;                       % Store actual angles
A0_deg_wrapped  = mod( A0_deg, MAX_DEGREE );    % Wrapped angle
A1_deg_wrapped  = mod( A1_deg, MAX_DEGREE );    % Wrapped angle

% Compute different distances
[ delta_CW, delta_CCW ] = computeDeltaDegree( A0_deg_wrapped, ...
                                       A1_deg_wrapped, MAX_DEGREE );

N = length( A1_mode );

for j = 1 : N   % Loop over the vector elements
    switch( A1_mode( j ) )
        case ( AngleMode.CW )       % Clockwise mode
            angles_deg( j ) = angles_deg( j ) + delta_CW( j );
        case ( AngleMode.CCW )      % Counterlockwise mode
            angles_deg( j ) = angles_deg( j ) - delta_CCW( j );
        case ( AngleMode.Closest )  % Shortest distance mode
            if( delta_CCW( j ) < delta_CW( j ) )
                delta = -delta_CCW( j );
            else
                delta = delta_CW( j );
            end
            angles_deg( j ) = angles_deg( j ) + delta;
    end
end

end

function [ delta_CW, delta_CCW ] = computeDeltaDegree( A0, A1, MAX_DEGREE )
% computeDeltaDegree : Compute the distance [ 0 , 360 ] between the angles.
    delta_CW     = mod( A1 - A0, MAX_DEGREE );
    delta_CCW    = MAX_DEGREE - delta_CW; 
end

