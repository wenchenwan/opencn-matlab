function [ zeroFlag ] = isAZeroStart( curv )
% isAZeroStart : Return true if the curv starts with zero speed
% curv  : The curve struct
    if( curv.Info.zspdmode == ZSpdMode.ZN || ...
        curv.Info.zspdmode == ZSpdMode.ZZ )
        zeroFlag = true; return;
    end
    zeroFlag = false;
end