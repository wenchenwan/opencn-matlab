function [ valid ] = checkParametrisationQueue( queue )
% checkParametrisationQueue : Check whether the curv parametrisation is 
% correct or not.
%
% Inputs :
%   queue       : A queue of curvStruct
%
% Outputs :
%   valid       : Boolean value, TRUE means the parametrisation is sound 
% for all the curvs.
%

valid = false;

N = queue.size;

if( N == 0 )
    valid = true;
    return;
end

for k = 1 : N
    curv = queue.get( k );

    if( ~checkParametrisation( curv ) ),
        return;
    end
end

valid = true;

end