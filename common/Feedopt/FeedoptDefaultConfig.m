function [ cfg ] = FeedoptDefaultConfig()
%#codegen
% FeedoptDefaultConfig : Create a configuration structure with the default
% settings.
% 
% Outputs :
% cfg   : The resulting default structure 
%

coder.inline("never");

tol_col_compress_deg    = 30;
tol_col_smooth_deg      = 10;

% Computation of Gauss-Legendre knots and weights for numerical integration
GaussLegendreN = 5;  % number of evaluation points
[GaussLegendreX, GaussLegendreW] = lgwt(GaussLegendreN, -1, 1); 
% normalized to integration interval [-1, 1]
GaussLegendreX = flipud( GaussLegendreX );


LP = struct(...
    'Type', 'LP', ...                       % Optimisation type
    'USE_JERK_CONSTRAINTS', true,...        % Use jerk constraints
    'FIND_REASON_INFEASIBILITY', true,...   % Find the reason of the infeasibility
    'ACC_RAMP_OVER_WINDOWS', 1.0 - 1E-3,... % Acceleration ramp used in the optimisation
    'VEL_RAMP_OVER_WINDOWS', 1.0 - 1E-3,... % Velocity ramp used in the optimisation
    'SLACK_PENALTY', 10000, ...             % Slack penalty
    'USE_LENGTH_SCALING', false, ...        % Use diagonal length scaling
    'USE_LINPROG', false,...                % Use Linprog solver
    'FORCE_POSITIV_COEFFS', false...        % For the use of positiv coefficients
    );

if( ~coder.target('MATLAB') )
    coder.cstructname( LP,          StructTypeName.LPCfg );
end

% To use XSR manual CAM offset
use_XSR_offset = true;  

if( use_XSR_offset )
    offM = [ 0, 0, 0 ]';
    offT = [ 0, 0, 0 ]';
    offP = [ 0.07155, -0.1645, 1.6 ]';
    offB = [ 0, 0, 0 ]';
    offC = [ 0, 0, 0 ]';
else
    offM = [ 0, 0, -68.802 ]';
    offT = [ 0, 0, 0 ]';
    offP = [ 0, 0, 0 ]';
    offB = [ 0, -60.8, -6.6 ]';
    offC = [ 0, 0, 0 ]';
end

kin_params  = [ offM offT offP offB offC ];
kin_type    = 'xyzbc_tt';

cfg = struct(...
    'ENABLE_PRINT_MSG', true, ...                   % Enable console msg
    'maskTot',  logical( [ 1, 1, 1, 0, 1, 1 ] ),... % [X,Y,Z,A,B,C]
    'maskCart', logical( 0 ),...                    % Do not modify
    'maskRot',  logical( 0 ),...                    % Do not modify
    'indCart', int32( 0 ), ...                      % Do not modify
    'indRot',  int32( 0 ),...                       % Do not modify
    'NumberAxis', int32( 0 ), ...                   % Do not modify
    'NCart',   int32( 0 ), ...                      % Do not modify
    'NRot',    int32( 0 ), ...                      % Do not modify
    'D', 0, ...                                     % Do not modify
    'coeffD', 1, ...                                % Scaling for cartesian and rotary axis
    'kin_params', reshape( kin_params, [], 1 ), ... % See kinematics parameters' structure
    'kin_type', kin_type, ... % Kinematics type
    'NDiscr', int32( 20 ),... % Number of discretization points
    'NBreak', int32( 10 ),... % Number of break points
    'SplitSpecialSpline', false,... % Split methode specific to spline
    'ReleaseMemoryOfTheQueues', true, ...  % Release memory of the queues once they're not required anymore    
    'UseDynamicBreakpoints',false,...       % Use a variable number of breakpoints for different lengths
    'UseLinearBreakpoints',true,...         % Use a linear distribution of breakpoints (else sinspace)
    'DynamicBreakpointsDistance', 0.1,...   % Distance between two breakpoints in mm
    'NHorz', int32( 5 ),... % Number of curves used in the window for the optimisation
    'vmax', [500,500,500,0, 40,50],... % Max speed per axe {[mm],[rad]} / s
    'amax', [15000,15000,15000,0, 200,1000],... % Max acceleration per axe {[mm],[rad]} / s^2
    'jmax', [1500000,1500000,1500000,0,10000,50000],... % Max jerk per axe {[mm],[rad]} / s^3
    'LeeSplineDegree', int32( 4 ),... % B Spline order used in the Lee algorithm
    'SplineDegree',    int32( 3 ),... % B Spline order used in the optimization
    'CutOff', 1E-1,... % Length used by the transition algorithm to cut the curves
    'LSplit',  3,... % Length used to cut the curves at a given length
    'LSplitZero', 1,... % Length used to cut the curves for a Zero start / end
    'LThresholdMax', 3,... % Maximum length used in the compressing algorithm
    'LThresholdMin', 5E-1,... % Minimum length used in the compressing algorithm 
    'v_0', 0, 'at_0', 0,... % Boundaries conditions used by the optimization
    'v_1', 0, 'at_1', 0,... % Boundaries conditions used by the optimization
    'dt', 1e-3, ...% Discretization time / time step
    'DefaultZeroStopCount', 1,... % Number of time step passed with stop
    'source', repmat(char(0), [1, 1024]),... % Path to the G Code filename
    'Cusp', ... % Configuration for the CUSP step : 
    struct(...
        'Skip', false,...       % Disable this step
        'CuspThreshold', 10 ... % Cusp's threshold in degree
    ),...
    'Compressing', ... % Configuration for the Compressing step :
    struct(...
        'Skip', false,...       % Disable this step
        'ColTolCosLee', cosd(tol_col_compress_deg) ... % Tolerance in term of colinearity (cos of the angle)
    ),...
    'Smoothing', ... % Configuration for the transition
    struct( ...
        'Skip', false,... % Disable this step
        'ColTolCosSmooth',  cosd(tol_col_smooth_deg), ... % Tolerance in term of colinearity (cos of the angle)
        'ColTolSmooth',     1E-5 ... % Tolerance in term of colinearity (cos of the angle)
    ), ...
    'GaussLegendreN', GaussLegendreN, ... % Gauss Legendre N
    'GaussLegendreX', GaussLegendreX, ... % Gauss Legendre X
    'GaussLegendreW', GaussLegendreW, ... % Gauss Legendre W
    'opt', LP,... % Optimisation Structure : Linear Programming (LP)
    'LogFileName', 'logs/logs' ...
    );

if ~coder.target( 'MATLAB' )
    coder.varsize( 'cfg.indCart',       StructTypeName.dimInd{ : } );
    coder.varsize( 'cfg.indRot',        StructTypeName.dimInd{ : } );
    coder.varsize( 'cfg.maskTot',       StructTypeName.dimMask{ : } );
    coder.varsize( 'cfg.maskCart',      StructTypeName.dimMask{ : } );
    coder.varsize( 'cfg.maskRot',       StructTypeName.dimMask{ : } );
    coder.varsize( 'cfg.D',             StructTypeName.dimD{ : } );
    coder.varsize( 'cfg.source',        StructTypeName.dimFileName{ : } );
    coder.varsize( 'cfg.kin_params',    StructTypeName.dimKinParams{ : } );
    coder.cstructname( cfg,             StructTypeName.FeedoptCfg );
end

[ cfg ] = setMachineAxisInConfig( cfg, cfg.maskTot );

end

