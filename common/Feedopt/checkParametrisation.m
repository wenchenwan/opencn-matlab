function [ valid ] = checkParametrisation( curv )
% checkParametrisation : Check whether the curv parametrisation is correct 
% or not.
%
% Inputs :
%   curv        : A curvStruct
%
% Outputs :
%   valid       : Boolean value, TRUE means the parametrisation is sound.
%
    valid = false;
    if( ~(curv.a_param > 0 && curv.a_param <= 1) ), return; end
    if( ~(curv.b_param >= 0 && curv.b_param < 1) ), return; end
    if( curv.a_param + curv.b_param -1 > eps ), return; end
    valid = true;
end
