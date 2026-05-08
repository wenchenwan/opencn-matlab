%% Basic example — OpenCN 完整流程示例
% 本脚本演示从 G-code 文件到时间最优轨迹的完整处理流程：
%   1. 加载配置并初始化
%   2. 运行 FSM（G-code 解析 → 几何处理 → LP 优化）
%   3. 重采样到均匀时间步
%   4. 验证约束满足性和时间最优性
%   5. 绘图并保存结果
%
clc; clear all; close all;

check_wkdir(); % 确保当前目录是工作目录（common/），否则报错

% 默认测试 G-code 文件（穹顶雕刻路径，约 37 条曲线）
sourceFileName = 'ngc_test/E2C/037_dome_gravure_v1.ngc';

% -------------------------------------------------------------------------
% 控制开关（调试/分析用）
% -------------------------------------------------------------------------
LoadContextFromFile             = false; % true = 跳过处理，直接从 .mat 加载上次的 ctx
SaveContextInFile               = false; % true = 处理完成后将 ctx 保存到 .mat（便于调试）
PlotGeometry                    = true;  % true = 绘制曲线几何图形
CreateFileForSampler            = false; % true = 额外生成采样器格式的 CSV（PR2 机器人用）
DeleteCSVFileAfterResampling    = false; % true = 重采样完成后删除临时 CSV

% -------------------------------------------------------------------------
% 初始化调试单例（仅 MATLAB 模式，代码生成中不存在这些对象）
% -------------------------------------------------------------------------
if( coder.target( "MATLAB" ) )
    DebugCusp.getInstance.reset;           % 重置尖点调试记录
    DebugCompressing.getInstance.reset;    % 重置压缩调试记录
    DebugTransition.getInstance.reset;     % 重置过渡曲线调试记录
    DebugOptimization.getInstance.reset;   % 重置优化调试记录
    DebugResampling.getInstance.reset;     % 重置重采样调试记录
end

% -------------------------------------------------------------------------
% 加载或创建上下文 ctx
% -------------------------------------------------------------------------
if( LoadContextFromFile )
    [ ret, ctx ] = loadCtx( "dev/test.mat" ); % 从文件恢复之前保存的 ctx
end

if( ~exist( 'ctx', 'var' ) )
    % 正常初始化流程
    cfg = FeedoptDefaultConfig();           % 创建默认配置
    ConfigSetSource( cfg, sourceFileName ); % 设置 G-code 文件路径
    cfg.source = sourceFileName;
    ctx = initFeedoptPlan( cfg );           % 初始化上下文（B 样条基、队列、运动学）
end

% -------------------------------------------------------------------------
% 日志设置
% -------------------------------------------------------------------------
setupLogs( cfg.LogFileName ); diary on;

try
    % =====================================================================
    % 主处理：运行有限状态机
    % 状态顺序：Init→GCode→Check→Compress→Smooth→Split→Opt→Finished
    % =====================================================================
    ctx = FeedoptPlanRun( ctx );

    % 检查处理结果：若有错误，抛出异常
    if( ctx.errcode ~= FeedoptPlanError.NoError )
        error( '%s\n', ctx.errmsg.msg( 1 : ctx.errmsg.size ) );
    end

    % 保存 ctx 以供后续分析（可选）
    if( SaveContextInFile )
        [ ret ] = saveCtx( ctx, "dev/test.mat" );
    end

    % 打印 LP 优化统计信息（仅 MATLAB 模式）
    if( coder.target( 'MATLAB' ) )
        DebugOptimization.getInstance().print();
    end

    % 绘制优化前后的几何曲线（三组：原始 G-code、压缩后、优化后）
    if( PlotGeometry )
        [ fig ] = plotGeometry( ctx, ctx.q_gcode, ctx.q_spline, ...
            "Gcode Line" );                 % 原始 G-code 线段
        [ fig ] = plotGeometryOnlyStartPoints( ctx, ctx.q_gcode, ...
            ctx.q_spline, "Gcode Point", fig ); % 原始起点散点图
        [ fig ] = plotGeometry( ctx, ctx.q_compress, ctx.q_spline, ...
            "Compressing", fig );           % 压缩后的 B 样条曲线
        messagePrompt();
        pause( 0.5 );
    end

    % 生成采样器文件（可选，用于 PR2 机器人实时采样）
    if( CreateFileForSampler )
        fileName = "PR2/sampler/dome.csv";
        resample4sampler( ctx, fileName );
    end

    % =====================================================================
    % 重采样：将 LP 优化结果（参数域）转换为均匀时间步的轨迹（时间域）
    % 输出格式：[t, u, v_norm, v, cf, r_1...r_N, a_1...a_N, j_1...j_N, ...]
    % =====================================================================
    if( ctx.q_opt.isempty ), error("Queue empty before resampling"); end
    fileName = '.tmp.csv';                   % 临时 CSV 文件
    resample2file( ctx, fileName );          % 按 dt=1ms 重采样，写入 CSV
    ctx.q_opt.delete();                      % 释放优化结果队列内存

    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance.print(); % 打印重采样调试信息
    end

    % 读取重采样结果（每行一个时间步）
    res = readmatrix( fileName );

    if( DeleteCSVFileAfterResampling )
        delete( fileName );
    end

    % =====================================================================
    % 分析与可视化
    % =====================================================================

    % 解析 CSV 列索引（进给率列、加速度列、跃度列等）
    [res_struct, indFeed, indAcc, indJerk, indRPiece] = get_res_struct( ...
        res, ctx.cfg.maskTot );

    % 验证约束满足性和时间最优性（打印百分比报告）
    analyse_optimality( res, indFeed, indAcc, indJerk, ctx.cfg.dt );

    % 绘制时间域轨迹（速度、加速度、跃度曲线）
    plotTrajectories( ctx, res_struct );

    % 绘制各轴位置/速度/加速度/跃度指令
    plotAxisCommands( ctx, res_struct );

    % 保存所有图表和运行数据到文件夹
    saveResults( sourceFileName );

