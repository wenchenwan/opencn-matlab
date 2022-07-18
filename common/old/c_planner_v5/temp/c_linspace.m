function A = c_linspace(x0, x1, N)
    coder.varsize('A', [1, FeedoptLimits.MaxNDiscr],[0, 1]);
    A = linspace(x0, x1, int32(N));
end