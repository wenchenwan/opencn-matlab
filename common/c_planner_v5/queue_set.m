function queue_set(ptr, index, value)
if coder.target('matlab')
    queue_set_mex(ptr, index, value);
else
    coder.ceval('c_queue_set', uint64(ptr), uint32(index), value);
end
end
