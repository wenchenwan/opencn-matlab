function [ curvC ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
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

a = curv.a_param;
b = curv.b_param;

u1_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );

curvC = curv;

if( isEnd )
    curvC.b_param = u1_tilda;
    curvC.a_param = a + b - curvC.b_param;
    
    if( isAZeroEnd( curvC ) )
        curvC.Info.zspdmode = ZSpdMode.NZ;
    else
        curvC.Info.zspdmode = ZSpdMode.NN;
    end

else
    curvC.a_param = u1_tilda - curvC.b_param;
    if( isAZeroStart( curvC ) )
        curvC.Info.zspdmode = ZSpdMode.ZN;
    else
        curvC.Info.zspdmode = ZSpdMode.NN;
    end
end

end