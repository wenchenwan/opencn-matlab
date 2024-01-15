function queue_set( ptr, index, elem )
% queue_set : Set an element at a given indey in the queue
%
% Inputs    : 
% ptr       : Handle to a queue instance
% index     : The index in the queue to store the element
% elem      : An element to store in the queue
%
if coder.target( 'MATLAB' )
    queue_set_mex( ptr, index, elem );
else
    coder.ceval( 'c_queue_set', uint64(ptr), uint32(index), elem );
end
end
