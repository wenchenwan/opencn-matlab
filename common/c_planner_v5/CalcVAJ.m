function [v_norm, acc, jerk] = CalcVAJ(ctx, CurvStruct, Bl, u_vec)
%

assert(u_vec(end)<=1, 'u_vec too long!!');

[~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec);
r1D_norm             = mysqrt(sum(r1D.^2));  % norm

q_val = zeros(size(u_vec));
qD_val = zeros(size(u_vec));
qDD_val = zeros(size(u_vec));

% TODO: Optimize this with a single call to eval, and maybe a basis
% precompute?

if ~CurvStruct.UseConstJerk
    for iu = 1:numel(u_vec)
        [v1, v2, v3] = bspline_eval(Bl, CurvStruct.Coeff', u_vec(iu));
        q_val(iu) = v1;
        qD_val(iu) = v2;
        qDD_val(iu) = v3;
    end
    q_val = q_val';
    qD_val = qD_val';
    qDD_val = qDD_val';
    
    
    v_norm = bsxfun(@times, r1D_norm, mysqrt(q_val'));
    acc = bsxfun(@times, r2D, q_val') + 0.5*bsxfun(@times, r1D, qD_val');
    jerk = bsxfun(@times, r3D, (q_val.^(3/2))') + ...
        1.5*bsxfun(@times, r2D, bsxfun(@times, qD_val',mysqrt(q_val)')) + ...
        0.5*bsxfun(@times, r1D, bsxfun(@times, qDD_val',mysqrt(q_val)'));
    
else
    jps = CurvStruct.ConstJerk;
    
    
    
    if CurvStruct.zspdmode == ZSpdMode.ZN
        t = (6*u_vec/jps).^(1/3);
        uk = u_vec;
        d1uk = jps*t.^2/2;
        d2uk = jps*t;
        d3uk = jps;
    else
        t = (6*(1 - u_vec)/jps).^(1/3);
        uk = u_vec;
        [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, 1 - uk);

        d1uk = jps*t.^2/2;
        d2uk = jps*t;
        d3uk = jps;
    end
    
    r3dt = r3D.*d1uk.^3 + 3*r2D.*d1uk.*d2uk + r1D.*d3uk;
    r2dt = r2D.*d1uk.^2 + r1D.*d2uk;
    r1dt = r1D.*d1uk;
    
    v_norm = mysqrt(sum(r1dt.^2, 1));
    acc    = r2dt;
    jerk   = r3dt;
end




end