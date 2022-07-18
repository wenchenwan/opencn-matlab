function Y = c_roots_(coeffs)
if coder.target('rtw')
    Y = complex(zeros(numel(coeffs)-1, 1));
    coder.cinclude('functions.h');
    coder.ceval('c_roots', coeffs(end:-1:1), coder.ref(Y), int32(numel(coeffs)));
else
    Y = roots(coeffs);
end
end
