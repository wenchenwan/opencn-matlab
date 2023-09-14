function [ valid ] = checkZSpdmode( queue )
% checkZSpdmode : Check if the curve has valid zero speed mode

valid = false;

N = queue.size;

if( N == 0 ) 
    valid = true; 
    return; 
end

curv = queue.get( 1 );

for k = 2 : N
    curvNext = queue.get( k );

    if( isAZeroEnd( curv ) && ~isAZeroStart( curvNext ) || ...
       ~isAZeroEnd( curv ) &&  isAZeroStart( curvNext ) )
        return;
    end

    curv = curvNext;
end

valid = true;

end