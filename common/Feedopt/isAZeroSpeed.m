function [ zeroFlag ] = isAZeroSpeed( speed )
% isAZeroSpeed : Return true if the curv is has a zero speed
% 
% Inputs :
% curv / Info / ZSpdMode : A structure containning the information of the
% curv zero 
% 
% Outputs :
% zeroFlag : Boolean value. TRUE means zero speed structure.
%

zeroFlag = false;

[zspdmode, error] = getZspdmode( speed );

if( error ), return; end    

zeroFlag = ( zspdmode ~= ZSpdMode.NN );

end
