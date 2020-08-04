function [CurvStruct1, CurvStruct2] = CutZeroEnd(ctx, CurvStruct, k0)
    cfg=ctx.cfg;
    [~, r1D] = EvalCurvStruct(ctx, CurvStruct, 0);
    jps = min(cfg.jmax) / max(abs(r1D));
    
    dt = cfg.dt;
    tmax = ceil((6/jps)^(1/3)/dt)*dt;
    jps = 6/tmax^3;
    t = tmax:-dt:0;
    
    uk = jps*t.^3/6;
    d1uk = jps*t.^2/2;
    d2uk = jps*t;
    d3uk = jps;
    
    [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, uk);

    r3dt = bsxfun(@times, r3D, d1uk.^3) + 3*bsxfun(@times, r2D, d1uk.*d2uk) + bsxfun(@times, r1D, d3uk);
    r2dt = bsxfun(@times, r2D, d1uk.^2) + bsxfun(@times, r1D, d2uk);
    r1dt = bsxfun(@times, r1D, d1uk);
    
    vmax = CurvStruct.FeedRate;
    N = max(k0 - uint64(ctx.cfg.NHorz) + 1, 1);
    for k = k0:-1:N
        TmpCurv = ctx.q_gcode.get(k);
        
        vmax_tmp = GetCurvMaxFeedrate(ctx, TmpCurv);
        vmax = min(vmax, vmax_tmp);
        if TmpCurv.zspdmode == ZSpdMode.ZN
            break;
        end
    end
    
    jt = abs(bsxfun(@rdivide, r3dt.', cfg.jmax));
    at = abs(bsxfun(@rdivide, r2dt.', cfg.amax));
    norm_vt = sqrt(sum(r1dt.^2, 1))/vmax;
    norm_vt = norm_vt.';
    
    max_jt = max(jt, [], 2);
    max_at = max(at, [], 2);
    
    N = length(max_at);
    cut_index_jerk = orelse(find(max_jt.' > cfg.ZeroStartJerkLimit, 1, 'last'), 1);
    cut_index_acc = orelse(find(max_at.' > cfg.ZeroStartAccLimit, 1, 'last'), 1);
    cut_index_vel = orelse(find(norm_vt.' > cfg.ZeroStartVelLimit, 1, 'last'), 1);
    
    cut_index = max([cut_index_acc, cut_index_jerk, cut_index_vel]);
    cut_from_end = int32(max(2, N - cut_index + 1));
    cut_index = N - cut_from_end;
    
    t_cut = t(cut_index);
    actual_jps = 6/t_cut.^3;
%     actual_jps = jps;
    
%     cut_index = N + 1 - cut_index;
    u_cut = uk(cut_index);
    max_iter = int32(N - cut_index + 1);
    
    L = LengthCurv(ctx, CurvStruct, 0, 1);
    
    CurvStruct1 = CutCurvStruct(ctx, CurvStruct, 0, u_cut*L);
    
    CurvStruct2 = CutCurvStruct(ctx, CurvStruct, L - u_cut*L, 0);
    CurvStruct2.ConstJerkMaxIterations = max_iter;
    CurvStruct2.UseConstJerk = true;
    CurvStruct2.ConstJerk = actual_jps;
    
    CurvStruct1.zspdmode = ZSpdMode.NN;
    CurvStruct2.zspdmode = ZSpdMode.NZ;
    
    CurvStruct1.gcode_source_line = CurvStruct.gcode_source_line;
    CurvStruct2.gcode_source_line = CurvStruct.gcode_source_line;
end
