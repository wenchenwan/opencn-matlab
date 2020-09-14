function y = mysqrt(x)
global sqrt_calls
y = sqrt(x);
sqrt_calls = sqrt_calls + 1;
end