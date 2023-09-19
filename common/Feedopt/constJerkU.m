function [ u, ud, udd, uddd ] = constJerkU( pseudoJerk, k_vec, isEnd, forceLimits)
% constJerkU : Compute u and its derivative based on the pseudo jerk 
% approximation.
% Inputs : 
%   pseudoJerk      :  [ N x 1 ] The pseudo constant Jerk
%   k_vec           :  [ 1 x M ] The time vector
%   isEnd           :  ( Boolean ) Is the end of the Curve.
%   forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1 
% Outputs : 
%   u               :  [ N x M ]
%   ud              :  [ N x M ]
%   udd             :  [ N x M ]
%   uddd            :  [ N x M ]

if( coder.target( "MATLAB" ) )
    % Check inputs shape
    if( isrow( pseudoJerk ) ), pseudoJerk = pseudoJerk'; end
    if( iscolumn( k_vec ) ),   k_vec = k_vec'; end
end

if( isEnd )
    k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
    k_vec  = k_max - k_vec;
end

% Compute u and its derivatives based on constant jerk
uddd    = pseudoJerk .* ones( size( k_vec ) );
udd     = pseudoJerk .* k_vec;
ud      = pseudoJerk .* k_vec .^2 / 2;
u       = pseudoJerk .* k_vec .^3 / 6;

if( forceLimits )
    u( u > 1 ) = 1;
    u( u < 0 ) = 0;
end

if( isEnd ) % Reverse time ( Backward-like integration )
    u    = 1 - u;
    ud   = ud;
    udd  = -udd;
    uddd = uddd;
end

end