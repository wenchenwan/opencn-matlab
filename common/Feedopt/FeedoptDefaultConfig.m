function [ cfg ] = FeedoptDefaultConfig()
%#codegen
% FeedoptDefaultConfig : 创建默认配置结构体 cfg
% 所有可调参数都在此处定义，通常流程：
%   cfg = FeedoptDefaultConfig();
%   cfg.vmax = [...];  % 按实际机床修改
%   ctx = initFeedoptPlan(cfg);
%

coder.inline("never");

% -------------------------------------------------------------------------
% 几何预处理参数
% -------------------------------------------------------------------------
tol_col_compress_deg    = 30;  % 压缩阶段：允许的最大方向偏转角（度）
                               % 两线段夹角 < 30° 才认为共线，可合并
tol_col_smooth_deg      = 10;  % 平滑阶段：切线共线容差（更严格，10°）

% -------------------------------------------------------------------------
% Gauss-Legendre 数值积分参数（用于弧长计算）
% -------------------------------------------------------------------------
GaussLegendreN = 5;  % 积分节点数（越大越精确，越慢）
[GaussLegendreX, GaussLegendreW] = lgwt(GaussLegendreN, -1, 1);
% 将区间 [-1,1] 上的 GL 节点和权重翻转（使 u 从 0 到 1 方向积分）
GaussLegendreX = flipud( GaussLegendreX );

% -------------------------------------------------------------------------
% LP 优化器参数
% -------------------------------------------------------------------------
LP = struct(...
    'Type', 'LP', ...
    'USE_JERK_CONSTRAINTS', true,...         % true = 两阶段 LP（含跃度约束）
    'FIND_REASON_INFEASIBILITY', true,...    % LP 不可行时分析原因（调试用）
    'ACC_RAMP_OVER_WINDOWS', 1.0 - 1E-3,... % 窗口末端加速度约束斜坡系数（略小于1）
    'VEL_RAMP_OVER_WINDOWS', 1.0 - 1E-3,... % 窗口末端速度约束斜坡系数
    'SLACK_PENALTY', 10000, ...             % 松弛变量惩罚系数（越大越强制满足约束）
    'USE_LENGTH_SCALING', false, ...        % 是否按弧长缩放决策变量（改善数值条件数）
    'USE_LINPROG', false,...                % false = 用 COIN-OR CLP；true = 用 linprog
    'FORCE_POSITIV_COEFFS', false...        % 是否强制系数非负（实验性功能）
    );

if( ~coder.target('MATLAB') )
    coder.cstructname( LP, StructTypeName.LPCfg );
end

% -------------------------------------------------------------------------
% 运动学参数（XSR 手动 CAM 偏置）
% -------------------------------------------------------------------------
% 说明：XSR 为某型五轴机器人的偏置补偿参数
% 每列对应一个运动学参数（偏置向量，3×1 的 XYZ 分量）
use_XSR_offset = true;

if( use_XSR_offset )
    offM = [ 0, 0, 0 ]';          % 机床基座偏置（mm）
    offT = [ 0, 0, 0 ]';          % 工作台偏置
    offP = [ 0.07155, -0.1645, 1.6 ]'; % 主轴偏置（来自 XSR 标定值）
    offB = [ 0, 0, 0 ]';
    offC = [ 0, 0, 0 ]';
else
    offM = [ 0, 0, -68.802 ]';
    offT = [ 0, 0, 0 ]';
    offP = [ 0, 0, 0 ]';
    offB = [ 0, -60.8, -6.6 ]';
    offC = [ 0, 0, 0 ]';
end

kin_params  = [ offM offT offP offB offC ]; % 拼接为 3×5 矩阵，传给 Kinematics
kin_type    = 'xyzbc_tt'; % 运动学类型：XYZBC 桌台式五轴

