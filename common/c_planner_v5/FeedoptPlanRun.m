function ctx = FeedoptPlanRun(ctx)
% coder.updateBuildInfo('addDefines', 'MEX_FEEDOPTPLANRUN')
% coder.updateBuildInfo('addIncludePaths','$(START_DIR)/gen_mex/feedoptplanrun');
coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
while ctx.op ~= Fopt.Finished
    [ctx, optimized, opt_curv] = FeedoptPlan(ctx);
end
%     DebugLog(DebugCfg.Transitions, 'End.\n');
end