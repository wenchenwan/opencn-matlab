function spnD = CalcBspline_Lee(cfg, points)
% CalcBspline_Lee :
%
% INPUT
% cfg       : struct : Configuration variables
% points    :   nDxN : Set of points in n dimension for the spline
%
% OUTPUT
% spnD      : struct : Output spline structure

[nD, N] = size(points); % number of points in 3D/5D space
du     = sum((diff(points.').^2).');
u      = cumsum([0,du.^(1/4)]);
u      = u / u(end);  % normalize knots to interval [0...1]
knots  = [zeros(1, 3), u, ones(1, 3)];

Bl = bspline_create(cfg.LeeSplineDegree, u);

BasisVal    = zeros(N, N+2); % preallocation
BasisValDD0 = zeros(1, N+2); % preallocation
BasisValDD1 = zeros(1, N+2); % preallocation
%
for k = 1:N+2                               % evaluate basis functions at the knots
    coef           = zeros(1, N+2);
    coef(:, k)     = 1;
    %     sp             = spmak(knots, coef);
    %     BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
    BasisVal(:, k) = bspline_eval_vec(Bl, coef, u);

    %     sp2D           = fnder(sp, 2);          % evaluate 2nd derivative of basis functions @u=0,1

    [~, ~, BasisValDD0(k)] = bspline_eval(Bl, coef, 0);
    [~, ~, BasisValDD1(k)] = bspline_eval(Bl, coef, 1);
    %     BasisValDD0(k) = spval(sp2D, 0);
    %     BasisValDD1(k) = spval(sp2D, 1);
end
%
A = [BasisValDD0; BasisVal; BasisValDD1];
% warning('NOT using a sparse matrix here because it pulled the CXSparse project into generation')
% A = sparse(A);

% figure;
% spy(A)
%
bx = [0; points(1, :)'; 0];
by = [0; points(2, :)'; 0];
bz = [0; points(3, :)'; 0];
if nD == 5
    bb = [0; points(4, :)'; 0];
    bc = [0; points(5, :)'; 0];
end
%

% mmdflag = spparms('autommd'); % protect current spparms setting
% spparms('autommd',0);         % suppress pivoting
%
%tic
cx = A\bx;              % solve sparse banded linear system
cy = A\by;              % solve sparse banded linear system
cz = A\bz;              % solve sparse banded linear system
if nD == 5
    cb = A\bb;          % solve sparse banded linear system
    cc = A\bc;          % solve sparse banded linear system
end
%toc
%
% spparms('autommd',mmdflag);   % restore spparms setting
%
% sp3D = spmak(knots, [cx'; cy'; cz']);
% coder.varsize('cx', 'cy', 'cz', [1, Inf], [0, 1]);
spnD.CoeffX = cx.';
spnD.CoeffY = cy.';
spnD.CoeffZ = cz.';
if nD == 5
    spnD.CoeffB = cb.';
    spnD.CoeffC = cc.';
end
spnD.Bl = Bl;
spnD.knots = knots;end