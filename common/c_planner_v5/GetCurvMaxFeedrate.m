function Feedrate = GetCurvMaxFeedrate(ctx, CurvStruct)
    
    BaseFeedrate = 1;
    [A, J] = GetCurvPeakAJ(ctx, CurvStruct, BaseFeedrate, 10);
    NonZeroA = A ~= 0;
    NonZeroJ = J ~= 0;
    ascale = A(NonZeroA)./ctx.cfg.amax(NonZeroA)';
    jscale = J(NonZeroJ)./ctx.cfg.jmax(NonZeroJ)';
   
    if isempty(ascale) || isempty(jscale)
        Feedrate = CurvStruct.FeedRate;
    else
        ascale = max(ascale);
        jscale = max(jscale);
        Feedrate = min([BaseFeedrate/ascale.^(1/2), BaseFeedrate/jscale.^(1/3), CurvStruct.FeedRate]);
    end
end
