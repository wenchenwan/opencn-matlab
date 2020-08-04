function ptr = queue_new()
if coder.target('matlab')
    ptr = queue_new_mex();
else
    ptr = uint64(0);
    ptr = coder.ceval('c_queue_new');
end
end
