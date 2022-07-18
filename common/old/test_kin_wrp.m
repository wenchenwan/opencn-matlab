%% Test kinematic Wrapper
type    = "xyzbc";
params  = zeros( 3, 4 ); params( 1, end ) = 24.876;
k       = Kinematics( type, params );

