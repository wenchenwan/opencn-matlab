function q = queue(value_type)%#codegen
% queue : Create and return a queue of the provided input type
%
% Inputs :
%  value_type   : A value type that the queue should contains
% Outputs :
%   q           : A queue of the instance passed as input
%
    q = queue_coder(value_type);
end
