function sp3D = CalcBspline_Lee_matlab(points)

[~, N] = size(points); % number of points in 3D space
du     = sum((diff(points.').^2).'); 
u      = cumsum([0,du.^(1/4)]);
u      = u / u(end);  % normalize knots to interval [0...1]
knots  = [zeros(1, 3), u, ones(1, 3)];

BasisVal    = zeros(N, N+2); % preallocation
BasisValDD0 = zeros(1, N+2); % preallocation
BasisValDD1 = zeros(1, N+2); % preallocation
%
for k = 1:N+2                               % evaluate basis functions at the knots
    coef           = zeros(1, N+2);
    coef(:, k)     = 1;
    sp             = spmak(knots, coef);
    BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
    sp2D           = fnder(sp, 2);          % evaluate 2nd derivative of basis functions @u=0,1
    BasisValDD0(k) = spval(sp2D, 0);
    BasisValDD1(k) = spval(sp2D, 1);
end
%
A = [BasisValDD0; BasisVal; BasisValDD1]; 
A = sparse(A);

% figure;
% spy(A)
%
bx = [0; points(1, :)'; 0];
by = [0; points(2, :)'; 0];
bz = [0; points(3, :)'; 0];
%  

mmdflag = spparms('autommd'); % protect current spparms setting
spparms('autommd',0);         % suppress pivoting
%
%tic
cx = A\bx;                    % solve sparse banded linear system
cy = A\by;                    % solve sparse banded linear system
cz = A\bz;                    % solve sparse banded linear system
%toc
%
spparms('autommd',mmdflag);   % restore spparms setting
%
sp3D = spmak(knots, [cx'; cy'; cz']);






