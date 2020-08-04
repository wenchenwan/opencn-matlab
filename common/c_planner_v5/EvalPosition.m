function r0D = EvalPosition(Curv, Spline, u)
    coder.varsize('r0D', [3, 1], [0,0]);
    r0D = EvalCurvStructNoCtx(Curv, Spline ,u(1));
end