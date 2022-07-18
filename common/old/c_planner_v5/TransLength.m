function L = TransLength(CurvStruct)
% computes numerically the arc length of a trans curve P5
p5    = CurvStruct.CoeffP5;
p5_1D = mypolyder(p5); % derivative
fh   = @(u) mysqrt(sum(mypolyval(p5_1D, u).^2)); % function handle to norm of parametric derivative
L     = integral(fh, 0, 1);