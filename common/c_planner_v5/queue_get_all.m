function values = queue_get_all(ptr) %#codegen
if coder.target('matlab')
    values = cell2mat(queue_get_all_mex(ptr));
else
    values = ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    values = coder.ceval('c_queue_get_all', uint64(ptr));
end
end
