function [ valid, ctx ] = checkZSpdmode( ctx, queue )
% checkZSpdmode : Check if the curve has valid zero speed mode.
%
% Inputs :
%   ctx     : The context of the computational chain
%   queue   : The queue of curvs
%
% Outputs :
%   valid   : Is a valid Zero Speed Mode
%   ctx     : The context of the computatinal chain
%
valid = false;

N = queue.size;

if( N == 0 ) 
    valid = true; 
    return; 
end

ctx.programmed_stop = int32( 0 );

curv = queue.get( 1 );

for k = 2 : N
    curvNext = queue.get( k );

    if( isAZeroEnd( curv ) && ~isAZeroStart( curvNext ) || ...
       ~isAZeroEnd( curv ) &&  isAZeroStart( curvNext ) )
        return;
    end
    
    if( isAZeroSpeed( curv ) )
        ctx.programmed_stop = ctx.programmed_stop + 1;
    end

    curv = curvNext;
end

valid = true;

end
