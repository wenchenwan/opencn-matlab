function CurvStructs = ConstrPolygon3D(Points, vmax)
%
[~, Npts] = size(Points);
%

trafo = false;
A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

CurvStructs = repmat(ConstrLineStruct(trafo, [0,0,0]',[1,1,1]', A0, A1, ...
                                    U0, U1, 0.2, ZSpdMode.NN), 1, Npts-1);

%
for k = 1:Npts-1
    P1 = Points(:, k);
    P2 = Points(:, k+1);
    CurvStructs(k) = ConstrLineStruct(trafo, P1, P2, A0, A1, U0, U1, ...
                                    vmax, ZSpdMode.NN);
end
