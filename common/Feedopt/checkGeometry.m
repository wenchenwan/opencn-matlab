function [ valid ] = checkGeometry( queue )
% checkZSpdmode : Check if the queue has a valid geometry

valid = false;

N = queue.size;

if( N == 0 ) 
    valid = true; 
    return; 
end

curv = queue.get( 1 );

for k = 2 : N
    curvNext = queue.get( k );

    if( isSameGeometry(curv, curvNext) )
        return;
    end

    curv = curvNext;
end

valid = true;

end