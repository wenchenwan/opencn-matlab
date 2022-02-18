function CurvStructs = ConstrPolygon3D(Points, vmax)
%
[~, Npts] = size(Points);
%

trafo = false;
A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;
Poff = zeros(3,1); Aoff = Poff; Uoff = Poff; Doff = 0;
P0 = zeros(3,1); P1 = ones(3,1);
FeedRate = 0.2;

line = ConstrLineStruct(trafo, Poff, Aoff, Uoff, Doff, P0,...
                        P1, A0, A1, U0, U1, FeedRate, ZSpdMode);

CurvStructs = repmat( line, 1, Npts-1 );

%
for k = 1:Npts-1
    P1 = Points(:, k);
    P2 = Points(:, k+1);
    CurvStructs(k) = ConstrLineStruct( trafo, Poff, Aoff, ...
                                      Uoff, Doff, P1, P2, A0, A1, U0, ...
                                      U1, vmax, ZSpdMode );
end