catch ME
    DestroyContext(ctx);
    error( '%s\n%s\n%s\n', ME.message, "File name : " + ME.stack(1).name, ...
                           "Line : " + ME.stack(1).line );
end

% 释放所有队列的外部内存（C++ 侧分配的堆内存）
DestroyContext(ctx);

diary off;


%-------------------------------------------------------------------------%
%% 局部工具函数
%-------------------------------------------------------------------------%

function [status] = check_constraints( tol, feed, a, j )
% 检查优化结果是否满足速度/加速度/跃度约束（超出则在对应位置置位）
status = 0;
if ( feed > 1 + tol.v_tol ),   bitset(status, 1); end % 位 1：速度超限
if any( a > 1 + tol.a_tol ),   bitset(status, 2); end % 位 2：加速度超限
if any( j > 1 + tol.j_tol ),   bitset(status, 3); end % 位 3：跃度超限
end

function [t_opt] = check_time_optimality( tol, feed, a, j )
% check_time_optimality : 逐时间步判断轨迹是否"时间最优"
%
% 时间最优的判断准则：
%   若某时刻至少有一个约束（速度/加速度/跃度）处于饱和状态（接近上限），
%   则认为该时刻"时间最优"——机器正在被充分利用。
%   若某时刻所有约束均远离上限，说明该时刻速度还有提升空间，轨迹非最优。
%
% 输入（均为归一化值，1.0 = 达到约束上限）：
%   tol  : 容差结构体
%          .tol_opt_v : 速度接近上限的判定阈值（如 0.05 表示 v > 0.95*v_max）
%          .tol_opt_a : 加速度接近上限的判定阈值
%          .tol_opt_j : 跃度接近上限的判定阈值
%   feed : [N×1]   归一化进给率 v/v_programmed（来自 CSV 第 3 列）
%   a    : [N×轴数] 归一化加速度 a_i/a_max_i（各轴）
%   j    : [N×轴数] 归一化跃度 j_i/j_max_i（各轴）
%
% 输出：
%   t_opt : [N×4] 布尔矩阵，每行对应一个时间步
%           第 1 列：速度约束是否饱和
%           第 2 列：任意轴加速度约束是否饱和
%           第 3 列：任意轴跃度约束是否饱和
%           第 4 列：以上三者中任意一项饱和（= 该时刻时间最优）

N = length( feed );
t_opt = zeros(N, 4); % 初始化为全 0（全部未饱和）

% 列 1：速度是否接近上限
%   feed > 1 - tol_opt_v 等价于 v > (1 - tol) * v_max
%   即进给率进入 [1-tol, 1] 区间，视为速度约束饱和
t_opt( : ,1 ) = ( feed > 1 - tol.tol_opt_v );

% 列 2：任意轴加速度是否接近上限
%   a 为 [N×轴数] 矩阵，any(..., 2) 沿列方向聚合（即按行取 any）
%   只要有一个轴满足 a_i > 1 - tol_opt_a，该时间步的加速度约束即饱和
t_opt( : ,2 ) = any( a > 1 - tol.tol_opt_a, 2);

