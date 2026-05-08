function [ ret, curvLeft, curvRight ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
%#codegen
% cutCurvStruct : 将曲线在弧长 L 处切成左右两半
%
% 切割不重新拟合曲线，只更新参数"窗口"（a_param/b_param）。
% B 样条几何数据只有一份，每个子段记录自己能用哪段全局参数区间。
%
% 参数映射（EvalCurvStructNoCtx 中使用）：
%   u_global = a_param * u_local + b_param
%
%   b_param = 这段曲线在全局参数空间的起点（窗口左边界）
%   a_param = 这段曲线在全局参数空间的跨度（窗口宽度）
%
% 例：原曲线 a=1,b=0，在 u_tilda=0.93 处截取
%   左段：b=0,    a=0.93  → u_local=0→查0.00, u_local=1→查0.93
%   右段：b=0.93, a=0.07  → u_local=0→查0.93, u_local=1→查1.00
%
% Inputs :
%   ctx   : 上下文（含配置、队列等）
%   curv  : 待截取的曲线段（CurvStruct）
%   u0    : 截取起始的局部参数值（通常为 0 或 1）
%   L     : 截取长度（mm）
%   isEnd : true = 从末端往回截 L；false = 从 u0 往前截 L
%
% Outputs :
%   ret       : 0 = 成功；-1 = 失败（曲线太短或找不到截点）
%   curvLeft  : 截取后的左半段（保留起端）
%   curvRight : 截取后的右半段（保留末端）
%
curvLeft = curv; curvRight = curvLeft;
ret   = 0;

% 第一步：求截点的全局参数值 u_tilda
% u_tilda 是切割点在全局参数空间 [0,1] 中的位置
% 对 Spline 类型：用 splineLengthFindU（弧长反求，二分法）
% 对 Line/Helix：用解析公式（均匀参数化，‖r'(u)‖ 为常数）
u_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );

% 截点无效（曲线总长 <= L，或二分法不收敛）→ 截取失败
if( u_tilda <= 0 ), ret = -1; return; end

a = curv.a_param;   % 原曲线的参数映射斜率（区间长度）
b = curv.b_param;   % 原曲线的参数映射偏移（区间起点）
% 原曲线全局参数范围：[b, b+a]

% -------------------------------------------------------------------------
% 第二步：更新右半段的参数映射
% 右半段 = 截点到原末端 → 全局范围 [u_tilda, b+a]
% -------------------------------------------------------------------------
curvRight.b_param = u_tilda;              % 右半段起点 = 截点（> 0，非全段）
curvRight.a_param = a + b - curvRight.b_param;  % 右半段长度 = 原终点 - 截点

% 右半段的零速状态：
%   - 起端（截点处）：内部点，不是零速边界 → 继承原状态中只保留末端零速信息
%   - 末端：与原曲线末端相同（若原来是 NZ/ZZ，右半段末端仍是零速）
if( isAZeroEnd( curvRight ) )
    curvRight.Info.zspdmode = ZSpdMode.NZ;  % 末端零速，起端正常
else
    curvRight.Info.zspdmode = ZSpdMode.NN;  % 两端均正常速度
end

ocn_assert( checkParametrisation( curvRight ), ...
    "Parametrisation is not correct...", mfilename );

% -------------------------------------------------------------------------
% 第三步：更新左半段的参数映射
% 左半段 = 原起点到截点 → 全局范围 [b, u_tilda]
% -------------------------------------------------------------------------
curvLeft.a_param = u_tilda - curvLeft.b_param;  % 左半段长度 = 截点 - 原起点
% curvLeft.b_param 不变（起点和原曲线相同）

% 左半段的零速状态：
%   - 起端：与原曲线起端相同（若原来是 ZN/ZZ，左半段起端仍是零速）
%   - 末端（截点处）：内部点，不是零速边界 → 正常速度
if( isAZeroStart( curvLeft ) )
    curvLeft.Info.zspdmode = ZSpdMode.ZN;   % 起端零速，末端正常
else
    curvLeft.Info.zspdmode = ZSpdMode.NN;   % 两端均正常速度
end

ocn_assert( checkParametrisation( curvLeft ), ...
    "Parametrisation is not correct...", mfilename  );

end
