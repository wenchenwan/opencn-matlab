function [ Aj, bj ] = buildConstrJerk( ctx, windowCurv, coeff, jmax, ...
                    BasisVal, BasisValD, BasisValDD, u_vec )
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
[ M, N ]    = size( BasisVal );               
Nx          = N * Nwindow;
Nc          = 2 * Ndim;

% A         : Matrix for equality constraints
% b         : Vector for equality constraints
% jmaxTot   : Jerk max total ( cart + rot )
% b_jmax    : Vector for maximum jerk
Aj          = zeros( Nc * M * Nwindow,  Nx ); 
bj          = zeros( Nc * M * Nwindow,  1 );   
jmaxTot     = jmax( ctx.cfg.maskTot );
b_jmax      = repmat( jmaxTot, M, 1 );

% Jerk       : Matrix of the jerk by axis
Jerk         = zeros( M * Ndim , N );


for k = 1 : Nwindow
    % Compute the partial derivatives
    [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, windowCurv( k ), u_vec );
    
    ctx.kin = ctx.kin.set_tool_length(windowCurv( k ).tool.offset.z);

    if( windowCurv( k ).Info.TRAFO )
        [ ~, r1D, r2D, r3D ]  = ctx.kin.joint( r0D, r1D, r2D, r3D );
    end
    
    for j = 1 : Ndim    % Compute the jerk matrix
        ind = int32( 1 : M ) + ( j - 1 ) * M ;
        Jerk( ind, : ) = ( r3D( j, : ).' .* BasisVal + 1.5 * r2D( j, : ).' ...
                        .* BasisValD + 0.5 * r1D( j, : ).' .* BasisValDD ) ...
                        .* sqrt( BasisVal * coeff( :, k ) );
    end
    % Inequality constraints
    indAL   = int32( 1 : Nc * M )   + ( k - 1 ) * Nc * M;
    indAC   = int32( 1 : N  )       + ( k - 1 ) * N;
    Aj( indAL, indAC )   = [ Jerk ; -Jerk ];
    bj( indAL )          = [ b_jmax( : ); b_jmax( : ) ];
end

checkValidity( Aj, bj );

c_prof_out(mfilename);

end

function checkValidity( A, b )

assert( ~any( isnan( A ) , 'all' ),          mfilename + " Error : A has NaN");
assert( ~any( isnan( b ) , 'all' ),          mfilename + " Error : b has NaN");

end


