function value = queue_size(ptr)
if coder.target('matlab')
    value = queue_size_mex(ptr);
else
    value = uint32(0);
    value = coder.ceval('c_queue_size', uint64(ptr));
end
end
