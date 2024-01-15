function queue_delete( ptr )
% queue_delete : Delete the queue and it elements
%
% Inputs :
% ptr   : Pointer to a queue instance
% 
if coder.target( 'MATLAB' )
    queue_delete_mex( ptr );
else
    coder.ceval( 'c_queue_delete', uint64( ptr ) );
end
end
