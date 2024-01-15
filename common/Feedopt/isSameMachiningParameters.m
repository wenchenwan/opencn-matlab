function [ isSame ] = isSameMachiningParameters( curv1, curv2 )
%#codegen
% isSameMachiningParameters : Check if the machine parameters are equal
%
% Inputs :
%   curv1 : First curve
%   curv2 : Second curve
%
% Outputs :
%   value : Boolean value. TRUE means the two curves machine parameters are equals.
%
isSame = false;
%if( curv1.Info.FeedRate ~= curv2.Info.FeedRate ),           return; end
if( curv1.Info.SpindleSpeed ~= curv2.Info.SpindleSpeed ),   return; end
if( curv1.Info.TRAFO ~= curv2.Info.TRAFO ),                 return; end
isSame = true;
end
