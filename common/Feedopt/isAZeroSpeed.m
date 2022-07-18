function [ speedFlag ] = isAZeroSpeed( curv )
% isAZeroSpeed : Return true if the curv is has a zero speed
% Input :
% curv  : The curve struct
    speedFlag = ( curv.Info.zspdmode ~= ZSpdMode.NN );
end