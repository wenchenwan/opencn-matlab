function [ctx, Coeff, NCoeff, success, status, msg] = ...
    FeedratePlanning( ctx, CurvStructsArray, amax, jmax, BasisVal, ...
    BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, N_Hor)
% FeedratePlanning :
%
% Inputs
% ctx               : The context
% CurvStructsArray  : Array of structures
% amax              : Acceleration maximum
% jmax              : Jerk maximum
% BasisVal          : Functions basis evaluated
% BasisValD         : 1st derivative
% BasisValDD        : 2nd derivative
% BasisIntegr       : Integral
% Bl                : B-spline
% u_vec             : Knot vector
% N_Hor             : Number of windows (horizon)
%
% Outputs
% ctx               : See before
% Coeff             : Result of the optimization
% NCoeff            : Number of coefficients
% success           : Result of the optimization
%                   0 : Fails of the optimization
%                   1 : Success of the optimization
% status            : returned structure by the optimizer
% msg               : Message on the optimiztion process

[ctx, Coeff, NCoeff, success, status, msg] = ...
    FeedratePlanning_LP( ctx, CurvStructsArray, amax, jmax, BasisVal, ...
    BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, N_Hor);

end