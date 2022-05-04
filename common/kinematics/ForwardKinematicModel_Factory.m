function [r_r] = ForwardKinematicModel_Factory( x, y, z, b, c, mx, my, mz,...
                                                tx, ty, tz, px, p_y, pz, d1,...
                                                d2, t_l )
% ForwardKinematicModel_Factory
%
% Variable :         unit : size : description
% OUTPUT 
% Fct_MGD  :                     : Function for the Forward Kinematic Model
% r_r   : [mm and rad] :  1x5 : 

T = [1, 0, 0,     x;
     0, 1, 0,    -y;
     0, 0, 1, z-t_l;
     0, 0, 0,     1];

FW_RTCP_sym = simplify( inv( M5_TCP( px, p_y, pz ) ) * ...
              inv( subs( M5_TMC_sym( d1 ), y, 0 ) ) * ...
              inv( M5_T0M( mx, my, mz + d1 ) ) * T );

% Output vector assignation
r_r(1) = FW_RTCP_sym(1, 4);
r_r(2) = -FW_RTCP_sym(2, 4);
r_r(3) = FW_RTCP_sym(3, 4);
r_r(4) = b;
r_r(5) = c;

end