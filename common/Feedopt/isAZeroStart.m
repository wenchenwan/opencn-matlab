function [ zeroFlag ] = isAZeroStart( speed )
% isAZeroStart : 判断曲线段是否以零速起始
%
% 零速起始条件：zspdmode 为 ZN 或 ZZ（起端均为零速）
%
% Inputs :
%   speed : 曲线结构体（含 Info.zspdmode 字段）或其他包含 zspdmode 的结构
%
% Outputs :
%   zeroFlag : true = 该段从零速出发（需要零速约束）；false = 普通起始
%
zeroFlag = false;

[zspdmode, error] = getZspdmode( speed );

if( error ), return; end

if( zspdmode == ZSpdMode.ZN || ...
    zspdmode == ZSpdMode.ZZ )
    zeroFlag = true; return;
end
end
