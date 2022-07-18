%% Test new optimization

NHorz   = 5;
Ndim    = 6;
R0      = zeros( Ndim, 1);
R1      = R0;
info    = constrGcodeInfoStructType;
info.FeedRate = 120;

path = linspace( 0, 1, NHorz + 1 );
C    = repmat( constrCurvStructType, 1, NHorz );

cfg   = FeedoptDefaultConfig;
ctx   = initFeedoptPlan( cfg );
ctx.coeff = ones( cfg.NBreak + 1 , cfg.NHorz );

center = [ 1; 1; 0 ];
rotation = 1;
evec = [ 0; 0; 1 ];
A0 = zeros( 3, 1 );
A1 = zeros( 3, 1 );
P0 = A0;

for k = 1 : NHorz
    R1 = repmat( path( k + 1 ), Ndim, 1 );
    C( k )     = constrLineStruct(info, R0, R1);
    R0 = R1;

    % P1 = [ P0( 1 : 2 ); k ];
    % C( k ) = constrHelixStructFromArcFeed( info, P0, ...
    %     P1, center, A0, A1, rotation, evec);
    % P0 = P1;
end

[ A, b, Aeq, beq ] = buildConstr( ctx, C, ctx.cfg.amax, ctx.cfg.v_0, ...
    ctx.cfg.at_0, ctx.cfg.v_1, ctx.cfg.at_1, ctx.BasisVal, ctx.BasisValD, ...
    ctx.u_vec);

[ Aj, bj ] =  buildConstrJerk( ctx, C, ctx.coeff, ctx.cfg.jmax, ...
    ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.u_vec );

if( ctx.cfg.NumberAxis == 3 ) % Comprate the old and the new version of the build constraints
    [ A1, b1, Aeq1, beq1 ] = BuildConstr_v4( ctx, C, ctx.cfg.amax, ctx.cfg.v_0, ...
        ctx.cfg.at_0, ctx.cfg.v_1, ctx.cfg.at_1, ctx.BasisVal, ctx.BasisValD, ...
        ctx.u_vec);
    [ Aj1, bj1 ] = BuildConstrJerkWithSlacks(ctx, C, ctx.coeff, ctx.cfg.jmax, ...
    ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.u_vec );
    disp( "A : "    +  full( sum( (A1 - A ).^2, "all" ) ) );
    disp( "b : "    +  norm( b1 - b ) );
    disp( "Aeq : "  +  norm( Aeq1( : , 3 : end ) + Aeq(: , 3 : end ) ) );
    disp( "beq : "  +  norm( beq1 - beq ) );
    disp( "Aj : "    +  full( sum( (Aj1 - Aj ).^2, "all" ) ) );
    disp( "bj : "    +  norm( bj1 - bj ) );
end

[ctx, Coeff, success, status, msg] = ...
    FeedratePlanning_LP( ctx, C, ctx.cfg.amax, ctx.cfg.jmax, ctx.BasisVal, ...
    ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ctx.u_vec, NHorz );