function y = mypolyval(p, x)
%POLYVAL Evaluate array of polynomials with same degree.
%
[nD, nc] = size(p);
siz_x    = length(x);
%
% Use Horner's method for general case where X is an array.
y = zeros(nD, siz_x);
if nc > 0
    y(:) = repmat(p(:, 1), 1, siz_x); 
end
for i=2:nc
    y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
end
