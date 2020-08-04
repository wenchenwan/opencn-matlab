function Copy = bspline_copy(Bl)
    Copy = bspline_create(Bl.degree, Bl.breakpoints);
end