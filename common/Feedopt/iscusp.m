function [ value ] = iscusp( u, v, angle_d )
% iscusp : Perdicat, TRUE means a CUSP has been detected
%
% Inputs : 
% u : A vector left side
% v : A vector right side
% angle_d : Angle value in degree
%
% Outputs :
% value : Boolean value. TRUE means a CUSP has been detected
%
    value = dot(u,v)/(norm(u)*norm(v)) <= cosd(180 - angle_d);
end
