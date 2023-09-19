% Compute the numerical derivatives of the position stored in a buffer
function [ buffer, v, a, j ] = numerical_derivatives( buffer, pos, dt )
    
    if(isrow(pos)), pos = pos'; end
    
    v = zeros( size( pos ) );
    a = zeros( size( pos ) );
    j = zeros( size( pos ) );

    [N,M]  = size( buffer );
    
    if( M >= 4 )
        buffer = [ buffer( : ,2 : 4 ), pos ];
    else
        buffer( :, end+1 ) = pos;
    end
    
    M = M + 1;
    if( M >= 4 )
        j = buffer( : , end-3 : end ) * [ -1, 3, -3, 1 ]' / dt^3;
    end
    if( M >= 3 )
        a = buffer( : , end-2 : end ) * [ 1, -2, 1 ]'/ dt^2;
    end
    if( M >=2 )
        v = buffer( : , end-1 : end)  * [ -1, 1 ]' / dt;
    end
end