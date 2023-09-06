function [ zeroFlag ] = isAZeroSpeed( speed )
% isAZeroSpeed : Return true if the curv is has a zero speed
% Input :
% curv / Info / ZSpdMode : A structure containning the information of the
% curv zero speed.zeroFlag = false;

[zspdmode, error] = getZspdmode( speed );

if( error ), return; end    

zeroFlag = ( zspdmode ~= ZSpdMode.NN );

end