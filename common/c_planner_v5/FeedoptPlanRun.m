function ctx = FeedoptPlanRun(ctx)
coder.updateBuildInfo('addDefines', 'MEX_FEEDOPTPLANRUN')
coder.updateBuildInfo('addIncludePaths','$(START_DIR)/gen_mex/feedoptplanrun');
coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
while ctx.op ~= Fopt.Opt
    [ctx, optimized, opt_curv] = FeedoptPlan(ctx);
    if optimized
        ctx.go_next = true;
        ctx.q_opt.push(opt_curv);
    end
end
    DebugLog(DebugCfg.Transitions, 'End.\n');
end