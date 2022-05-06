function spnD = CalcBspline_Lee(cfg, points)
% CalcBspline_Lee :
%
% INPUT
% cfg       : struct : Configuration variables
% points    :   nDxN : Set of points in n dimension for the spline
%
% OUTPUT
% spnD      : struct : Output spline structure

[~, N] = size(points); % number of points in nD space
nAxis = cfg.NumberAxis;

du     = sum((diff(points.').^2).');
u      = cumsum([0,du.^(1/4)]);
u      = u / u(end);  % normalize knots to interval [0...1]
knots  = [zeros(1, 3), u, ones(1, 3)];

Bl = bspline_create(cfg.LeeSplineDegree, u);

BasisVal    = zeros(N, N+2); % preallocation
BasisValDD0 = zeros(1, N+2); % preallocation
BasisValDD1 = zeros(1, N+2); % preallocation
%
for k = 1:N+2                % evaluate basis functions at the knots
    coef           = zeros(1, N+2);
    coef(:, k)     = 1;

    BasisVal(:, k) = bspline_eval_vec(Bl, coef, u);

    [~, ~, BasisValDD0(k)] = bspline_eval(Bl, coef, 0);
    [~, ~, BasisValDD1(k)] = bspline_eval(Bl, coef, 1);
end
%
A = [BasisValDD0; BasisVal; BasisValDD1];
%
b = [zeros(1, nAxis);
             points';
     zeros(1, nAxis)];
%
c = A\b;
%
spnD.coeff = c.';
spnD.Bl = Bl;
spnD.knots = knots;
end