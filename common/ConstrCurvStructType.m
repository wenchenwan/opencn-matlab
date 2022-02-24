function C = ConstrCurvStructType
    trafo       = false;
    HSC         = false;
    HSC_cmd = char(zeros(1,256));
    Poff        = zeros(3,1);
    Aoff        = zeros(3,1);
    Uoff        = zeros(3,1);
    Doff        = 0.0;
    P0          = zeros(3,1);
    P1          = zeros(3,1);
    A0          = zeros(3,1);
    A1          = zeros(3,1);
    U0          = zeros(3,1);
    U1          = zeros(3,1);
    FeedRate    = 0.2;
    
    C = ConstrLineStruct(trafo, HSC, HSC_cmd, Poff, Aoff, Uoff, Doff, P0, P1, A0, A1, ...
                            U0, U1, FeedRate,  ZSpdMode.NN);
end