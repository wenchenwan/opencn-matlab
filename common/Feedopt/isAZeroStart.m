function [ zeroFlag ] = isAZeroStart( speed )
% isAZeroStart : Return true if the curv starts with zero speed
% 
% Inputs :
% curv / Info / ZSpdMode : A structure containning the information of the
% curv zero speed.
%
% Outputs :
% zeroflag : Boolean value. TRUE means zero structure with a zero speed.
%
zeroFlag = false;

[zspdmode, error] = getZspdmode( speed );

if( error ), return; end

if( zspdmode == ZSpdMode.ZN || ...
    zspdmode == ZSpdMode.ZZ )
    zeroFlag = true; return;
end
end
