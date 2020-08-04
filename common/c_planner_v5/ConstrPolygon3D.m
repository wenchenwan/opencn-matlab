function CurvStructs = ConstrPolygon3D(Points, vmax)
%
[~, Npts] = size(Points);
%
CurvStructs = repmat(ConstrLineStruct([0,0,0]',[1,1,1]', 0.2, ZSpdMode.NN), 1, Npts-1);

%
for k = 1:Npts-1
    P1 = Points(:, k);
    P2 = Points(:, k+1);
    CurvStructs(k) = ConstrLineStruct(P1, P2, vmax, ZSpdMode.NN);
end
