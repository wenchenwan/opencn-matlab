function CurvStruct = ConstrHelixStructFromArcFeed(trafo, HSC, ...
                      Poff, Aoff, Uoff, Doff, p0x, p0y, p0z, ...
                      p1x, p1y, p1z, cx, cy, cz, A0, A1, U0, U1, rotation,...
                      evec) %#codegen
% ConstrHelixStructFromArcFeed : Construct a Curv struct filled with the
% parameters of a helix. The resulting helix is the combination of a linear 
% motion along one of the three reference axis (x,y,z) with a circular
% motion in the perpendicular plan (XY, ZX, YZ).
%
% trafo     : Flag for the trafo directive
% HSC       : High speed cutting (true : on, false : off)
% Poff      : Offset on the position {X, Y, Z}
% Aoff      : Offset on the angle {A, B, C}
% Uoff      : Offset on the sub-axis {U, V, W}
% Doff      : Offset for the diameter of the tool
% p0x       : Value in the x axis of point P0
% p0y       : Value in the y axis of point P0
% p0z       : Value in the z axis of point P0
% p1x       : Value in the x axis of point P1
% p1y       : Value in the y axis of point P1
% p1z       : Value in the z axis of point P1
% cx        : Value in the x axis of the center C
% cy        : Value in the y axis of the center C
% cz        : Value in the z axis of the center C
% A0        : Vector of the orientation angles at starting pose
% A1        : Vector of the orientation angles at ending pose
% U0        : Vector of for the secondary axes at starting pose
% U1        : Vector of for the secondary axes at ending pose
% rotation  : Number of rotation to realize (positive ; Clockwise |
%             negative ; Counterclockwise | zero ; pure translation)
% evec      : Unit vector orthogonal to the planned of the projected circle 
%
% CurvStruct : The resulting CurvStruct
coder.inline("never");


% Create vectors
P0 = [p0x, p0y, p0z]';
P1 = [p1x, p1y, p1z]';
C  = [cx,  cy,  cz]';

if evec(1) > 0.5        % YZ
    indYZ = [2, 3]; 
    [~, Cprim, delta] = CorrectArcCenter(P0(indYZ), P1(indYZ), C(indYZ));
    Cprim = [cx, Cprim(1), Cprim(2)]';
    R0 = cross(evec, P0 - Cprim);
    R1 = cross(evec, P1 - Cprim);
    phi0 = atan2(R0(3), R0(2));
    phi1 = atan2(R1(3), R1(2));
    
elseif evec(2) > 0.5    % ZX
    indZX = [3, 1];
    [~, Cprim, delta] = CorrectArcCenter(P0(indZX), P1(indZX), C(indZX));
    Cprim = [Cprim(2), cy, Cprim(1)]';
    R0 = cross(evec, P0 - Cprim);
    R1 = cross(evec, P1 - Cprim);
    phi1 = atan2(R0(3), R0(1));
    phi0 = atan2(R1(3), R1(1));
    
else                    % XY
    indXY = [1,2];
    [~, Cprim, delta] = CorrectArcCenter(P0(indXY), P1(indXY), C(indXY));
    Cprim = [Cprim(1), Cprim(2), cz]';
    R0 = cross(evec, P0 - Cprim);
    R1 = cross(evec, P1 - Cprim);
    phi0 = atan2(R0(2), R0(1));
    phi1 = atan2(R1(2), R1(1));
    
end

P10 = P1 - P0;
% Theta is in [-2 pi; 2 pi]
theta = phi1 - phi0; 
% Projection of P10 along the linear motion. Note evec is a unit vector.
devec = dot(evec, P10);

if rotation == 0 % Linear motion
    theta = 0; pitch = devec;
else 
    if rotation > 0 % Clockwise rotation
        if theta <= 0, theta = theta + 2*pi; end
        theta = theta + ( rotation - 1 ) * 2*pi;
    else            % Counterclockwise rotation
        if theta >= 0, theta = theta - 2*pi; end
        theta = theta + ( rotation + 1 ) * 2*pi;
    end
    if( theta == 0 ) % Linear motion
        pitch = devec;
    else
        pitch = (devec / theta) * 2*pi;
    end
end

CurvStruct = ConstrHelixStruct(trafo, HSC, Poff, Aoff, Uoff, ...
                                Doff, P0, P1, A0, A1, U0, U1, Cprim, ...
                                delta, evec, theta, pitch, 1, ZSpdMode.NN);
end
