function queue_delete(ptr)
if coder.target('matlab')
    queue_delete_mex(ptr);
else
    coder.ceval('c_queue_delete', uint64(ptr));
end
end
