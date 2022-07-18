function [ valid ] = checkParametrisation( queue )
% checkParametrisation : Check if the parametrisation of the curve is
% valide

valid = false;

N = queue.size;

curv = queue.get( 1 );

if( ~valid_curv_param( curv ) ), return; end

for k = 2 : N
    curvNext = queue.get( k );
    
    if( ~valid_curv_param( curvNext ) ), return; end
    
    if( curvNext.Info.Type == CurveType.TransP5 )  || ...
      ( curv.Info.Type == CurveType.TransP5 )
    else
        if( abs( ( curv.b_param + curv.a_param ) - 1 ) > eps )
            if( abs( curvNext.b_param - ( curv.b_param + curv.a_param ) ) > eps )
                return;
            end
        end
    end
    
    curv = curvNext;
end

if( curv.b_param + curv.a_param < 1 ), return; end

valid = true;

end

function [ valide ] = valid_curv_param( curv )
    valide = false;
    if( curv.a_param <= 0 ),    return; end
    if( curv.b_param < 0 ),     return; end
    if( curv.a_param + curv.b_param -1 > eps ), return; end
    valide = true;
end