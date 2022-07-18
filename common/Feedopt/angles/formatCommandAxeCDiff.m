function [ c_drive ] = formatCommandAxeCDiff( c_cmd, ANG_MAX, ANG_MIN, reset )
% formatCommandAxeCDiff : Change the format of the input command for the axe C.
% The ANG_MAX and ANG_MIN are respectively half of the maximum and minimum 
% values allowed by the drive (see the note below). 
% This code also unsure smooth commands send to the drive.
% Note : The drive needs to allocate 2 times the range of angle to unsure
% smooth command for the drive to test on the machine.
%#codegen
persistent prev_c_drive prev_c_cmd;

if( reset || isempty( prev_c_cmd )  )    
    prev_c_cmd = c_cmd;  
end

if( reset || isempty( prev_c_drive )  )     
    prev_c_drive  = formatCommandAxeC( c_cmd, ANG_MAX, ANG_MIN );  
end

ANG_RANGE   = abs( ANG_MAX - ANG_MIN );

diff_cmd    = c_cmd - prev_c_cmd;
diff_drive  = formatCommandAxeC( diff_cmd, ANG_RANGE / 2, -ANG_RANGE / 2 );
c_drive     = prev_c_drive + diff_drive;

prev_c_cmd      = c_cmd;
prev_c_drive    = formatCommandAxeC( c_drive, ANG_MAX, ANG_MIN );

end