function [ k_vec ] = constJerkTime(pseudoJerk, u_vec, isEnd)
% constJerkN : Compute k
% Inputs : 
%   pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
%   u_vec      :  [ 1 x M ] The u vector
%   isEnd      :  ( Boolean ) Is the end of the Curve
% Outputs : 
%   k_vec      :  [ 1 x M ] The time vector

if( coder.target( "MATLAB" ) )
    % Check inputs shape
    if( isrow( pseudoJerk ) ), pseudoJerk = pseudoJerk'; end
    if( iscolumn( u_vec ) ),   u_vec = u_vec'; end
end

if( isEnd )
    u_vec = 1 - u_vec;
end

k_vec = (u_vec * 6 / pseudoJerk).^(1/3);

if( isEnd )
    k_max   = ( 6 / pseudoJerk )^( 1 / 3 );
    k_vec   = k_max - k_vec; 
end

end