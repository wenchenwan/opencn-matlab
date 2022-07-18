function y = mycot(x)
global cot_calls
y = cot(x);
cot_calls = cot_calls + 1;
end