% 列 3：任意轴跃度是否接近上限（逻辑同上）
t_opt( :, 3 ) = any( j > 1 - tol.tol_opt_j, 2);

% 列 4：该时刻是否"时间最优"——速度、加速度、跃度三者中至少一项饱和
%   any(..., 2) 沿列方向聚合前三列
t_opt( :, 4 ) = any( t_opt( :, 1:3 ) ,2 );

end

function [] = analyse_optimality( res, indFeed, indAcc, indJerk, dt )
% 从验证参数文件加载容差，然后打印约束满足和时间最优性统计
PfileName = pwd + "/Validate_OpenCN/params.m";
run(PfileName); % 加载验证参数（vmax_norm_tol、amax_xyz_tol 等）

tol.v_tol       = vmax_norm_tol;
tol.a_tol       = amax_xyz_tol;
tol.j_tol       = jmax_xyz_tol;
tol.tol_opt_v   = tol_opt_vnorm;
tol.tol_opt_a   = tol_opt_a;
tol.tol_opt_j   = tol_opt_j;
tol.TOpt_tol    = TOpt_tol;

status     = check_constraints( tol, res( :, indFeed ), ...
                                     res( :, indAcc ), ...
                                     res( :, indJerk ) );
disp( optSolStatus2String( status ) ); % 打印约束状态（成功或哪项超限）

t_opt_res  = check_time_optimality( tol, res( :, indFeed ), ...
                                         res( :, indAcc ), ...
                                         res( :, indJerk ) );

% 总加工时间 = 最后一行时间步索引 × dt
disp( "Machining time : " + res(end, 1) * dt );

% 时间最优性百分比 = 处于约束边界的时间步数 / 总时间步数
disp( "Optimality : "                + sum( t_opt_res(:, end) ) / ...
    res(end, 1) * 100 + "[%]" );
disp( "Optimality feedrate : "       + sum( t_opt_res(:, 1) ) / ...
    res(end, 1) * 100 + "[%]" );
disp( "Optimality acceleration : "   + sum( t_opt_res(:, 2) ) / ...
    res(end, 1) * 100 + "[%]" );
disp( "Optimality jerk : "           + sum( t_opt_res(:, 3) ) / ...
    res(end, 1) * 100 + "[%]" );
end

function [res_struct, indFeed, indAcc, indJerk, indRPiece] = ...
    get_res_struct( res, mask )
% 解析重采样 CSV 的列索引，转换为命名结构体
%
% CSV 列布局（mask 决定有多少激活轴 N）：
%   列 1  : 时间步索引（整数，乘以 dt 得秒）
%   列 2  : 参数 u（归一化弧长）
%   列 3  : 归一化进给率 v_norm（v / v_programmed）
%   列 4  : 速度标量（mm/s）
%   列 5  : 编程进给率（mm/s）
%   列 6 ~ 5+N  : 各轴位置 r（mm 或 rad）
%   列 6+N ~ 5+2N: 各轴加速度 a（mm/s² 或 rad/s²）
%   列 6+2N ~ 5+3N: 各轴跃度 j（mm/s³ 或 rad/s³）
%   列 6+3N ~ 5+4N: 各轴机床坐标位置 rpiece（含运动学变换）

ind         = 1 : sum( mask );  % 激活轴的索引序列（1~N）
indFeed     = 3;                % 归一化进给率列
indR        = 5                 + ind;    % 位置列范围
indAcc      = indR( end )       + ind;    % 加速度列范围
indJerk     = indAcc( end )     + ind;    % 跃度列范围
indRPiece   = indJerk( end )    + ind;    % 机床坐标列范围

res_struct.tvec       = res( :, 1 );            % 时间步向量
res_struct.uvec       = res( :, 2 );            % 参数 u 向量
res_struct.vvec       = res( :, 3 ) .* res( :, 4 ) * 60; % 实际速度（mm/min）
res_struct.fvec       = res( :, 4 ) * 60;       % 速度标量（mm/min）
res_struct.cfvec      = res( :, 5 ) * 60;       % 编程进给率（mm/min）
res_struct.pvec       = res( :, indR );          % 各轴位置
res_struct.avec       = res( :, indAcc );        % 各轴加速度
res_struct.jvec       = res( :, indJerk );       % 各轴跃度
res_struct.rpiece     = res( :, indRPiece );     % 机床坐标位置
end

