function R = Rotation(Axis, Angle)
% Rotation
% INPUT :
% Axis  = x, y, or z : Choose the axis of rotation
% Angle = [0 2pi]    : Angle of rotation in radian
% OUTPUT :
% R     = 4x4 matrix of rotation

if Axis == 'x'
    R = [1,          0,           0, 0;
         0, cos(Angle), -sin(Angle), 0;
         0, sin(Angle),  cos(Angle), 0;
         0,          0,           0, 1];
elseif Axis == 'y'
    R = [ cos(Angle), 0, sin(Angle), 0;
                   0, 1,          0, 0;
         -sin(Angle), 0, cos(Angle), 0;
                   0, 0,          0, 1];
elseif Axis == 'z'
    R = [cos(Angle), -sin(Angle), 0, 0;
         sin(Angle),  cos(Angle), 0, 0;
                  0,           0, 1, 0;
                  0,           0, 0, 1];
else
    disp('Only Axis x, y or z are allowed')
end
end