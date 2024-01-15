function [ ptr ] = queue_new()
% queue_new : Create a new queue
%
% Outputs :
% ptr   : Handle to a queue instance
%
if coder.target( 'MATLAB' )
    ptr = queue_new_mex();
else
    ptr = uint64( 0 );
    ptr = coder.ceval( 'c_queue_new' );
end
end
