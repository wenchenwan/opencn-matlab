function [ zspdmode, error ] = getZspdmode( speed )
%#codegen
% getZspdmode : 从多种类型的参数中提取零速模式（ZSpdMode）
%
% 采用"鸭子类型"策略：speed 可以是枚举值、CurvStruct 或简单结构体，
% 函数按优先级依次尝试，找到后立即返回。
%
% 优先级：
%   1. speed 本身就是 ZSpdMode 枚举 → 直接返回
%   2. speed 含 Info 子结构（如 CurvStruct）→ 取 speed.Info.zspdmode
%   3. speed 直接含 zspdmode 字段 → 取 speed.zspdmode
%   4. 无法识别 → error=true（调用方须先检查 error，勿使用 zspdmode）
%
% Inputs :
%   speed    : ZSpdMode 枚举、CurvStruct 或含 zspdmode 字段的结构体
%
% Outputs :
%   zspdmode : 提取到的零速模式（error=true 时为占位值，勿使用）
%   error    : false = 成功提取；true = 无法识别类型

error    = false;
zspdmode = ZSpdMode.NN;  % 占位初始化，防止 codegen 报未赋值警告

if( isenum( speed ) )
    % speed 本身即为 ZSpdMode 枚举，直接返回
    zspdmode = speed;
elseif( isfield( speed, "Info") )
    % CurvStruct 类型：zspdmode 存放在 Info 子结构中
    zspdmode = speed.Info.zspdmode;
elseif( isfield( speed, "zspdmode") )
    % 简化结构体：zspdmode 直接作为顶层字段
    zspdmode = speed.zspdmode;
else
    % 无法识别的类型，无法提取 zspdmode
    % 调用方（isAZeroStart / isAZeroEnd）通过 if(error), return; end 提前退出
    error = true;
    return;
end
end
