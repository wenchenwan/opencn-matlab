function result = CurvCollinear(ctx, Curv1, Curv2, ToleranceCos)

[~, V0] = EvalCurvStruct(ctx, Curv1, 1);
[~, V1] = EvalCurvStruct(ctx, Curv2, 0);

result = collinear(V0, V1, ToleranceCos);
end

