function r0D = SampleCurvStruct(ctx, CurvStruct, min_dist)
    ul = 0;
    ur = 1;
    Pl = EvalCurvStruct(ctx, CurvStruct, ul);
    Pr = EvalCurvStruct(ctx, CurvStruct, ur);
end

function SubSample(CurvStruct, ul, ur)
    
end