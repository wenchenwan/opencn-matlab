function x = sinspace(x0, x1, N)
t = linspace(-1,0,N);
if coder.target('rtw')
    coder.varsize('x', [1, Inf], [0, 1]);
end
x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
end
