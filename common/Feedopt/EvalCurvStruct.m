function [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, curv, u_vec )
%#codegen
% EvalCurvStruct : Eval curve structure and its derivatives on a set of u
% points.
%
% 功能描述：
%   在参数空间中评估曲线结构及其导数
%   支持从曲线队列中获取对应的B样条曲线数据并计算导数
%
% Inputs : 
%   ctx   : 计算链的上下文对象（包含配置和曲线队列）
%   curv  : 要评估的曲线结构体
%   u_vec : 参数向量（0到1之间的值），表示曲线上的参数位置
%
% Outputs : 
%   r0D   : 位置矩阵（0阶导数） - 给定u值集合对应的参数空间点坐标
%   r1D   : 速度矩阵（1阶导数） - 给定u值集合对应的参数空间速度向量
%   r2D   : 加速度矩阵（2阶导数） - 给定u值集合对应的参数空间加速度向量
%   r3D   : 加加速度矩阵（3阶导数） - 给定u值集合对应的参数空间加加速度向量
%

coder.inline("never");  % 禁止函数内联，用于代码调试追踪

% ============================================================================
% 初始化：获取曲线对应的B样条数据
% ============================================================================

% 持久化变量：缓存默认的B样条结构体，避免重复创建
persistent splineDefault;

% 首次调用时初始化默认B样条结构体
if( isempty( splineDefault ) ), splineDefault = constrCurvStructType; end

% ============================================================================
% 曲线类型判断：确定使用哪个B样条数据
% ============================================================================

if( curv.Info.Type == CurveType.Spline )
    % 如果曲线类型是B样条（Spline），则从曲线队列中获取对应的B样条数据
    ptr    = curv.sp_index;                    % 获取B样条在队列中的索引
    spline = ctx.q_spline.get( ptr );          % 从队列中提取对应的B样条结构体
else
    % 如果曲线类型不是B样条（如直线、圆弧等），则使用默认的空B样条结构体
    spline = splineDefault;
end

% ============================================================================
% 调用核心计算函数：计算曲线的位置和导数
% ============================================================================
% EvalCurvStructNoCtx 是实际计算导数的函数
% 输入参数：
%   ctx.cfg    - 配置参数集
%   curv       - 曲线结构体信息
%   spline     - B样条数据（如果曲线是样条）
%   u_vec      - 参数位置集
[ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline, u_vec );

end
