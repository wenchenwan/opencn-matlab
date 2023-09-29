function  [res, resd, resdd, resddd] = export_kinematic_class( cfg, vec, vecd, vecdd, vecddd )
%#codegen
coder.inline( "never" );

% Constructor
kin = Kinematics( cfg.kin_type, cfg.kin_params );

% Set parameters
kin = kin.set_params( cfg.kin_params );

% Set type
kin = kin.set_type( cfg.kin_type );

% Set tool length
kin = kin.set_tool_length( 1.0 );

% Get params
params = kin.get_params();

% Get types
type = kin.get_type();

%----------------------------------------------------------------%
% Basic kinematics
%----------------------------------------------------------------%

% Position
vec = kin.r_joint( vec );
vec = kin.r_relative( vec);

%----------------------------------------------------------------%
% Advanced kinematics
%----------------------------------------------------------------%

% Speed
vec = kin.v_joint( vec, vecd );
vec = kin.v_relative( vec, vecd );

% Acceleration
vec = kin.a_joint( vec, vecd, vecdd );
vec = kin.a_relative( vec, vecd, vecdd );

% Jerk
vec = kin.j_joint( vec, vecd, vecdd, vecddd );
vec = kin.j_relative( vec, vecd, vecdd, vecddd );

% All
[ vec, vecd, vecdd, vecddd] = kin.relative( vec, vecd, vecdd, vecddd );
[ res, resd, resdd, resddd ] = kin.joint( vec, vecd, vecdd, vecddd );
end