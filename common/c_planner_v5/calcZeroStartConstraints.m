function [ v_0, at_0 ] = calcZeroStartConstraints( ctx, Curv )
    % calcZeroStartConstraints : Compute the velocity and acceleration 
    % required for the continuity at zero start.  
    % Inputs : 
    % ctx   : The context
    % Curv  : The curve
    % Outputs : 
    % v_0   : Norm of the velocity
    % at_0  : Norm of the tangential acceleration
    jps = Curv.ConstJerk;
    
    [ ~, ud, udd, ~ ] = constJerkU( jps, ctx.cfg.dt, false, Curv.a_param, ...
                        Curv.b_param );

    [~, r1D, r2D] = EvalCurvStruct( ctx, Curv, 1 );
   
    V = r1D .* ud;
    A = r2D .* ud .^2 + r1D .* udd;
    
    norm_vt = mysqrt( sum( V.^2, 1 ) );
    t_end   = r1D / MyNorm( r1D );
    
    v_0  = norm_vt;
    at_0 = norm( A.*t_end );
end