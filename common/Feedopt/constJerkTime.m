function [ k_vec ] = constJerkTime( pseudoJerk, u_vec, isEnd )
% constJerkTime : Compute the time vector for a given u vector based on a 
%                 constant jerk velocity profile.
%
% Inputs :
%   pseudoJerk  : Constant jerk value 
%   u_vec       : U vector
%   isEnd       : Is the end of a curv
%
% Outputs :
%   k_vec       : Time vector
%
if( coder.target( "MATLAB" ) )
    % Check inputs shape
    if( isrow( pseudoJerk ) ), pseudoJerk = pseudoJerk'; end
    if( iscolumn( u_vec ) ),   u_vec = u_vec'; end
end

if( isEnd )
    u_vec = 1 - u_vec;
end

k_vec = ( u_vec * 6 / pseudoJerk ).^( 1 / 3 );

if( isEnd )
    k_max   = ( 6 / pseudoJerk )^( 1 / 3 );
    k_vec   = k_max - k_vec; 
end

end
