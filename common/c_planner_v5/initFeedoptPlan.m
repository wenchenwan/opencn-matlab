function ctx = initFeedoptPlan( cfg )
%#codegen
% ctx is the context variable, it should contain:
% - op: Operation to execute
% - go_next:    Should we optimize the next segment
% - q_gcode:    GCode queue
% - q_smooth:   Queue for smoothed segments
% - q_split:    Queue after splitting
% - q_opt:      Queue after optimization
coder.inline("never");

if cfg.UseLinearBreakpoints
    Bl      = bspline_create( cfg.SplineDegree, linspace( 0, 1, ...
                                  cfg.NBreak ) );
    u_vec   = linspace( 0, 1, cfg.NDiscr );
else
    Bl      = bspline_create( cfg.SplineDegree, sinspace( 0, 1, ...
                                  cfg.NBreak ) );
    u_vec   = sinspace( 0, 1, cfg.NDiscr );
end

[ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr] = ...
                                    bspline_base_eval( Bl , u_vec );

ctx.BasisVal    = BasisVal;
ctx.BasisValD   = BasisValD;
ctx.BasisValDD  = BasisValDD;
ctx.BasisValDDD = BasisValDDD;
ctx.BasisIntegr = BasisIntegr;
ctx.Bl          = Bl;
ctx.u_vec       = u_vec;

Curv            = constrCurvStructType();
ctx.q_spline    = queue( Curv );
ctx.q_gcode     = queue( Curv );
ctx.q_compress  = queue( Curv );
ctx.q_smooth    = queue( Curv );
ctx.q_split     = queue( Curv );
ctx.q_opt       = queue( Curv );
% 
ctx.op              = Fopt.Init;
ctx.go_next         = false;
ctx.try_push_again  = false;
ctx.n_optimized     = int32(0);
ctx.reached_end     = false;
ctx.k0              = int32(1);
ctx.v_0             = cfg.v_0;
ctx.v_1             = cfg.v_1;
ctx.at_0            = cfg.at_0;
ctx.at_1            = cfg.at_1;
ctx.cfg             = cfg;
ctx.errcode         = FeedoptPlanError.Success;
ctx.jmax_increase_count = int32(0);
ctx.zero_start          = false;
ctx.zero_end            = false;
ctx.simplex_calls       = int32(0);

ctx.forced_stop     = int32(0);
ctx.programmed_stop = int32(0);

ctx.Coeff   = zeros( 1, 1 );
ctx.Skipped = int32(0);

Curv.Info.Type = CurveType.Spline;
Curv.sp.Bl     = Bl;

if ~coder.target('matlab')
    coder.varsize( 'cfg.indCart',   StructTypeName.dimInd{ : } );
    coder.varsize( 'cfg.indRot',    StructTypeName.dimInd{ : } );
    coder.varsize( 'cfg.indTot',    StructTypeName.dimIndTot{ : } );
    coder.varsize('ctx.BasisVal',   StructTypeName.dimBasis{ : } );
    coder.varsize('ctx.BasisValD',  StructTypeName.dimBasis{ : } );
    coder.varsize('ctx.BasisValDD', StructTypeName.dimBasis{ : } );
    coder.varsize('ctx.BasisIntegr',StructTypeName.dimBasisInt{ : } );
    coder.varsize('ctx.u_vec',      StructTypeName.dimCtxUvec{ : } );
    coder.varsize('ctx.Bl.breakpoints', StructTypeName.dimCtxBlBreaks{ : } );
    coder.varsize('ctx.Coeff',      StructTypeName.dimCtxCoeff{ : } );
    coder.cstructname(ctx, StructTypeName.FeedoptCtx );
end

ctx.q_spline.push( Curv );

end
