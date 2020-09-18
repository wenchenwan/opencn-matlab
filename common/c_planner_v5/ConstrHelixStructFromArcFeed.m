function CurvStruct = ConstrHelixStructFromArcFeed(p0x, p0y, p0z, p1x, p1y, p1z, cx, cy, cz, rotation, evec)
%#codegen

P0 = [p0x, p0y, p0z]';
P1 = [p1x, p1y, p1z]';
C  = [cx, cy, cz]';

R0 = cross(evec, P0 - C);
R1 = cross(evec, P1 - C);

if evec(1) > 0.5
    phi0 = atan2(R0(3), R0(2));
    phi1 = atan2(R1(3), R1(2));
    
elseif evec(2) > 0.5
    phi1 = atan2(R0(3), R0(1));
    phi0 = atan2(R1(3), R1(1));
%     rotation = -rotation;
else
    phi0 = atan2(R0(2), R0(1));
    phi1 = atan2(R1(2), R1(1));
end

theta = phi1 - phi0;

devec = dot(evec, P1) - dot(evec, P0);

if rotation > 0
    if theta <= 0
        theta = theta + 2*pi;
    end
    theta = theta + (rotation-1)*2*pi;
    
else
    if theta >= 0
        theta = theta - 2*pi;
    end
    theta = theta + (rotation+1)*2*pi;
    
end

pitch = devec/theta*2*pi;
CurvStruct = ConstrHelixStruct(P0, P1, C, evec, theta, pitch, 1, ZSpdMode.NN);

end
