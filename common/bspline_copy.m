function Copy = bspline_copy(Bl)
    coder.inline("never");
    Copy = bspline_create(Bl.degree, Bl.breakpoints);
end