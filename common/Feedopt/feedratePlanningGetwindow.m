function [ window, NWindow ] = feedratePlanningGetwindow( k0, NHorz, q_curves )
%#codegen
% feedratePlanningGetwindow : 
%
% Inputs :
%   k0          : Index in the optimization 
%   NHorz       : Number of curves in the optimization window
%   q_curves    : Queue of curve structures
%
% Outputs :
%   window      : Window of curves structure
%   NWindow     : Number of curves in the structures
%

window = repmat( constrCurvStructType, 1, NHorz );

kend = min( double( k0 + NHorz -1 ), q_curves.size );

ind = 0;

for curv_ind = k0 : int32( kend )
    ind = ind + 1;

    % store the value in the queue
    curv            = q_curves.get( curv_ind );
    window( ind )   = curv;
    % Check if zero speed at the end
    if( isAZeroEnd( curv ) ), break; end
end

NWindow = ind;
end
