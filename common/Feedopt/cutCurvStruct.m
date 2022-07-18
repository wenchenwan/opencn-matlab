function [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
% cutCurvStruct: Cut a piece of the structure with a size of L
% starting at point u0
% Inputs :
% ctx   : Context
% curv  : Curvature
% u0    : Starting point of the spline
% L     : Length of the segment of curv
% isEnd : Is a zero stop curv
% Outputs :
% u1    : The last point of the splitted curv
curv1 = curv; curv2 = curv1;
ret   = 0;

u_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );

if( u_tilda <= 0 ), ret = -1; return; end

a = curv.a_param;
b = curv.b_param;

curv2.b_param = u_tilda;
curv2.a_param = a + b - curv2.b_param;

if( isAZeroEnd( curv2 ) )
    curv2.Info.zspdmode = ZSpdMode.NZ;
else
    curv2.Info.zspdmode = ZSpdMode.NN;
end

curv1.a_param = u_tilda - curv1.b_param;
if( isAZeroStart( curv1 ) )
    curv1.Info.zspdmode = ZSpdMode.ZN;
else
    curv1.Info.zspdmode = ZSpdMode.NN;
end

end