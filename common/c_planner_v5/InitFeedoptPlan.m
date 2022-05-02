function ctx = InitFeedoptPlan(cfg)
%#codegen
coder.inline("never");
% ctx is the context variable, it should contain:
% - op: Operation to execute
% - go_next:    Should we optimize the next segment
% - q_gcode:    GCode queue
% - q_smooth:   Queue for smoothed segments
% - q_split:    Queue after splitting
% - q_opt:      Queue after optimization

    if cfg.UseLinearBreakpoints
        Bl = bspline_create(cfg.SplineDegree, linspace(0, 1, cfg.NBreak));
        u_vec = linspace(0, 1, cfg.NDiscr);
    else
        Bl = bspline_create(cfg.SplineDegree, sinspace(0, 1, cfg.NBreak));
        u_vec = sinspace(0, 1, cfg.NDiscr);
    end
    
    
    if ~coder.target('matlab')
        coder.varsize('BasisVal', [Inf, Inf], [1, 1]);
        coder.varsize('BasisValD', [Inf, Inf], [1, 1]);
        coder.varsize('BasisValDD', [Inf, Inf], [1, 1]);
        coder.varsize('BasisIntegr', [Inf, 1], [1 0]);
    end
    [BasisVal, BasisValD, BasisValDD, ~, BasisIntegr] = bspline_base_eval(Bl, u_vec);

    Coeff = zeros(0, 0);

    Curv            = ConstrCurvStructType();
    Spline          = CalcBspline_Lee(cfg, [[0,0,0]', [1,1,1]']);
    Curv.sp         = Spline;
    Curv.sp.knots   = 0;
    Curv.sp.Ltot    = 0;
    Curv.sp.Lk      = 0;
    
    ctx.op          = Fopt.Init;
    ctx.go_next     = false;
    ctx.q_gcode     = queue(Curv);
    ctx.q_compress  = queue(Curv);
    ctx.q_splines   = queue(Curv);
    ctx.q_smooth    = queue(Curv);
    ctx.q_split     = queue(Curv);
    ctx.q_opt       = queue(Curv);

    ctx.try_push_again = false;
    ctx.n_optimized = int32(0);
    ctx.reached_end = false;
    ctx.k0 = int32(1);
    ctx.v_0 = cfg.v_0;
    ctx.v_1 = cfg.v_1;
    ctx.at_0 = cfg.at_0;
    ctx.at_1 = cfg.at_1;
    ctx.cfg = cfg;
    ctx.Bl = Bl;
    ctx.u_vec = u_vec;
    ctx.errcode = FeedoptPlanError.Success;
    ctx.jmax_increase_count = int32(0);
    ctx.zero_start = false;
    ctx.zero_end = false;
    ctx.simplex_calls = int32(0);
    
    ctx.forced_stop = int32(0);
    ctx.programmed_stop = int32(0);

    
    if ~coder.target('matlab')
        coder.varsize('ctx.BasisVal', [Inf, Inf], [1, 1]);
        coder.varsize('ctx.BasisValD', [Inf, Inf], [1, 1]);
        coder.varsize('ctx.BasisValDD', [Inf, Inf], [1, 1]);
        coder.varsize('ctx.BasisIntegr', [Inf, 1], [1 0]);
        coder.varsize('ctx.u_vec', [1, Inf], [0, 1]);
        coder.varsize('ctx.Coeff', [Inf, Inf], [1 1]);
        coder.varsize('ctx.Bl.breakpoints', [1, Inf], [0, 1]);
    end
    
    ctx.BasisVal = BasisVal;
    ctx.BasisValD = BasisValD;
    ctx.BasisValDD = BasisValDD;
    ctx.BasisIntegr = BasisIntegr;
    
    ctx.Coeff = Coeff;
    ctx.Skipped = int32(0);
    coder.cstructname(ctx, 'FeedoptContext');
    
    % Push the dummy spline curv
    ctx.q_splines.push(Curv);
    
end
