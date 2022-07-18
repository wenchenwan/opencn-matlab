function [ angles ] = angles2deg( angles )
% angles2deg : Rad to degree conversion on a vector of angles.
% 
% Inputs :
% angles : Vector of angles expressed in rad
%
% Outputs:
% angles : Vector of angles expressed in degree
    angles = rad2deg( angles );
end