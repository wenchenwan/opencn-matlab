function CurvStruct = ConstrHelixStructFromArcFeed(p0x, p0y, p0z, p1x, p1y, p1z, cx, cy, cz, rotation, evec)
%#codegen
coder.inline("never");

P0 = [p0x, p0y, p0z]';
P1 = [p1x, p1y, p1z]';
C  = [cx, cy, cz]';

if evec(1) > 0.5        % YZ
    [~, Cprim, delta] = CorrectArcCenter([P0(2), P0(3)]', [P1(2), P1(3)]', [C(2), C(3)]');
    Cprim = [cx, Cprim(1), Cprim(2)]';
    R0 = cross(evec, P0 - Cprim);
    R1 = cross(evec, P1 - Cprim);
    phi0 = atan2(R0(3), R0(2));
    phi1 = atan2(R1(3), R1(2));
    
elseif evec(2) > 0.5    % ZX
    [~, Cprim, delta] = CorrectArcCenter([P0(3), P0(1)]', [P1(3), P1(1)]', [C(3), C(1)]');
    Cprim = [Cprim(2), cy, Cprim(1)]';
    R0 = cross(evec, P0 - Cprim);
    R1 = cross(evec, P1 - Cprim);
    phi1 = atan2(R0(3), R0(1));
    phi0 = atan2(R1(3), R1(1));
    
else                    % XY
    [~, Cprim, delta] = CorrectArcCenter([P0(1), P0(2)]', [P1(1), P1(2)]', [C(1), C(2)]');
    Cprim = [Cprim(1), Cprim(2), cz]';
    R0 = cross(evec, P0 - Cprim);
    R1 = cross(evec, P1 - Cprim);
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
CurvStruct = ConstrHelixStruct(P0, P1, Cprim, delta, evec, theta, pitch, 1, ZSpdMode.NN);

end
