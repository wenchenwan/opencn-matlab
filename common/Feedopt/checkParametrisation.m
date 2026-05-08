function [ valid ] = checkParametrisation( curv )
% checkParametrisation : 验证曲线结构体的参数窗口是否合法
%
% 【参数窗口合法性条件】
%   a_param（窗口宽度）和 b_param（窗口起点）须满足：
%     1. a_param ∈ (0, 1]        — 宽度为正且不超过全段
%     2. b_param ∈ [0, 1)        — 起点在 [0,1) 范围内
%     3. a_param + b_param ≤ 1  — 窗口不超出 [0,1] 的右边界
%
%   合法示例：
%     完整段：a=1, b=0     → u_g ∈ [0,1]（整条曲线）
%     左半段：a=0.5, b=0   → u_g ∈ [0,0.5]
%     右半段：a=0.5, b=0.5 → u_g ∈ [0.5,1]
%     内部截段：a=0.3, b=0.4 → u_g ∈ [0.4,0.7]
%
%   不合法情况（返回 false）：
%     a_param=0           — 退化为点，无长度
%     b_param+a_param > 1 — 超出参数范围（含浮点 eps 容差）
%
% Inputs :
%   curv  : 曲线结构体（需含 a_param 和 b_param 字段）
%
% Outputs :
%   valid : true = 参数窗口合法；false = 非法（禁止求值）
%
    valid = false;
    if( ~(curv.a_param > 0 && curv.a_param <= 1) ), return; end       % 条件 1
    if( ~(curv.b_param >= 0 && curv.b_param < 1) ), return; end       % 条件 2
    if( curv.a_param + curv.b_param -1 > eps ), return; end            % 条件 3
    valid = true;
end
