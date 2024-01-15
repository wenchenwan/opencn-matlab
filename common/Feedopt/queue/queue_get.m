function [ value ] = queue_get( ptr, value_type, index ) %#codegen
% queue_get : Get an element of the queue at a given index
%
% Inputs    : 
% ptr           : Handle to a queue instance
% value_type    : Value type of an instance in the queue
% index         : Index on the queue
%
% Outputs    : 
% value         : Element in the queue
%
if coder.target( 'MATLAB' )
    value = queue_get_mex( ptr, index );
else
    value = value_type;
    coder.ceval( 'c_queue_get', uint64( ptr ), uint32( index ), ...
        coder.ref( value ) );
end
end
