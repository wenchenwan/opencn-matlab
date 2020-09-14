function [v_0, at_0] = CalcZeroStartConstraints(ctx, Curv, JerkScale)
    c_assert(Curv.UseConstJerk, 'CalcZeroStartConstraints: Called on non-const jerk');
    jps = Curv.ConstJerk*JerkScale;
    u = 1;
    t = (6*u/jps)^(1/3);
    d1uk = jps*t.^2/2;
    d2uk = jps*t;
    
    [~, r1D, r2D] = EvalCurvStruct(ctx, Curv, u);
    
    r2dt = bsxfun(@times, r2D, d1uk.^2) + bsxfun(@times, r1D, d2uk);
    r1dt = bsxfun(@times, r1D, d1uk);
    
    norm_vt = mysqrt(sum(r1dt.^2, 1));
    t_end = r1D/MyNorm(r1D);
    
    v_0 = norm_vt;
    at_0 = norm(r2dt.*t_end);
end