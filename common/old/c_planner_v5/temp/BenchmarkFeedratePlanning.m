function [Coeff, TElapsed] = BenchmarkFeedratePlanning(CurvStructs, Count)

global g_FeedoptConfig
    u_vec  = sinspace(0, 1, g_FeedoptConfig.NDiscr);
    Bl = bspline_create(0, 1, g_FeedoptConfig.SplineDegree, g_FeedoptConfig.NBreak);
    [BasisVal, BasisValD, BasisValDD, BasisIntegr] = bspline_base_eval(Bl, u_vec);
    
    Coeff = zeros(g_FeedoptConfig.MaxNCoeff, g_FeedoptConfig.NHorz);
    coder.varsize('Coeff', [FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz], [1,1]);
    tic
    for k = 1:Count
        Coeff = FeedratePlanning(CurvStructs, g_FeedoptConfig.amax, g_FeedoptConfig.jmax, ...
            g_FeedoptConfig.v_0, g_FeedoptConfig.at_0, ...
            g_FeedoptConfig.v_1, g_FeedoptConfig.at_1, ...
            BasisVal, BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, ...
            g_FeedoptConfig.NHorz);
    end
    TElapsed = toc;
    
    bspline_destroy(Bl);
end