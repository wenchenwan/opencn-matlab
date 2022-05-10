function [ctx, Coeff, NCoeff, success, status, msg] = ...
    FeedratePlanning_LP( ctx, CurvStructsArray, amax, jmax, BasisVal, ...
    BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, N_Hor)
% FeedratePlanning_LP : Perform the feedrate planning based on the LP
% formulation. A two stages scheme is performed ( with and without jerk
% constraints ).
%
% Inputs
% ctx               : The context
% CurvStructsArray  : Array of structures
% amax              : Acceleration maximum
% jmax              : Jerk maximum
% BasisVal          : Functions basis evaluated
% BasisValD         : 1st derivative
% BasisValDD        : 2nd derivative
% BasisIntegr       : Integral
% Bl                : B-spline
% u_vec             : Knot vector
% N_Hor             : Number of windows (horizon)
%
% Outputs
% ctx               : See before
% Coeff             : Result of the optimization
% NCoeff            : Number of coefficients
% success           : Result of the optimization
%                   0 : Fails of the optimization
%                   1 : Success of the optimization
% status            : returned structure by the optimizer
% msg               : Message on the optimiztion process

% 0) Initialization of the problem

LP = ctx.cfg.opt;   % Load parameters of the LP

[~, NCoeff0] = size( BasisVal ); % Extract size of the problem

CurvStructs  = CurvStructsArray( 1 : N_Hor ); % Extract window of interest

f = -repmat( BasisIntegr, 1, N_Hor ); % Linear pernalty

% 1) Optimization : first LP

% Constraints

% [A, b, Aeq, beq] = BuildConstr(ctx, CurvStructs, amax, ctx.v_0, ...
%                             ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, ...
%                             BasisValD, u_vec);
% A = sparse( A );
%b = full( b ); beq = full( beq ); %Aeq = full( Aeq );

[A, b, Aeq, beq ] = BuildConstr_v4(ctx, CurvStructs, amax, ctx.v_0, ...
    ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, ...
    BasisValD, u_vec);

A = [-1 * eye( size(A,2) ); A];
b = [zeros( size(A,2), 1 ) ; b];

[Coeff0, success, status, msg] = c_simplex(f, A, b, Aeq, beq, ctx);

% if( ~success ) % Return if optimization fails
%     printMSG( "\t First LP | "); ctx.at_1 = [];
%     Coeff = []; NCoeff = int32(0); return; 
% end

Coeff1  = reshape(Coeff0, NCoeff0, N_Hor);

% 2) Optimization : second LP

[A_jerk, b_jerk] = BuildConstrJerk_v4(ctx, CurvStructs, Coeff1,...
                   jmax, BasisVal, BasisValD, BasisValDD, u_vec);

Atot = [A; A_jerk]; btot = [b; b_jerk];

[Coeff2, success, status, msg] = c_simplex(f, Atot, btot, ...
                                 Aeq, beq, ctx);

if( ~success )
    printMSG( "\t Second LP | k : " + ctx.k0 );

    if( LP.USE_SLACK_ON_JERK )

        % Create jerk constraints
        [A_jerk, b_jerk] = BuildConstrJerkWithSlacks( ctx, CurvStructs,...
            Coeff1, jmax, BasisVal, BasisValD, BasisValDD, u_vec ...
            );

        Aeq_tot = [Aeq zeros(size(Aeq,1),1)];

        Atot = [zeros(size(A,1), size(A_jerk,2)); A_jerk];

        Atot(1 : size(A,1), 1 : size(A,2)) = A;

        btot = [zeros(size(b)); b_jerk];

        btot(1 : size(b,1)) = b;

        ftot = [f(:) ; LP.SLACK_PENALTY];

        [Coeff3, success, status, msg ] = c_simplex(ftot, Atot, btot, ...
            Aeq_tot, beq, ctx);

        jerkRatio = (jmax + Coeff3(end)) ./ jmax;

        printSecondLPMsg( jerkRatio, msg, success, ...
            LP.USE_SLACK_ON_JERK );

        Coeff4 = Coeff3(1:end-1);

        Coeff  = reshape(Coeff4, NCoeff0, N_Hor);
    else
        max_increase = 5; success = false;

        jmaxNew = jmax;

        while ~success && max_increase > 0
            jmaxNew = jmaxNew * 2;

            jerkRatio = jmaxNew ./ jmax;

            % Create jerk constraints
            [A_jerk, b_jerk] = BuildConstrJerk_v4(ctx, CurvStructs, Coeff1,...
                jmaxNew, BasisVal, BasisValD, BasisValDD, u_vec);

            Atot = [A; A_jerk]; btot = [b; b_jerk];


            [Coeff2, success, status, msg] = c_simplex(f, Atot, btot, ...
                Aeq, beq, ctx);

            printSecondLPMsg( jerkRatio, msg, success, ...
                LP.USE_SLACK_ON_JERK );

            max_increase = max_increase - 1;

            ctx.jmax_increase_count = ctx.jmax_increase_count + 1;

        end

        Coeff  = reshape(Coeff2, NCoeff0, N_Hor);
    end
else
    Coeff  = reshape(Coeff2, NCoeff0, N_Hor);
end

% Return if optimization fails
if( ~success )
    printMSG(  "\t ERROR OPTMIZATION FAILED\n" );    
    Coeff = []; NCoeff = int32(0); return; 
end

[v_0, a_0]  = CalcVAJ_v5(ctx, CurvStructs(1), Bl, Coeff(:, 1), {1});
[~, r1D]    = EvalCurvStruct(ctx, CurvStructs(1), 1);
t_end       = r1D / MyNorm( r1D ); % unit tangential vector
% tangential acceleration at the end of first piece in horizon
at_0        = a_0'*t_end; 
ctx.v_0     = v_0;
ctx.at_0    = at_0;
NCoeff      = int32( NCoeff0 );

end

function [] = printSecondLPMsg( jerkRatio, msg, success, isSlack )
% printSecondLPMsg : Write generated message from the optimization in the
% console. 
%
% jerkRatio :   Ratio between the inital jerk limit and the one applied to
% the optimization
% msg :         Generated error message from the optimization
% success :     Is true if the optimization succeed
% isSlack :     Flag used to specified wether or not a the slack
% formulation is used
if coder.target('matlab')
    msgSlack = "";
    
    if( isSlack ), msgSlack = " due to slack"; end

    printMSG(  ...
        sprintf("\n\tWARNING: (Jerk) Increasing jmax by a factor" + ...
        " [%.2f, %.2f, %.2f]" + msgSlack + "\n ",...
        jerkRatio(1), jerkRatio(2), jerkRatio(3) ) );
    
    if( ~success )
        printMSG(msg);
    else
        printMSG("\n");
    end
end

end


function [] = printMSG( msg )

if( coder.target( "MATLAB" ) )
    diary on;
    DebugLog(DebugCfg.FeedratePlanning, msg );
    diary off;
end

end