function [msg] = optSolStatus2String(status)
% 将约束检查 status（位编码）翻译为可读字符串
msg = "Optimization successed !"; % 默认成功
constr = bitand(status, 7);       % 取低 3 位（速度/加速度/跃度）
if constr ~= 0
    if bitget(constr, 1), msg = 'V max exceeded!.\n';
    elseif bitget(constr, 2), msg = 'A max exceeded!.\n';
    elseif bitget(constr, 3), msg = 'J max exceeded!.\n';
    end
end
if bitand(status, 8) ~= 0
    msg = 'Not time optimal!\n'; % 位 4：时间非最优
end
end

function [] = setupLogs( logFileName )
% 初始化日志：创建 logs/ 目录，开启 diary，配置调试级别
mkdir logs;
diary ([logFileName, '_', ...
    datestr(now,'yyyy_mm_dd_HH_MM_SS'), ...
    '.txt']);

% 全局调试配置（0 = 关闭，非零 = 开启对应级别）
global DebugConfig
DebugConfig = 0;

% 启用的调试级别（通过 EnableDebugLog 设置 DebugConfig 中的对应位）
EnableDebugLog(DebugCfg.OptimProgress);  % 优化进度
EnableDebugLog(DebugCfg.Validate);       % 验证信息
EnableDebugLog(DebugCfg.FeedratePlanning); % 进给率规划细节
EnableDebugLog(DebugCfg.Error);          % 错误信息
EnableDebugLog(DebugCfg.Plots);          % 绘图信息
end

function plotAxisCommands( ctx, res_struct )
% 绘制各轴位置/速度/加速度/跃度时序曲线
N = double( ctx.cfg.NumberAxis );
time = res_struct.tvec;
axisNameGen = {"x", "y", "z", "a", "b", "c"};
axisUnitGen = {"mm", "mm", "mm", "rad", "rad", "rad"};
axisName    = axisNameGen(1, ctx.cfg.maskTot); % 按激活轴过滤轴名
axisUnit    = axisUnitGen(1, ctx.cfg.maskTot); % 按激活轴过滤单位

% 图 1：各轴位置
figure("Name","Axis Commands : Position");
for j = 1 : N
    subplot(N, 1, j);
    plot(time, res_struct.pvec(:, j)); grid on;
    ylabel( axisName{ j } + " in " + axisUnit{ j } );
end
xlabel("Time in [s]");

% 图 2：编程进给率（目标）vs 实际进给率（跟踪误差可视化）
plot_name = "Axis Commands : Computed feedrate"; figure("Name",plot_name);
plot(time, res_struct.cfvec, 'r', 'LineWidth', 3); hold on;
plot(time, res_struct.fvec, 'b'); grid on;
title( plot_name );
ylabel( "Feedrate in [mm/s]" ); xlabel( "Time in [s]" );
legend( "Feedrate target", "Actual Feedrate");

% 图 3：各轴归一化速度（v_i / v_max_i，超过 1 则违约）
v       = diff(res_struct.pvec) / ctx.cfg.dt;       % 有限差分求速度
v_norm  = v ./ ctx.cfg.vmax( ctx.cfg.maskTot );     % 归一化（除以上限）
plot_name = "Axis Commands : Normalized Velocity"; figure("Name",plot_name);
for j = 1 : N
    subplot(N, 1, j);
    plot(time(2:end), v_norm(:,j)); grid on;
    ylabel( "v_" + axisName{ j } + " in " + axisUnit{ j } + "/s");
    if( j == 1 ), title( plot_name ), end
end
xlabel("Time in [s]");

% 图 4：各轴归一化加速度（a_i / a_max_i）
a       = diff(v) / ctx.cfg.dt;
a_norm  = a ./ ctx.cfg.amax( ctx.cfg.maskTot );
plot_name = "Axis Commands : Normalized Acceleration"; figure("Name",plot_name);
for j = 1 : N
    subplot(N, 1, j);
    plot(time(3:end), a_norm(:,j)); grid on;
    ylabel( "a_" + axisName{ j } + " in " + axisUnit{ j } + "/s^2");
    if( j == 1 ), title( plot_name ), end
end
xlabel("Time in [s]");

% 图 5：各轴归一化跃度（j_i / j_max_i）
jerk    = diff(a) / ctx.cfg.dt;
j_norm  = jerk ./ ctx.cfg.jmax( ctx.cfg.maskTot );
plot_name = "Axis Commands : Normalized Jerk"; figure("Name",plot_name);
for j = 1 : N
    subplot(N, 1, j);
    plot(time(4:end), j_norm(:,j)); grid on;
    ylabel( "j_" + axisName{ j } + " in " + axisUnit{ j } + "/s^3");
    if( j == 1 ), title( plot_name ), end
end
xlabel("Time in [s]");
end
