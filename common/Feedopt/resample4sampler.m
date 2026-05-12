function [] = resample4sampler( ctx, fileName )
% resample4sampler : 对整个优化队列 q_opt 执行重采样，将结果写入 CSV 文件供采样器使用。
%
% 重采样原理：
%   优化器输出的是参数域曲线（以弧长参数 u 描述），采样器需要等时间间隔
%   的离散位置点。本函数以固定时间步长 dt 逐步推进，调用 resampleCurv
%   在曲线参数域内插值，得到每个时刻的参数值 u 及其导数，再通过
%   calcRVAJfromU 换算为笛卡尔空间位置/速度/加速度/加加速度。
%
% 环形缓冲区机制（ring buffer）：
%   为避免每步都写磁盘，先将采样点攒满 sizeBuffer 行再批量写文件。
%   当 ind 超过 sizeBuffer 时触发一次写操作，ind 归 1 重新填充。
%   循环结束后再将缓冲区剩余数据（1:ind）写入文件。
%
% Inputs :
%       ctx :       当前计算链上下文（含 q_opt、q_spline、cfg 等）
%       fileName :  输出 CSV 文件路径

if ctx.q_opt.isempty(), return; end % 优化队列为空，无需采样，直接返回

% ── 初始化全局参数 ───────────────────────────────────────────────────────
N               = ctx.q_opt.size();              % 优化队列中的曲线总数
dt              = ctx.cfg.dt;                    % 采样时间步长（秒）
% 初始化重采样状态机：dt 决定积分步长，DefaultZeroStopCount 控制零速停留时长
% （零速停留：机床在速度降为 0 时需保持 DefaultZeroStopCount 个 dt 步才继续）
state           = ResampleState( dt, ctx.cfg.DefaultZeroStopCount );
countInPercent  = double( 0 );                   % 进度计数器（百分比，0~100）

% ── 初始化环形缓冲区 ─────────────────────────────────────────────────────
ind = 0;                                         % 缓冲区当前写入位置（1-based）
sizeBuffer = 1E4;                                % 缓冲区容量：每满 10000 行写一次文件
t = 0;                                           % 全局时间步计数（用于调试/统计）
buffer = zeros( sizeBuffer, ctx.cfg.NumberAxis );% 预分配缓冲区：[行数 × 轴数]
firstTime = true;                                % 标记是否第一次写文件（决定覆盖还是追加）

% ── 主循环：逐条曲线重采样 ──────────────────────────────────────────────
for k = 1 : N

    % 打印百分比进度（每增加 1% 才输出一次，避免刷屏）
    countInPercent = printAvancement( countInPercent, k, N, ctx.cfg.ENABLE_PRINT_MSG );

    % 从优化队列取第 k 条曲线，并取出其对应的 B 样条结构体
    Curv                        = ctx.q_opt.get( k );
    SplineCurv                  = ctx.q_spline.get( Curv.sp_index );
    % MaxConstantFeedRate 用于匀速段检测，当前版本强制置 0（禁用该优化路径）
    Curv.MaxConstantFeedRate    = 0;%GetCurvMaxFeedrate( ctx, Curv );

    % ── 内层循环：在当前曲线上逐时间步推进，直到曲线消耗完毕 ────────────
    % state.go_next = true 表示当前曲线的参数域已走完，可切换到下一条曲线
    while ~state.go_next

        % resampleCurv：在当前参数位置 state.u 处推进一个 dt 步
        %   输入：state（含当前 u, ud, udd, uddd），曲线系数 Curv.Coeff，常数加加速度
        %   输出：更新后的 state（含新的 u, ud, udd，以及 go_next / isOutsideRange 标志）
        %   go_next      = true  → 本曲线走完，退出 while，外层切换到 k+1
        %   isOutsideRange = true → 本步超出曲线范围，跳过写缓冲（不产生采样点）
         [ state ] = resampleCurv(state, ctx.Bl, ...
                                    Curv.Info.zspdmode, Curv.Coeff, ...
                                    Curv.ConstJerk, dt, ctx.cfg.GaussLegendreX, ...
                                    ctx.cfg.GaussLegendreW, ctx.cfg.ENABLE_PRINT_MSG );

        % 只在参数值未超出曲线范围时记录采样点
        if( ~state.isOutsideRange )
            t = t + 1;       % 全局时间步 +1
            ind = ind + 1;   % 缓冲区写指针 +1

            % ── 环形缓冲区满时批量写文件 ────────────────────────────────
            % ind 超过 sizeBuffer 说明缓冲区已满，触发一次写磁盘操作
            % 写完后将 ind 归 1，下一个采样点从缓冲区头部覆盖写入
            if( ind > sizeBuffer )
                ind = 1;
                firstTime = write2files( firstTime, buffer, fileName );
            end

            % calcRVAJfromU：根据参数值 u 及其各阶导数，计算笛卡尔空间坐标
            %   state.u   → 当前弧长参数值
            %   state.ud  → 参数对时间的一阶导（速度相关）
            %   state.udd → 参数对时间的二阶导（加速度相关）
            %   state.uddd→ 参数对时间的三阶导（加加速度相关）
            %   输出 r：各轴的位置/速度/加速度/加加速度（取决于 cfg 配置）
            [ r ]  = calcRVAJfromU( ctx, Curv, state.u, state.ud, ...
                                    state.udd, state.uddd );

            % 旋转轴单位换算：calcRVAJfromU 输出旋转轴角度单位为弧度，
            % 采样器需要角度（度），在写缓冲区前统一转换
            if( ctx.cfg.NRot > 0 )
                r( ctx.cfg.indRot ) = rad2deg( r( ctx.cfg.indRot ) );
            end

            % 将当前时步的各轴数据写入缓冲区对应行（行向量形式）
            buffer( ind, : ) = r( : ).';
        end
    end

    % ── 切换到下一条曲线前重置状态 ──────────────────────────────────────
    % 每条曲线的参数域从 0 开始，且超出范围标志和切换标志均需复位
    % （ud 保持连续性，由 resampleCurv 在跨曲线时自动处理；此处仅重置位置和标志）
    state.u              = 0;       % 新曲线参数从 0 起
    state.ud             = 0;       % 速度参数归零（下一曲线重新计算）
    state.isOutsideRange = false;   % 清除超出范围标志
    state.go_next        = false;   % 清除曲线完成标志，准备处理下一条
