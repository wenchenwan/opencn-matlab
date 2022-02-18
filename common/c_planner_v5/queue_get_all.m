function values = queue_get_all(ptr) %#codegen
if coder.target('matlab')
    values = cell2mat(queue_get_all_mex(ptr));
else
    trafo = false; % TRAFO flag disable
    Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
    A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0;

    values = ConstrLineStruct(trafo, Poff, Aoff, Uoff, ...
                              Doff, [0,0,0]', [0,0,0]', A0, A1, U0, ...
                              U1, 0.2, ZSpdMode.NN);
    values = coder.ceval('c_queue_get_all', uint64(ptr));
end
end
