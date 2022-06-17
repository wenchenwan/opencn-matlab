function [ zeroFlag ] = isAZeroEnd( curv )
% isAZeroEnd : Return true if the curv ends with zero speed
% Input :
% curv  : The curve struct
    if( curv.Info.zspdmode == ZSpdMode.NZ || ...
        curv.Info.zspdmode == ZSpdMode.ZZ )
        zeroFlag = true; return;
    end
    zeroFlag = false;
end