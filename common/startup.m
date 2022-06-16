addpath '.'
pathOfInterest = { 'c_planner_v5', 'Tests/Full', 'Tests', 'arc_center', ... 
    'Tests', 'types/', 'interp/', 'kinematics/', 'gen_mex', 'plot'};

if( exist( "dev" , 'dir' ) ), addpath( "dev/" ); end

for t = 1 : length( pathOfInterest )
    genPath = genpath( pathOfInterest{ t } );
    addpath( genPath );
end

