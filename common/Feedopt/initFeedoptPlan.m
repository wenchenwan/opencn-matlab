function [ ctx ] = initFeedoptPlan( cfg )
%#codegen
% initFeedoptPlan : Initialize the context of the computational chain.
%
% Inputs : 
%   cfg : The configuration structure
%
% Outputs : 
%   ctx : The context structure of the computational chain
%
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

ctx.BasisVal            = BasisVal;
ctx.BasisValD           = BasisValD;
ctx.BasisValDD          = BasisValDD;
ctx.BasisValDDD         = BasisValDDD;
ctx.BasisIntegr         = BasisIntegr;
ctx.Bl                  = Bl;
ctx.u_vec               = u_vec;

% Initialize the different queue used in the computational chain
Curv                    = constrCurvStructType;
ctx.q_spline            = queue( Curv );
ctx.q_gcode             = queue( Curv );
ctx.q_compress          = queue( Curv );
ctx.q_smooth            = queue( Curv );
ctx.q_split             = queue( Curv );
ctx.q_opt               = queue( Curv );

% Current operation
ctx.op                  = Fopt.Init;
% Go to the next queue
ctx.go_next             = false;
% Try to push again. HGS : Probably not used anymore
ctx.try_push_again      = false;
% Number of optimized queue
ctx.n_optimized         = int32( 0 );
% Reach the last optimized queue
ctx.reached_end         = false;
% Index of the element of the current queue
ctx.k0                  = int32( 1 );
% Velocity at start of next queue window
ctx.v_0                 = cfg.v_0;
% Velocity at end of next queue window
ctx.v_1                 = cfg.v_1;
% Tangential acceleration at start of next queue window
ctx.at_0                = cfg.at_0;
% Tangential acceleration at end of next queue window
ctx.at_1                = cfg.at_1;
% Configuration structure with all the parameters
ctx.cfg                 = cfg;
% Number of time the maximum jerk increase
ctx.jmax_increase_count = int32(0);
% The current curv is a zero start
ctx.zero_start          = false;
% The current curv is a zero end
ctx.zero_end            = false;
% A zero curv has been forced, because the optimization fails
ctx.zero_forced         = false;
% A buffer to store the left and right curves use when the optimization
% fails
ctx.zero_forced_buffer  = [ Curv, Curv ];
% The number of time the simplex algorithm has been called. HGS : Probably
% not used anymore
ctx.simplex_calls       = int32(0);

% HGS : Don't know why this parameter is used for
ctx.forced_stop         = int32(0);
% Counter of programmed stop during the whole computational chain
ctx.programmed_stop     = int32(0);
% Coeff of resulting from the optimization
ctx.Coeff               = zeros( 1, 1 );
% HGS : Don't know what this parameter is used for
ctx.Skipped             = int32(0);
% Kinematic class used to interact with the different kinematics
ctx.kin                 = Kinematics( cfg.kin_type, cfg.kin_params );

Curv.Info.Type          = CurveType.Spline;
Curv.sp.Bl              = Bl;
% Error message structure
ctx.errmsg              = constrMsgStructType;
% Error code (a.k.a. Operation index when the error has been raised)
ctx.errcode             = FeedoptPlanError.NoError;

if ~coder.target('matlab')
    coder.varsize( 'ctx.cfg.indCart',       StructTypeName.dimInd{ : } );
    coder.varsize( 'ctx.cfg.indRot',        StructTypeName.dimInd{ : } );
    coder.varsize( 'ctx.cfg.maskTot',       StructTypeName.dimMask{ : } );
    coder.varsize( 'ctx.cfg.maskCart',      StructTypeName.dimMask{ : } );
    coder.varsize( 'ctx.cfg.maskRot',       StructTypeName.dimMask{ : } );
    coder.varsize( 'ctx.cfg.D',             StructTypeName.dimD{ : } );
    coder.varsize( 'ctx.cfg.source',        StructTypeName.dimFileName{ : } );
    coder.varsize( 'ctx.cfg.kin_params',    StructTypeName.dimKinParams{ : } );
    coder.cstructname( ctx.cfg,             StructTypeName.FeedoptCfg );
    coder.varsize( 'ctx.BasisVal',          StructTypeName.dimBasis{ : } );
    coder.varsize( 'ctx.BasisValD',         StructTypeName.dimBasis{ : } );
    coder.varsize( 'ctx.BasisValDD',        StructTypeName.dimBasis{ : } );
    coder.varsize( 'ctx.BasisIntegr',       StructTypeName.dimBasisInt{ : } );
    coder.varsize( 'ctx.u_vec',             StructTypeName.dimCtxUvec{ : } );
    coder.varsize( 'ctx.Bl.breakpoints',    StructTypeName.dimCtxBlBreaks{ : } );
    coder.varsize( 'ctx.Coeff',             StructTypeName.dimCtxCoeff{ : } );
    coder.cstructname(ctx, StructTypeName.FeedoptCtx );
end
% Queue of BSpline
ctx.q_spline.push( Curv );

end
