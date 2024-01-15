function [ value ] = queue_size( ptr )
% queue_size : Get the queue size
%
% Inputs    : 
% ptr       : Handle to a queue instance
% 
% Outputs   :
% value     : The size of the queue
%
if coder.target( "MATLAB" )
    value = queue_size_mex( ptr );
else
    value = uint32( 0 );
    value = coder.ceval( 'c_queue_size', uint64( ptr ) );
end
end
