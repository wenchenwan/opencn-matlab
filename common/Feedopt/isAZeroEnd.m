function [ zeroFlag ] = isAZeroEnd( speed )
% isAZeroEnd : Return true if the curv ends with zero speed
% 
% Inputs :
% curv / Info / ZSpdMode : A structure containning the information of the
% curv zero speed.
% 
% Outputs : 
% zeroFlag : Boolean value. TRUE mean zero flag
zeroFlag = false;

[zspdmode, error] = getZspdmode( speed );

if( error ), return; end

if( zspdmode == ZSpdMode.NZ || ...
    zspdmode == ZSpdMode.ZZ )
    zeroFlag = true; return;
end
end