end

% ── 收尾：将缓冲区剩余数据写入文件 ─────────────────────────────────────
% 循环结束后 buffer(1:ind) 中存有最后一批未满 sizeBuffer 的采样点
write2files( firstTime, buffer( 1 : ind , : ) , fileName );

% 强制输出 100% 进度（避免因整除误差导致最后一步未打印）
printAvancement( 100 , N, N, ctx.cfg.ENABLE_PRINT_MSG );
end

% ============================================================================
% 辅助函数
% ============================================================================

function [countInPercent] = printAvancement(countInPercent, k, N, enablePrint)
% printAvancement : 打印采样进度（以整数百分比显示，每增加 1% 输出一次）
%
% 触发条件：floor(k*100/N) > countInPercent（百分比整数部分增加时才打印）
% 更新步长：max(1, floor(100/N)) — 防止 N 很大时步长为 0 导致不更新
    if( floor( k * 100 / N ) > countInPercent )
        if( coder.target('matlab') )
            % MATLAB 环境：使用调试日志输出（带日志级别过滤）
            DebugLog(DebugCfg.OptimProgress, '%3d [%%]\n', countInPercent);
        else
            % 代码生成环境：使用 ocn_print 输出（受 enablePrint 开关控制）
            ocn_print( enablePrint, '%3d [%%]\n', countInPercent, mfilename );
        end
        % 更新进度计数器；步长至少为 1，避免 N > 100 时卡死在同一百分比
        countInPercent = double( countInPercent + max( 1, floor( 100 / N ) ) );
    end

end

function [ firstTime ] = write2files( firstTime, A, fileName )
% write2files : 将矩阵 A 写入（或追加到）CSV 文件
%
% 写入策略：
%   - 第一次调用（firstTime = true）：覆盖写（不带 WriteMode 参数，默认覆盖）
%   - 后续调用（firstTime = false） ：追加写（WriteMode = 'append'）
% 分隔符统一使用空格（Delimiter = ' '），兼容采样器的文本解析格式

p_default = { 'Delimiter', ' ' };  % 基础参数：空格分隔

if( firstTime )
    param = p_default;    % 第一次：仅用默认参数（覆盖写）
    firstTime = false;    % 标记后续写操作改为追加模式
else
    % 追加模式：在基础参数后附加 WriteMode = 'append'
    param = [ p_default, { 'WriteMode', 'append' } ];
end

writematrix( A, fileName, param{ : } );

end
