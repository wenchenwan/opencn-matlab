function [ angles_deg ] = angles2deg( angles_rad )
% angles2deg : Rad to degree conversion on a vector of angles.
% 
% angles_rad : Vector of angles expressed in rad
%
% angles_deg : Vector of angles expressed in degree
    angles_deg = rad2deg( angles_rad );
end