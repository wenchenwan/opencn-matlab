function [BasisVal, BasisValD, BasisValDD, BasisIntegr] = EvalSplineBasis(knots, d, u_vec)
%
% import splines.*
%
Bl          = BSplineBasis(knots, d);
%
BasisVal    = Bl.list_eval(u_vec); 
BasisIntegr = Bl.basis_functions.integral';
%
[M, N]      = size(BasisVal);
BasisValD   = zeros(M, N);       % preallocate for speed reasons
BasisValDD  = zeros(M, N);       % preallocate for speed reasons
%
for k = 1:N
    Coeff            = zeros(N, 1);
    Coeff(k)         = 1;
    Spl              = Function(Bl, Coeff);
    SplD             = Spl.derivative;
    SplDD            = SplD.derivative;
    BasisValD(:, k)  = SplD.fast_eval(u_vec);
    BasisValDD(:, k) = SplDD.fast_eval(u_vec);
end




