function y = mysin(x)
global sin_calls
y = sin(x);
sin_calls = sin_calls + 1;
end