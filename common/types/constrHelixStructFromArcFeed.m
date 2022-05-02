function [ CStrct ] = constrHelixStructFromArcFeed( gcodeInfoStruct, ...
                                                        P0, P1, C, A0, A1, ...
                                                        rotation, evec) %#codegen
% ConstrHelixStructFromArcFeed : Construct a Curv struct filled with the
% parameters of a helix. The resulting helix is the combination of a linear 
% motion along one of the three reference axis ( x, y, z ) with a circular
% motion in the perpendicular plan ( XY, ZX, YZ ).
%
% gcodeInfoStruct : struct containing the information from the Gcode
% P0        : Starting point of the helix P0
% P1        : Ending point of the helix P0
% C         : Center C
% A0        : Vector of the orientation angles at starting pose
% A1        : Vector of the orientation angles at ending pose
% rotation  : Number of rotation to realize (positive ; Clockwise |
%             negative ; Counterclockwise | zero ; pure translation)
% evec      : Unit vector orthogonal to the planned of the projected circle 
%
% CStrct : The resulting CurvStruct
coder.inline( "never" );

% Create vectors
P0 = getColVec( P0 );
P1 = getColVec( P1 );
A0 = getColVec( A0 );
A1 = getColVec( A1 );
C  = getColVec( C );

if evec(1) > 0.5        % YZ
    indYZ = [2, 3]; 
    [~, Cprim, delta] = CorrectArcCenter(P0(indYZ), P1(indYZ), C(indYZ));
    Cprim = [C( 1 ), Cprim(1), Cprim(2)]';
    R0 = cross(evec, P0 - Cprim);
    R1 = cross(evec, P1 - Cprim);
    phi0 = atan2(R0(3), R0(2));
    phi1 = atan2(R1(3), R1(2));
    
elseif evec(2) > 0.5    % ZX
    indZX = [3, 1];
    [~, Cprim, delta] = CorrectArcCenter(P0(indZX), P1(indZX), C(indZX));
    Cprim = [Cprim(2), C( 2 ), Cprim(1)]';
    R0 = cross(evec, P0 - Cprim);
    R1 = cross(evec, P1 - Cprim);
    phi1 = atan2(R0(3), R0(1));
    phi0 = atan2(R1(3), R1(1));
    
else                    % XY
    indXY = [1,2];
    [~, Cprim, delta] = CorrectArcCenter(P0(indXY), P1(indXY), C(indXY));
    Cprim = [Cprim(1), Cprim(2), C( 3 )]';
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

R0 = [ P0; A0 ];
R1 = [ P1; A1 ];

[ CStrct ] = constrHelixStruct( gcodeInfoStruct, R0, R1, Cprim, delta, ...
                                    evec, theta, pitch );
end

function [ col_vec ] = getColVec( vec )
if( isrow( vec ) )
    col_vec = vec';    
else
    col_vec = vec;
end
end
