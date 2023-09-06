function [isSame] = isSameMachiningParameters( curv1, curv2 ) %#codegen
% Check if the machine parameters are equals
isSame = false;
%if( curv1.Info.FeedRate ~= curv2.Info.FeedRate ),           return; end
if( curv1.Info.SpindleSpeed ~= curv2.Info.SpindleSpeed ),   return; end
if( curv1.Info.TRAFO ~= curv2.Info.TRAFO ),                 return; end
isSame = true;
end