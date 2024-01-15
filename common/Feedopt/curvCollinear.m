function [ areCollinear ] = curvCollinear( ctx, curv1, curv2, toleranceCos )
%#codegen
% curvCollinear : Check whether or not two curves are collinear.
%
% Inputs :
% ctx           : The context of the computational chain
% curv1         : The first curve
% curv2         : The second curve
% toleranceCos  : The tolerance used to determinate the colinearity
%
% Outputs :
% areCollinear  : Are the two curves collinear
%

[~, V0] = EvalCurvStruct(ctx, curv1, 1);
[~, V1] = EvalCurvStruct(ctx, curv2, 0);

areCollinear = collinear(V0(ctx.cfg.indCart), V1(ctx.cfg.indCart), toleranceCos);
end

