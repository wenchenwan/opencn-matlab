function [ k ] = computeContinuityMat( ctx, curv, u, ud, udd, isEnd )
    u_vec       = ctx.u_vec;
    BasisVal    = ctx.BasisVal;
    BasisValD   = ctx.BasisValD;
    b           = [ 0, u( 1 : end -1 ) ];
    a           = [ u( 1 ), diff( u ) ];

    if( isEnd )
        u           = flip( u );
        ud          = flip( ud );
        udd         = flip( udd );
        u_vec       = flip( u_vec );
        BasisVal    = flip( BasisVal, 2 );
        BasisValD   = flip( BasisValD, 2 );
        b           = flip( b );
        a           = flip( a );
    end
    
    [ N ]   = length( ud );               
   
    u_tot   = [ u ; a * u_vec( 2 ) + b ];

    u_tot   = u_tot( : )';

    [ ~ , r1D, r2D ] = EvalCurvStruct( ctx, curv, u_tot );

    ind = 1 : 2 : 2 * N;
    M   = size( BasisValD, 2);
    % Tangent unit vector at start and at end
    normR1D = vecnorm( r1D( :, ind ) );
    t_vec   = r1D( :, ind ) ./ normR1D;
    
    % Compute the acceleration
    acc     = r2D( :, ind ) .* ud.^2 + r1D( :, ind ) .* udd;
    % Compute the norm of the velocity
    v2_vec  = normR1D.^2 .* ud.^2;
    % Compute the norm of the tangential acceleration
    at_norm = zeros( size( v2_vec ) ); 
    for j = 1 : N
        at_norm( j ) = t_vec( :,  j )' * acc( :, j );
    end

    % Compute the norm of the velocity for q( u ) 
    v2_mat  = normR1D'.^2 .* BasisVal( 1, : );
    % Compute the acceleration
    s = zeros( M, 1 );
    for j = 2 * N : -2 : 1
        k = ( j ) / 2;
        acc_mat = a( k )^2 .* r2D( :, j-1 : j ) * BasisVal( 1 : 2, : ).^2 ...
                   + a( k ) * r1D( :, j-1 : j ) * BasisValD( 1 : 2, : );
        at_vec  = t_vec( :, k )' * acc_mat;

        M = [ v2_mat( k, 1 ), 0 ; at_vec( 1, 1 : 2 ) ];
        
        C = M  \ [ v2_vec( k ); at_norm( k ) ];
        if( C( 1 ) > 0 && C( 2 ) > 0 ), break; end
    end

    if( isEnd ), k = N - 1; end
end