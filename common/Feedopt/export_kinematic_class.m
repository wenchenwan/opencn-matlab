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
res = kin.r_joint( vec ) + rand;
res = kin.r_relative( res) + rand;

%----------------------------------------------------------------%
% Advanced kinematics
%----------------------------------------------------------------%

% Speed
resd = kin.v_joint( res, vecd ) + rand;
resd = kin.v_relative( res, resd ) + rand;

% Acceleration
resdd = kin.a_joint( res, resd, vecdd ) + rand;
resdd = kin.a_relative( res, resd, resdd ) + rand;

% Jerk
resddd = kin.j_joint( res, resd, resdd, vecddd ) + rand;
resddd = kin.j_relative( res, resd, resdd, resddd ) + rand;

% All
[ res, resd, resdd, resddd] = kin.relative( res, resd,resdd, resddd );
[ res, resd, resdd, resddd ] = kin.joint( res + rand, resd + rand, resdd + rand, resddd + rand );
end