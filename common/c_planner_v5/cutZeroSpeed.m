function [ curvS, curvM, curvE ] = cutZeroSpeed( ctx, curv )
% cutZeroSpeed : Cut the curv in three part depending of the zero speed
% Input :
% curv  : The curve struct with a zero speed
% Outputs :
% curvS : The curve struct with a zero start  ( ZN )
% curvM : The curve struct with no zero speed ( NN )
% curvE : The curve struct with a zero end    ( NZ )

curvS = curv;
curvM = curvS;
curvE = curvS;

if( ~isAZeroSpeed( curv ) ), return; end % Error : Not a zero speed

if( isAZeroStart( curv ) )
    % cut zero Start
    [ curvS, curvM ] = cutZeroStart( ctx, curvM );
end

if( isAZeroEnd( curv ) )
    % cut zero End
    [ curvM, curvE ] = cutZeroEnd( ctx, curvM );
end


end
