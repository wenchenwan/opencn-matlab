function [ state ] = resampleCurvOCN( state, Bl, curv_mode, ...
    coeff, constJerk, dt, GaussLegendreX, GaussLegendreW, enablePrint )
%#codegen
% resampleCurvOCN : Interface for a call from the real target (See.
% resampleCurv).
[ state ] = resampleCurv(state, Bl, curv_mode, coeff, constJerk, dt, ...
    GaussLegendreX, GaussLegendreW, enablePrint );

end
