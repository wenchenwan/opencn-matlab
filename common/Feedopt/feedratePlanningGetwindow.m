function [ window, NWindow ] = feedratePlanningGetwindow( k0, NHorz, q_curves )

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