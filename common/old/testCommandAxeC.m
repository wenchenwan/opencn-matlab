

ANG_MAX     = 360;
ANG_MIN     = 0;

[ traj_mat ]    = generate_traj();

traj_drive      = traj_mat;

[ c_drive ] = format_command_axe_c_diff( 0, ANG_MAX, ANG_MIN, true );

for j = 1 : numel( traj_drive )
    traj_drive( j )  = format_command_axe_c_diff( traj_mat( j ), ANG_MAX, ANG_MIN, false );
%     traj_drive( j )  = format_command_axe_c( traj_mat( j ), ANG_MAX, ANG_MIN );
end

figure();
plot( traj_mat, '.' );

figure();
plot( traj_drive, '.' );


function [ traj ] = generate_traj()

time = linspace( 0, 10, 1000 );
f = @(x) sin( x * (2*pi) / 5 )* 400;

traj = f( time );
end

function [ c_drive ] = format_command_axe_c( c_matlab, ANG_MAX, ANG_MIN )

ANG_RANGE   = abs( ANG_MAX - ANG_MIN );

c_drive = c_matlab;

while( c_drive >= ANG_MAX )
    c_drive = c_drive - ANG_RANGE; 
end

while( c_drive < ANG_MIN )
    c_drive = c_drive + ANG_RANGE; 
end

end


function [ c_drive ] = format_command_axe_c_diff( c_matlab, ANG_MAX, ANG_MIN, reset )
persistent prev_c_drive prev_c_matlab;

if( reset || isempty( prev_c_matlab )  )    
    prev_c_matlab = c_matlab;  
end

if( reset || isempty( prev_c_drive )  )     
    prev_c_drive  = format_command_axe_c( c_matlab, ANG_MAX, ANG_MIN );  
end

diff_matlab = c_matlab - prev_c_matlab;
diff_drive  = format_command_axe_c( diff_matlab, 180, -180 );
c_drive     = prev_c_drive + diff_drive;

prev_c_matlab   = c_matlab;
prev_c_drive    = format_command_axe_c( c_drive, ANG_MAX, ANG_MIN );

end

function [ c_vec_drive ] = format_command_axe_c_vec( c_vec_matlab, ANG_MAX, ANG_MIN )

ANG_RANGE = abs( ANG_MAX - ANG_MIN );

c_vec_drive = c_vec_matlab;

while( any( c_vec_drive >= ANG_MAX, 'all' ) )
    c_vec_drive( c_vec_drive >= ANG_MAX ) = ...
    c_vec_drive( c_vec_drive >= ANG_MAX ) - ANG_RANGE; 
end

while( any( c_vec_drive < ANG_MIN, 'all' ) )
    c_vec_drive( c_vec_drive < ANG_MIN ) = ...
    c_vec_drive( c_vec_drive < ANG_MIN ) + ANG_RANGE; 
end

end

