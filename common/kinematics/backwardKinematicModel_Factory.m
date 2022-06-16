function [joint] = backwardKinematicModel_Factory( R, P )
% BackwardKinematicModel_Factory
%
% Variable :         unit : size : description
% INPUT 
% P = [mx, tx,  px,  d1;
%      my, ty, p_y,  d2;
%      mz, tz,  pz, t_l];
% OUTPUT 
% Fct_MGI  :                     : Function for the Backward Kinematic Model
% r_a      : [mm and rad] :  1x5 : 

BW_RTCP_sym = simplify( Translation( [0, 0, P(3, 4)]) * M5_T0M(P(1, 1),...
                        P(2, 1), P(3, 1)+P(1, 4)) ...
                        * subs(M5_TMC_sym(R(2), R(5), R(6), P(1, 4)), R(2), 0)...
                        * M5_TCP(P(1, 3), -P(2, 3), P(3, 3)) ...
                        * inv(subs(M5_TMC_sym(R(2), R(5), R(6), P(1, 4)),...
                        [R(5), R(6)], [0, 0])) ...
                        * M5_TMB_sym(R(1), R(3), P(2, 4)) ...
                        * Translation( [P(1, 2), P(2, 2), P(3, 2) - P(3, 4)] ) );
% BW_RTCP_sym
% Output vector assignation
joint(1) = BW_RTCP_sym(1, 4);
joint(2) = -BW_RTCP_sym(2, 4);
joint(3) = BW_RTCP_sym(3, 4);
joint(4) = 0;
joint(5) = R(5);
joint(6) = R(6);
end