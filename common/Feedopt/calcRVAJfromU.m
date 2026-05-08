function [ R, V, A, J ] = calcRVAJfromU( ctx, curv, u_vec, ud_vec, udd_vec, ...
                          uddd_vec )
%#codegen
% calcRVAJfromU : 从样条参数 u 的时间导数，计算位置/速度/加速度/跃度
%
% 原理（链式法则）：
%   曲线用弧长参数 u∈[0,1] 表达：位置 = r(u)
%   时间 t 为自变量，u 是关于 t 的函数
%   因此：
%     位置  R = r(u)
%     速度  V = r'(u) * u'
%     加速度 A = r''(u) * u'^2 + r'(u) * u''
%     跃度  J = r'''(u) * u'^3 + 3*r''(u)*u'*u'' + r'(u)*u'''
%
% Inputs :
%   ctx      : 全局上下文（含运动学对象 kin、配置 cfg）
%   curv     : 当前曲线段结构体
%   u_vec    : [1×M] u 的取值向量
%   ud_vec   : [1×M] u 对时间的一阶导 u'(t)
%   udd_vec  : [1×M] u 对时间的二阶导 u''(t)
%   uddd_vec : [1×M] u 对时间的三阶导 u'''(t)
%
% Outputs :
%   R        : [N×M] 各轴位置
%   V        : [N×M] 各轴速度
%   A        : [N×M] 各轴加速度
%   J        : [N×M] 各轴跃度
%

% 第一步：在 u_vec 处对曲线求 0~3 阶几何导数（对 u 求导，非对 t）
[ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u_vec );

% 第二步：设置刀具长度偏移（用于运动学变换）
ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );

% 第三步：若该曲线段启用了运动学变换（TRAFO），则将笛卡尔坐标转换为关节坐标
if( curv.Info.TRAFO )
    [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
end

% 第四步：用链式法则将 u 的几何导数组合为时间域的运动学量
[ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec, ...
                          udd_vec, uddd_vec, r0D, r1D, r2D, r3D );
end
