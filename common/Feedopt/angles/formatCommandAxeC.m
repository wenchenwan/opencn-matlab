function [ c_drive ] = formatCommandAxeC( c_cmd, ANG_MAX, ANG_MIN )
% formatCommandAxeC : Change the format of the input command for the axe C.
% The ANG_MAX and ANG_MIN are respectively the maximum and minimum values
% allowed by the drive.
%#codegen 
ANG_RANGE   = abs( ANG_MAX - ANG_MIN );

c_drive = c_cmd;

while( c_drive >= ANG_MAX )
    c_drive = c_drive - ANG_RANGE; 
end

while( c_drive < ANG_MIN )
    c_drive = c_drive + ANG_RANGE; 
end

end