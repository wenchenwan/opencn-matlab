function [ value ] = queue_pop( ptr )
% queue_pop : Pop the last element in the queue
%
% Inputs    : 
% ptr   : Handle to a queue instance
%
% Outputs    : 
% value : Element in the queue
%
if coder.target( "MATLAB" )
    value = queue_pop_mex( ptr );
else
    value = coder.ceval( 'c_queue_pop', uint64( ptr ) );
end
end
