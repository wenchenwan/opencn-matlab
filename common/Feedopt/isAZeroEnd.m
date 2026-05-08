function [ zeroFlag ] = isAZeroEnd( speed )
% isAZeroEnd : 判断曲线段是否以零速结束
%
% 零速终止条件：zspdmode 为 NZ 或 ZZ（末端均为零速）
%
% Inputs :
%   speed : 曲线结构体（含 Info.zspdmode 字段）或其他包含 zspdmode 的结构
%
% Outputs :
%   zeroFlag : true = 该段以零速结束（需要零速约束）；false = 普通终止
%
zeroFlag = false;

[zspdmode, error] = getZspdmode( speed );

if( error ), return; end

if( zspdmode == ZSpdMode.NZ || ...
    zspdmode == ZSpdMode.ZZ )
    zeroFlag = true; return;
end
end
