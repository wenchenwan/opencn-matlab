function value = queue_pop(ptr)
if coder.target('matlab')
    value = queue_pop_mex(ptr);
else
    value = coder.ceval('c_queue_pop', uint64(ptr));
    
end
end
