function [ ret, curvLeft, curvRight ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
%#codegen
% cutCurvStruct: Cut a piece of the structure with a size of L
% starting at point u0.
%
% Inputs :
% ctx   : Context
% curv  : Curvature
% u0    : Starting point of the spline
% L     : Length of the segment of curv
% isEnd : Is a zero stop curv
% 
% Outputs :
% ret       : Return 0 if operation fails
% curvLeft  : Left curve after cutting
% curvRight : Right curve after cutting
%
curvLeft = curv; curvRight = curvLeft;
ret   = 0;

u_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );

if( u_tilda <= 0 ), ret = -1; return; end

a = curv.a_param;
b = curv.b_param;

curvRight.b_param = u_tilda;
curvRight.a_param = a + b - curvRight.b_param;

if( isAZeroEnd( curvRight ) )
    curvRight.Info.zspdmode = ZSpdMode.NZ;
else
    curvRight.Info.zspdmode = ZSpdMode.NN;
end

ocn_assert( checkParametrisation( curvRight ), ...
    "Parametrisation is not correct...", mfilename );

curvLeft.a_param = u_tilda - curvLeft.b_param;
if( isAZeroStart( curvLeft ) )
    curvLeft.Info.zspdmode = ZSpdMode.ZN;
else
    curvLeft.Info.zspdmode = ZSpdMode.NN;
end

ocn_assert( checkParametrisation( curvLeft ), ...
    "Parametrisation is not correct...", mfilename  );

end
