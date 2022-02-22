function [CurvStruct1, CurvStruct2] = CutZeroStart(ctx, CurvStruct, k0)
    cfg=ctx.cfg;
    [~, r1D] = EvalCurvStruct(ctx, CurvStruct, 0);
    jps = min(cfg.jmax) / max(abs(r1D));
    
    dt = cfg.dt;
    tmax = ceil((6/jps)^(1/3)/dt)*dt;
    jps = 6/tmax^3;
    t = 0:dt:tmax;
    
    uk = jps*t.^3/6;
    d1uk = jps*t.^2/2;
    d2uk = jps*t;
    d3uk = jps;
    
    [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, uk);

    r3dt = bsxfun(@times, r3D, d1uk.^3) + 3*bsxfun(@times, r2D, d1uk.*d2uk) + bsxfun(@times, r1D, d3uk);
    r2dt = bsxfun(@times, r2D, d1uk.^2) + bsxfun(@times, r1D, d2uk);
    r1dt = bsxfun(@times, r1D, d1uk);
    
    vmax = CurvStruct.FeedRate;
    N = min(int64(k0 + ctx.cfg.NHorz - 1), int64(ctx.q_gcode.size()));
  
    for k = k0:N
        TmpCurv = ctx.q_gcode.get(k);
        
        vmax_tmp = GetCurvMaxFeedrate(ctx, TmpCurv);
        vmax = min(vmax, vmax_tmp);
        if TmpCurv.zspdmode == ZSpdMode.NZ
            break;
        end
    end
    
    jt = abs(bsxfun(@rdivide, r3dt.', cfg.jmax));
    at = abs(bsxfun(@rdivide, r2dt.', cfg.amax));
    norm_vt = mysqrt(sum(r1dt.^2, 1))/vmax;
    norm_vt = norm_vt.';
    
    max_jt = max(jt, [], 2);
    max_at = max(at, [], 2);
    
    N = length(max_jt);
    
    cut_index_jerk = orelse(find(max_jt.' > cfg.ZeroStartJerkLimit, 1), N);
    cut_index_acc = orelse(find(max_at.' > cfg.ZeroStartAccLimit, 1), N);
    cut_index_vel = orelse(find(norm_vt.' > cfg.ZeroStartVelLimit, 1), N);
    
    cut_index = min([cut_index_acc, cut_index_jerk, cut_index_vel]);
    cut_index = max(2, int32(cut_index) - 1);
    cut_index = min(int32(N/2), cut_index);
    u_cut = uk(cut_index);
    t_cut = t(cut_index);
    L = LengthCurv(ctx, CurvStruct, 0, 1);
    
    actual_jps = 6/t_cut.^3;
    
    CurvStruct1 = CutCurvStruct(ctx, CurvStruct, 0, L - u_cut*L);
    CurvStruct1.UseConstJerk = true;
    CurvStruct1.ConstJerk = actual_jps;
    CurvStruct1.ConstJerkMaxIterations = int32(cut_index);
    CurvStruct2 = CutCurvStruct(ctx, CurvStruct, u_cut*L, 0);
    
    norm_vt_at_index = norm_vt(cut_index);
    
    CurvStruct1.zspdmode = ZSpdMode.ZN;
    CurvStruct2.zspdmode = ZSpdMode.NN;
    
    CurvStruct1.gcode_source_line = CurvStruct.gcode_source_line;
    CurvStruct2.gcode_source_line = CurvStruct.gcode_source_line;
    
    if ctx.cfg.DebugCutZero
        fprintf('======== CUT ZERO START =========\n');
        fprintf('Initial: \n');
        PrintCurvStruct(ctx, CurvStruct);
        
        fprintf('\nCut:\n');
        fprintf('Index = %d, t_cut = %e, vmax = %.1f\n', cut_index, t_cut, vmax);
        fprintf('jps = %e, norm_vt(%d) = %f\n', jps, cut_index, norm_vt_at_index);
        
        PrintCurvStruct(ctx, CurvStruct1);
        PrintCurvStruct(ctx, CurvStruct2);
    end
end
