function [ values ] = queue_get_all( ptr ) %#codegen
% queue_get_all : Get all the elements of the queue
% Outputs :
% ptr       : Handle to a queue instance
%
% Outputs :
% values    : Values in the queue
%
if coder.target( 'MATLAB' )
    values = cell2mat( queue_get_all_mex( ptr ) );
else
    values = constrCurvStructType;
    values = coder.ceval( 'c_queue_get_all', uint64( ptr ) );
end
end
