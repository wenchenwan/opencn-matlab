function Y = c_roots_( coeffs )
%#codegen
% c_roots_ : Compute the square root
% 
% Inputs : 
% coeffs        : Coefficient of the optimization
%
% Outputs :
% Y             : Result for the square root
if coder.target('rtw')
    Y = complex(zeros(numel(coeffs)-1, 1));
    coder.cinclude('functions.h');
    coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y), int32(numel(coeffs)));
else
    Y = roots(coeffs);
end
end
