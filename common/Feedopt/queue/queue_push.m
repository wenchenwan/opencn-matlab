function queue_push( ptr, elem )
% queue_push : Push an element at the end of the queue
%
% Inputs    : 
% ptr   : Handle to a queue instance
% elem  : Element to add to the queue
%
if coder.target( "MATLAB" )
    queue_push_mex( ptr, elem );
else
    coder.ceval( 'c_queue_push', uint64(ptr), elem );
end
end