% -------------------------------------------------------------------------
% 主配置结构体
% -------------------------------------------------------------------------
cfg = struct(...
    'ENABLE_PRINT_MSG', true, ...           % 是否在控制台打印处理进度

    % 轴掩码：[X, Y, Z, A, B, C]，1 = 激活，0 = 不使用
    'maskTot',  logical( [ 1, 1, 1, 0, 1, 1 ] ),...  % 使用 X/Y/Z/B/C 五轴（A 轴关闭）
    'maskCart', logical( 0 ),...            % 自动计算的笛卡尔轴掩码（勿手动设置）
    'maskRot',  logical( 0 ),...            % 自动计算的旋转轴掩码（勿手动设置）
    'indCart', int32( 0 ), ...              % 笛卡尔轴索引（自动计算）
    'indRot',  int32( 0 ),...               % 旋转轴索引（自动计算）
    'NumberAxis', int32( 0 ), ...           % 激活轴总数（自动计算）
    'NCart',   int32( 0 ), ...              % 笛卡尔轴数（自动计算）
    'NRot',    int32( 0 ), ...              % 旋转轴数（自动计算）
    'D', 0, ...                             % 对角缩放矩阵（自动计算）
    'coeffD', 1, ...                        % 笛卡尔/旋转轴缩放系数（统一单位用）

    'kin_params', reshape( kin_params, [], 1 ), ... % 运动学偏置参数（展平为列向量）
    'kin_type', kin_type, ...               % 运动学类型字符串

    % B 样条和离散化参数
    'NDiscr', int32( 20 ),... % 每段曲线的离散化点数 M（越大约束越密，越慢）
    'NBreak', int32( 10 ),... % B 样条断点数（越多表达能力越强，LP 规模越大）
    'SplitSpecialSpline', true,... % 样条曲线的特殊分割模式
    'ReleaseMemoryOfTheQueues', true, ... % 每个阶段完成后释放前置队列内存

    % 断点分布模式
    'UseDynamicBreakpoints', false,...      % 是否按弧长自动调整断点数
    'UseLinearBreakpoints', true,...        % true = 均匀断点；false = sinspace 断点
    'DynamicBreakpointsDistance', 0.1,...   % 动态模式下断点间距（mm）

    % 优化窗口参数
    'NHorz', int32( 5 ),... % 滑动窗口中的曲线段数（越大考虑更远预瞻，但 LP 规模增大）

    % 机床约束（严格上限，优化时不可超过）
    'vmax', [500,500,500,0, 40,50],...        % 各轴最大速度 [mm/s, mm/s, mm/s, -, rad/s, rad/s]
    'amax', [15000,15000,15000,0, 200,1000],... % 各轴最大加速度 [mm/s², ..., rad/s²]
    'jmax', [1500000,1500000,1500000,0,10000,50000],... % 各轴最大跃度 [mm/s³, ..., rad/s³]

    % B 样条配置
    'LeeSplineDegree', int32( 4 ),... % Lee 压缩算法使用的 B 样条阶次（4 = 三次）
    'SplineDegree',    int32( 3 ),... % 优化用 B 样条阶次（3 = 二次，较快）

    % 几何处理长度阈值（单位 mm）
    'CutOff', 1E-1,...         % 过渡曲线切割长度：每端切掉 0.1mm
    'LSplit',  3,...            % 正常段的最大分割长度（超过则切为多段）
    'LSplitZero', 1,...         % 零速段附近的分割长度（更短，精确控制减速）
    'LThresholdMax', 3,...      % 可参与压缩的最大线段长度（超过则不压缩）
    'LThresholdMin', 5E-1,...   % 极短线段（< 0.5mm）跳过共线检查，强制加入批次

    % 边界条件（整条轨迹的起/末速度，通常均为 0 表示从静止开始到静止结束）
    'v_0', 0, 'at_0', 0,...     % 起点：速度 = 0，切向加速度 = 0
    'v_1', 0, 'at_1', 0,...     % 终点：速度 = 0，切向加速度 = 0

    'dt', 1e-3, ...             % 重采样时间步长（1ms，即 1000Hz 输出）
    'DefaultZeroStopCount', 1,... % 零速段的默认停留时间步数

    'source', repmat(char(0), [1, 1024]),... % G-code 文件路径（字符串，最长 1024）

    % 尖点检测配置
    'Cusp', struct(...
        'Skip', false,...          % false = 执行尖点检测
        'CuspThreshold', 10 ...    % 尖点阈值：两段夹角 > 10° 认为是尖点，插入零速
    ),...

    % 曲线压缩配置
    'Compressing', struct(...
        'Skip', false,...
        'ColTolCosLee', cosd(tol_col_compress_deg) ... % 共线 cos 容差（cos(30°)≈0.866）
    ),...

    % 曲线平滑配置
    'Smoothing', struct( ...
        'Skip', false,...
        'ColTolCosSmooth', cosd(tol_col_smooth_deg), ... % 平滑共线 cos 容差（cos(10°)≈0.985）
        'ColTolSmooth',    1E-5 ...                      % 位置连续性绝对容差（mm）
    ), ...

    % Gauss-Legendre 数值积分（弧长计算）
    'GaussLegendreN', GaussLegendreN, ...
    'GaussLegendreX', GaussLegendreX, ...
    'GaussLegendreW', GaussLegendreW, ...

    'opt', LP,...                 % LP 优化器参数子结构体

    'LogFileName', 'logs/logs' ... % 日志文件前缀
    );

% 代码生成：声明可变尺寸字段
if ~coder.target( 'MATLAB' )
    coder.varsize( 'cfg.indCart',       StructTypeName.dimInd{ : } );
    coder.varsize( 'cfg.indRot',        StructTypeName.dimInd{ : } );
    coder.varsize( 'cfg.maskTot',       StructTypeName.dimMask{ : } );
    coder.varsize( 'cfg.maskCart',      StructTypeName.dimMask{ : } );
    coder.varsize( 'cfg.maskRot',       StructTypeName.dimMask{ : } );
    coder.varsize( 'cfg.D',             StructTypeName.dimD{ : } );
    coder.varsize( 'cfg.source',        StructTypeName.dimFileName{ : } );
    coder.varsize( 'cfg.kin_params',    StructTypeName.dimKinParams{ : } );
    coder.cstructname( cfg,             StructTypeName.FeedoptCfg );
end

% 根据 maskTot 自动计算轴索引等衍生字段
[ cfg ] = setMachineAxisInConfig( cfg, cfg.maskTot );

end
