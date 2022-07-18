function a = mypolyder(u)
%MYPOLYDER Differentiate polynomial.
%
%u  = u(:).'; 
[nD, nu] = size(u);
if nu < 2
    a = 0; 
else
    a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1); 
end

