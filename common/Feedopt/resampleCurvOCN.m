function [ state ] = resampleCurvOCN( state, Bl, curv_mode, ...
    coeff, constJerk, dt, GaussLegendreX, GaussLegendreW )
% resampleCurvOCN :
% Interface for the resampling in ocn
[ state ] = resampleCurv(state, Bl, curv_mode, coeff, constJerk, dt, ...
    GaussLegendreX, GaussLegendreW );

end