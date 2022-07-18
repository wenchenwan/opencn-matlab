function ctx = FeedoptPlanRun( ctx )

coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')

while ctx.op ~= Fopt.Finished
    [ ctx, optimized, opt_curv ] = FeedoptPlan( ctx );
end

end