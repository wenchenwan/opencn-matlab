function [ ctx ] = CheckCurvStructs( ctx )
% CheckCurvStruct : Check if the curve contains some CUSP. If so force a
% zero stop.
%
% Inputs    :
%   ctx :   The context of the computational chain
% Outputs   :
%   ctx :   The context of the computational chain
%

% ============================================================================
% 初始化：设置计数器和获取曲线总数
% ============================================================================
ctx.k0  = int32( 1 );              % 初始化曲线计数器为1（当前处理的曲线索引）
N       = ctx.q_gcode.size;        % 获取G代码中曲线队列的总数量

% 输出日志信息
DebugLog( DebugCfg.Validate, 'Checking for cusps...\n' );
DebugLog( DebugCfg.OptimProgress, 'Checking for cusps...\n' );

% ============================================================================
% 主循环：逐对检查相邻曲线间的尖点（CUSP）
% ============================================================================
curv1 = ctx.q_gcode.get( 1 );      % 获取第一条曲线作为起始
for k = 2 : N                       % 从第二条曲线开始遍历到最后一条
    ctx.k0  = ctx.k0 + 1;          % 更新计数器
    curv2   = ctx.q_gcode.get( k ); % 获取当前要检查的曲线
    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + N, mfilename );  % 打印处理进度
    
    % ========================================================================
    % 尖点检测：计算相邻两条曲线的方向导数（在局部坐标系中）
    % ========================================================================
    % 获取曲线1末端的导数（参数1表示在曲线末端，即参数u=1处）
    [~, r0D1] = EvalCurvStructInPieceFrame( ctx, curv1, 1 );
    % 获取曲线2起点的导数（参数0表示在曲线起点，即参数u=0处）
    [~, r1D1] = EvalCurvStructInPieceFrame( ctx, curv2, 0 );

    % 判断条件：曲线1末端不是零速 且 两条曲线间存在尖点（方向变化过大）
    if ( ~isAZeroEnd( curv1 ) ) && ... 
        iscusp( r0D1( ctx.cfg.indCart ), r1D1( ctx.cfg.indCart ), ...
                ctx.cfg.Cusp.CuspThreshold )

        % ====================================================================
        % 尖点处理1：修改曲线1的速度模式（末端强制为零速）
        % ====================================================================
        % ZSpdMode含义：第一个字符为起点，第二个字符为末端；N=非零速，Z=零速
        switch curv1.Info.zspdmode
            case ZSpdMode.NN        % 起点非零、末端非零 → 改为末端零速
                curv1.Info.zspdmode = ZSpdMode.NZ;
            case ZSpdMode.ZN        % 起点零速、末端非零 → 改为起点末端都零速
                curv1.Info.zspdmode = ZSpdMode.ZZ;
            otherwise               % 其他情况（已是ZZ或ZN）保持不变
        end
        
        % ====================================================================
        % 尖点处理2：修改曲线2的速度模式（起点强制为零速）
        % ====================================================================
        switch curv2.Info.zspdmode
            case ZSpdMode.NN        % 起点非零、末端非零 → 改为起点零速
                curv2.Info.zspdmode = ZSpdMode.ZN;
            case ZSpdMode.NZ        % 起点非零、末端零速 → 改为起点末端都零速
                curv2.Info.zspdmode = ZSpdMode.ZZ;
            otherwise               % 其他情况（已是ZZ或ZN）保持不变
        end
        
        % ====================================================================
        % 保存修改后的曲线信息回队列
        % ====================================================================
        ctx.q_gcode.set( k - 1,   curv1 );  % 保存修改后的曲线1
        ctx.q_gcode.set( k, curv2 );        % 保存修改后的曲线2
        
        % 如果编译目标是MATLAB环境，记录调试信息
        if( coder.target( "MATLAB" ) )
            DebugCusp.getInstance.add( curv1, curv2 );  % 向调试对象添加尖点信息
        end
    end

    % 更新curv1：当前曲线变为下一次迭代的前一条曲线
    curv1 = curv2;
end    
end
