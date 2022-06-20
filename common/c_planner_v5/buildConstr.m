function [ A, b, Aeq, beq, continuity ] = buildConstr( ctx, windowCurv, amax, ...
    v_0, at_0, v_1, at_1, BasisVal, BasisValD, u_vec )
%#codegen

c_prof_in(mfilename);
% Ndim     : number of dimention
% NWindow  : number of axes
Ndim        = ctx.cfg.NumberAxis;
Nwindow     = length( windowCurv );

% M     : number of discretization
% N     : number of coefficients
% Nx    : number of decision variable
% Nc    : number of inequality constraints
% Nec   : number of equality constraints
[ M, N ]    = size( BasisVal );               
Nx          = N * Nwindow;
Nc          = ( 2 + 2 * Ndim );
Nec         = 2 * ( Nwindow + 1 );

% A         : Matrix for equality constraints
% b         : Vector for equality constraints
% Aeq       : Matrix for inequality constraints
% beq       : Vector for inequality constraints
% amaxTot   : Acceleration max total ( cart + rot )
% b_amax    : Vector for maximum acceleration
A           = zeros( Nc * M * Nwindow,  Nx ); 
b           = zeros( Nc * M * Nwindow,  1 );   
Aeq         = zeros( Nec, Nx );
beq         = zeros( Nec, 1 );
amaxTot     = amax( ctx.cfg.maskTot );
b_amax      = repmat( amaxTot, M, 1 );

% at_norm   : Norm of tangential acceleration vector
% t_vec     : Unit vector tangential to the curve
% Acc       : Matrix of the acceleration by axis
% Aw        : Cell of the matrix of inequality const. by window
% bw        : Cell of the vector of inequality const. by window
% indAT     : Indexis for at_norm at continuity points
% mask_continuity : Mask used in the recursive form the continuity equ.
at_norm     = zeros( 2, N, Nwindow );
t_vec       = zeros( Ndim, 2, Nwindow );
v2_vec      = zeros( 2, N, Nwindow );
Acc         = zeros( M * Ndim , N, 2 );
indAT       = ( int32( 1 : Ndim ) - 1 ) * M  + int32( [ 1 ; M ] );
mask_continuity = [ 1; 1; -1; -1 ];
v_max       = zeros( Ndim + 1, M );

for k = 1 : Nwindow
    % Compute the partial derivatives    
    [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec );
    
    if( windowCurv( k ).Info.TRAFO )
        [ ~, r1D_a, r2D_a ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
        r1D_r    = r1D;
    else
        [ r1D_r ] = ctx.kin.v_relative( r0D, r1D );
        r1D_a    = r1D;
        r2D_a    = r2D;
    end

    % Tangent unit vector at start and at end
    normR1D = vecnorm( r1D );
    t_vec( : , :, k ) = r1D( :, [ 1, end ] ) ./ normR1D( [1, end] );
   
    v_max( 1 : Ndim, : ) = ( ctx.cfg.vmax( ctx.cfg.maskTot ).'./ r1D_a ).^2;

    % Maximum constraint on the speed
    v_max( end, : ) = ( windowCurv( k ).Info.FeedRate ./ ...
        vecnorm( r1D_r( ctx.cfg.indCart, : ) ) ).^2;
    
    f_max = min( v_max, [], 1 );

    for j = 1 : Ndim    % Compute the acceleration matrix
        ind = int32( 1 : M ) + ( j - 1 ) * M ;
        Acc( ind, :, 1 ) = r2D_a( j, : )' .* BasisVal + 0.5 * r1D_a( j, : )' .* BasisValD;
        Acc( ind, :, 2 ) = r2D( j, : )'   .* BasisVal + 0.5 * r1D( j, : )'   .* BasisValD;
    end

    % Inequality constraints
    indAL   = int32( 1 : Nc * M ) + ( k - 1 ) * Nc * M;
    indAC   = int32( 1 : N  ) + ( k - 1 ) * N;
    A( indAL, indAC )   = [ BasisVal; -BasisVal ; Acc( :, :, 1) ; -Acc( :, :, 1) ];
    b( indAL )          = [ f_max'; zeros( size(f_max) )'; 
                            b_amax( : ); b_amax( : ) ];

    % Continuity equations
    indAEL  = int32( 1 : 4 ) + ( k - 1 ) * 2 ;      % Line   index
    indAEC  = int32( 1 : N ) + ( k - 1 ) * N ;      % Column index
    at_norm( 1, :, k )   = t_vec( : , 1, k )' * Acc( indAT( 1, : ) , :, 2 );
    at_norm( 2, :, k )   = t_vec( : , 2, k )' * Acc( indAT( 2, : ) , :, 2 );

    v2_vec( :, :, k ) = normR1D( [1, end] ).^2' .* BasisVal( [ 1; end ], :);
    continuity = [ v2_vec( 1, :, k ); at_norm( 1, :, k ); ...
                   v2_vec( 2, :, k ); at_norm( 2, :, k ) ];
    Aeq( indAEL, indAEC ) = Aeq( indAEL, indAEC ) + continuity.* mask_continuity;
end

beq( [ 1, 2, end-1, end ] ) = [ v_0^2; at_0; v_1^2; at_1 ] .* mask_continuity;

% Add a ramp on the acceleration and speed limits
vel_ramp = linspace( 1, ctx.cfg.opt.VEL_RAMP_OVER_WINDOWS, M )';
acc_ramp = repmat( linspace( 1, ctx.cfg.opt.ACC_RAMP_OVER_WINDOWS, M )',1, Nc -1 );

if( Nwindow > 1 )
    ramp = [ones(M, Nc ), vel_ramp, acc_ramp, ...
            repmat([vel_ramp(end), acc_ramp(end,:)], M, Nwindow-2)];
    b  = b .* ramp(:);
end

A = [ -ones( size( A, 2 ) );      A ];
b = [ zeros( size( A, 2 ), 1 );   b ];

% Continuity equations
continuity = [ v2_vec( 2, : , 1 ); at_norm( 2, :, 1 ) ];

c_prof_out(mfilename);

end

