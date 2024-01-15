function  [ r0D ] = evalPositionFromU( cfg, curv, spline, u )
    %#codegen
    % evalPositionFromU : Eval a curv on a set of u values. No context is
    % required, only the corresponding spline of the curve or a dummy one.
    %
    % Inputs :
    % cfg       : The configuration structure of the computational chain
    % curv      : The curve structure
    % spline    : The spline structure
    % u         : The u values
    %
    % Outputs :
    % r0D       : Matrix of points for a given set of u values
    %
    coder.inline( "never" );
    r0D = EvalCurvStructNoCtx( cfg, curv, spline, u );
end
