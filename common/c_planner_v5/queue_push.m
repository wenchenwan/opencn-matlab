function queue_push(ptr, value)
if coder.target('matlab')
    queue_push_mex(ptr, value);
else
    coder.ceval('c_queue_push', uint64(ptr), value);
end
end
