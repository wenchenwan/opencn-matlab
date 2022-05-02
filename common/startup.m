addpath '.'
addpath c_planner_v5
addpath Tests/Full
addpath Tests/Unit/CutStruct
addpath Tests/Unit/ZSpdMode
addpath Tests/Unit
addpath Validate_OpenCN
addpath arc_center
addpath Tests
addpath types/
addpath interp/

if( exist( "dev" , 'dir' ) ), addpath( "dev/" ); end

genPath = genpath( 'gen_mex' );
addpath( genPath );