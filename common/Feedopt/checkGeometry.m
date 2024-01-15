function [ valid ] = checkGeometry( queueCurv )
% checkZSpdmode : Check if the queue have two folowing curvs with the same 
% geometry.
%
% Inputs :
%   queueCurv   : A queue a curvStructs
%
% Outputs :
%   valid       : Boolean value, TRUE means they are no same curv geometry
%                 in the whole queue.
%
valid = false;

N = queueCurv.size;

if( N == 0 ) 
    valid = true; 
    return; 
end

curv = queueCurv.get( 1 );

for k = 2 : N
    curvNext = queueCurv.get( k );

    if( isSameGeometry(curv, curvNext) )
        return;
    end

    curv = curvNext;
end

valid = true;

end
