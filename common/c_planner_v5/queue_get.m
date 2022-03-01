function value = queue_get(ptr, value_type, index) %#codegen
if coder.target('matlab')
    value = queue_get_mex(ptr, index);
else
    value = value_type;
    coder.ceval('c_queue_get', uint64(ptr), uint32(index), coder.ref(value));
end
end
