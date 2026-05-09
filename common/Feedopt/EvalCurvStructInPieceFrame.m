function [r0D, r1D, r2D, r3D] = EvalCurvStructInPieceFrame( ctx, curv, u_vec )
%#codegen
% EvalCurvStructInPieceFrame : Eval curve structure and its derivatives on 
% a set of u points on the piece frame (WCS).
%
% 功能描述：
%   在工件坐标系（WCS）中，评估曲线结构及其导数
%   支持计算0阶到3阶导数（位置、速度、加速度、加加速度）
%
% Inputs : 
%   ctx   : 计算链的上下文对象
%   curv  : 用于评估的曲线结构体
%   u_vec : 参数向量（0到1之间的值），表示曲线上的参数位置
%
% Outputs : 
%   r0D   : 位置矩阵（0阶导数）- 给定u值集合对应的空间点坐标
%   r1D   : 速度矩阵（1阶导数）- 给定u值集合对应的速度向量
%   r2D   : 加速度矩阵（2阶导数）- 给定u值集合对应的加速度向量
%   r3D   : 加加速度矩阵（3阶导数）- 给定u值集合对应的加加速度向量
%
coder.inline("never");  % 禁止此函数内联，保证代码可追踪性

% ============================================================================
% 第一步：在参数空间中计算曲线及其导数
% ============================================================================
% 调用EvalCurvStruct函数计算在参数空间中的位置和导数信息
% 该函数返回原始的B样条或其他曲线的导数值
[r0D, r1D, r2D, r3D]= EvalCurvStruct( ctx, curv, u_vec );

% ============================================================================
% 第二步：应用运动学变换（从参数空间转换到工件坐标系WCS）
% ============================================================================
% 判断是否需要应用运动学变换
% curv.Info.TRAFO=true时，表示曲线已在工件坐标系中，无需转换
% curv.Info.TRAFO=false时，需要应用运动学变换（正解、雅可比等）
if( ~curv.Info.TRAFO )
    % 设置刀具长度偏移量（Z轴方向，取负值）
    % 这在多轴加工中用于补偿刀具的长度
    ctx.kin.set_tool_length( -curv.tool.offset.z );
    
    % 应用运动学正解变换，将参数空间的导数转换到工件坐标系
    % ctx.kin.relative() 计算相对于工件的坐标和导数
    % 输入：参数空间的位置和三阶导数
    % 输出：工件坐标系中的位置和对应的导数
    [r0D, r1D, r2D, r3D] = ctx.kin.relative(r0D, r1D, r2D, r3D);
end

end
