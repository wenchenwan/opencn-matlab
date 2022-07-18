function [A,J] = GetCurvPeakAJ(ctx, CurvStruct, ConstantFeedrate, NSample)
% rdot = r1D * u1d
% rdot'*rdot = r1D'*r1D * u1d .^2
% ConstantFeedrate = r1D'*r1D * u1d .^2     (1)

    uvec = linspace(0,1,NSample);
    [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, uvec);
    
    % from (1):
    u1d = ConstantFeedrate./vecnorm(r1D, 2);
    % u2d = 0;
    % u3d = 0;
    
    r2t = bsxfun(@times, r2D, u1d.^2); % + r1D*u2d
    r3t = bsxfun(@times, r3D, u1d.^3); % + 3*r2D*u1d*u2d + r1d*u3d
    % These 2 equations tell us that to obtain the values for other
    % feedrates, they have to be multiplied by the scale.^2 and scale.^3
    
    A = max(abs(r2t), [], 2);
    J = max(abs(r3t), [], 2);
end