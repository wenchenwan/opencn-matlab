function [r_r] = forwardKinematicModel_Factory( R, P )
% ForwardKinematicModel_Factory
%
% Variable :         unit : size : description
% INPUT 
% P = [mx, tx,  px,  d1;
%      my, ty, p_y,  d2;
%      mz, tz,  pz, t_l];
% OUTPUT 
% Fct_MGD  :                     : Function for the Forward Kinematic Model
% r_r      : [mm and rad] :  1x5 : 

T = [1, 0, 0,         R(1);
     0, 1, 0,        -R(2);
     0, 0, 1, R(3)-P(3, 4);
     0, 0, 0,            1];

FW_RTCP_sym = simplify( inv(Translation( [P(1, 2), P(2, 2), P(3, 2) + P(1, 4) + P(2, 4) - P(3, 4)] )) * ...
              inv( M5_TCP( P(1, 3), -P(2, 3), P(3, 3) ) ) * ...
              inv( subs( M5_TMC_sym( R(2), R(5), R(6), P(1, 4) ), R(2), 0 ) ) * ...
              inv( M5_T0M( P(1, 1), P(2, 1), P(3, 1) + P(1, 4) ) ) * T );

% Output vector assignation
r_r(1) = FW_RTCP_sym(1, 4);
r_r(2) = -FW_RTCP_sym(2, 4);
r_r(3) = FW_RTCP_sym(3, 4);
r_r(4) = 0;
r_r(5) = R(5);
r_r(6) = R(6);
end