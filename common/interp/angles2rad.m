function [ angles_rad ] = angles2rad( angles_deg )
% angles2rad : Degree to rad conversion on a vector of angles.
% 
% angles_deg : Vector of angles expressed in degree
%
% angles_rad : Vector of angles expressed in rad
    angles_rad = deg2rad( angles_deg );
end