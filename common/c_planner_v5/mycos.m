function y = mycos(x)
global cos_calls
y = cos(x);
cos_calls = cos_calls + 1;
end