function [ A_din ] = anglesNormDin( A_prev, A, A_mode, G90 ) 
%#codegen
% anglesNormDin : Compute the given vector of angles expressed in degree
% ( A_prev ) based on the Din norm for the angle used by Beckhoff.
%
% A_prev    : Vector of angles expressed in degree ( Starting angle )
% A         : Vector of angles expressed in degree ( End angle )
% A_mode    : Vector mode based on the sign before the value
% G90       : (boolean) Is the absolute mode enable

if( G90 )   % Absolute mode : Recompute the correct angle
    A_din = recompute_angles( A_prev, A, A_mode );
else        % Incremental   : The angle is already correct
    A_din = A;
end

end

function [ A_din ] = recompute_angles( A_prev, A, A_mode )
% recompute_angles : Recompute the angles bases on the Din norm.
%       - CW        : CLockwise movement        (wrapped)
%       - CCW       : Counterclockwise movement (wrapped)
%       - Shortest  : Shorter distance          (wrapped)
%
% A_din : Corrected angle
MAX_DEGREE = 360; % Maximum value in degree

A_din           = A_prev;                       % Store actual angles
A_prev_wrapped  = mod( A_prev, MAX_DEGREE );    % Wrapped angle
A_wrapped       = mod( A, MAX_DEGREE );         % Wrapped angle

% Compute different distances
[ delta_CW, delta_CCW ] = computeDeltaDegree( A_prev_wrapped, ...
                                              A_wrapped, MAX_DEGREE );

switch( A_mode )
    case ( AngleMode.CW )       % Clockwise mode
        A_din = A_din + delta_CW;
    case ( AngleMode.CCW )      % Counterlockwise mode
        A_din = A_din - delta_CCW;
    case ( AngleMode.Closest )  % Shortest distance mode
        if( delta_CCW < delta_CW )
            delta = -delta_CCW;
        else
            delta = delta_CW;
        end
        A_din = A_din + delta;
end

end

function [ delta_CW, delta_CCW ] = computeDeltaDegree( A_prev, A, MAX_DEGREE )
% computeDeltaDegree : Compute the distance [ 0 , 360 ] between the angles.
    delta_CW     = mod( A - A_prev, MAX_DEGREE );
    delta_CCW    = MAX_DEGREE - delta_CW; 
end

