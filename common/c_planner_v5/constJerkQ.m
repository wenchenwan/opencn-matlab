function [ q, qd, qdd, q1, u1 ] = constJerkQ( pseudoJerk, k_vec, isEnd, a, b)
% constJerkQ : Compute q( u ) and its derivative based on the pseudo jerk 
% approximation.
% Inputs : 
%   pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
%   k_vec      :  [ 1 x M ] The time vector
%   isEnd      :  ( Boolean ) Is the end of the Curve.
%   a          :  Curve parameter a for affine transform
%   b          :  Curve parameter b for affine transform
% Outputs : 
%   q          :  [ N x M ]
%   qd         :  [ N x M ]
%   qdd        :  [ N x M ]
%   q1         :  [ N x 1 ] q( u_tilde ) @ u_tilde = 1
%   u1         :  [ N x 1 ] uk

if( coder.target( "MATLAB" ) )
    % Check inputs shape
    if( isrow( pseudoJerk ) ), pseudoJerk = pseudoJerk'; end
    if( iscolumn( k_vec ) ),   k_vec = k_vec'; end
end

% Compute u and its derivatives based on constant jerk
[ u, ud, udd, uddd ] = constJerkU( pseudoJerk, [ k_vec, 1 ], isEnd );

% [ u, ud, udd, uddd ] = tilda2u( u, ud, udd, uddd, a, b );

indK = 1 : length( k_vec );

[ q, qd, qdd ] = calcQfromU( ud, udd, uddd );

q   = q( :, indK );
qd  = qd( :, indK );
qdd = qdd( :, indK );
q1  = ud( :, end ) .^2;
u1  = u( : , 1 );
end