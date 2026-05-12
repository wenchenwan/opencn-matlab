classdef ResampleStateClass
% ResampleStateClass : 重采样状态机，跨时间步和跨曲线传递积分状态。
%
% 设计动机：
%   重采样器以固定时间步长 dt 逐步推进。每一步结束时，需要将当前的
%   参数位置（u）及其各阶导数传递给下一步作为初始条件。当一条曲线
%   的参数域走完（u ≥ 1），还需通知外层循环切换到下一条曲线。
%   此外，在零速停留（机床速度降为 0 的位置）需要原地停留若干个 dt
%   步后才继续，stopCounter 负责计时。
%
% 状态转移概览：
%   正常推进：resampleCurv 每步更新 u, ud, udd, uddd
%             u < 1 → 继续当前曲线
%             u ≥ 1 → go_next = true，外层切换下一条曲线
%   零速停留：startZeroStopTime() 触发停留计时
%             decreaseStopCounter() 每步递减计数器
%             计数器归零 → isAStop=false, go_next=true, 切换下一曲线

    properties
        u               double  % 弧长参数值，范围 [0, 1]，对应曲线从起点到终点
        ud              double  % u 对时间的一阶导数（参数速度，与实际速度/弧长相关）
        udd             double  % u 对时间的二阶导数（参数加速度）
        uddd            double  % u 对时间的三阶导数（参数加加速度，jerk）
        dt              double  % 采样时间步长（秒），由外部传入，整个采样过程固定不变
        go_next         logical % true = 当前曲线已消耗完毕，通知外层切换到下一条曲线
        isOutsideRange  logical % true = 本时步的 u 超出 [0,1]，该步不产生有效采样点
        isAStop         logical % true = 当前处于零速停留状态（机床原地保持）
        stopCounter     int32   % 零速停留剩余步数，每调用一次 decreaseStopCounter 减 1
        zeroStopTime    int32   % 零速停留总步数（由配置 DefaultZeroStopCount 决定）
    end

    methods

        function [this] = ResampleStateClass(dt, zeroStopTime)
        % 构造函数：初始化采样时间步长和零速停留步数，其余状态重置为默认值
        %
        % Inputs:
        %   dt           : 采样时间步长（秒）
        %   zeroStopTime : 零速停留持续的时间步数（DefaultZeroStopCount）
            this.dt             = dt;
            this.zeroStopTime   = zeroStopTime;
            % 将参数位置和所有导数置零，标志位全部复位
            this.u              = 0;
            this.ud             = 0;
            this.udd            = 0;
            this.uddd           = 0;
            this.go_next        = false;
            this.isOutsideRange = false;
            this.isAStop        = false;
            this.stopCounter    = 0;
        end

        function [this] = setZeroStop(this, dt, zeroStopTime)
        % setZeroStop : 进入零速停留模式
        %
        % 调用时机：resampleCurv 检测到当前曲线末端为零速（ZSpdMode.NZ/ZZ），
        %   且 u 已推进到 1（曲线终点），需要原地停留若干步再切换下一曲线。
        %
        % 进入停留状态后的行为：
        %   - u 固定在 1（始终输出曲线终点位置，机床保持不动）
        %   - isAStop = true，resampleCurv 将调用 decreaseStopCounter 计时
        %   - stopCounter 倒计时，归零后 go_next=true，外层切换下一曲线
            this.dt             = dt;
            this.u              = 1;        % 停留在曲线终点（u=1）
            this.ud             = 0;        % 速度为零
            this.udd            = 0;        % 加速度为零
            this.uddd           = 0;        % 加加速度为零
            this.go_next        = false;    % 尚未完成停留，不切换
            this.isOutsideRange = false;    % u=1 在范围内，允许输出采样点
            this.isAStop        = true;     % 标记：当前处于零速停留
            this.stopCounter    = zeroStopTime; % 重置计数器为完整停留步数
            this.zeroStopTime   = zeroStopTime;
        end

        function [this] = setU(this, u, ud, udd, uddd )
        % setU : 批量更新参数值及其各阶导数（由 resampleCurv 在每步积分后调用）
            this.u      = u;
            this.ud     = ud;
            this.udd    = udd;
            this.uddd   = uddd;
        end

        function [u, ud, udd, uddd] = getU(this)
        % getU : 读取当前参数值及其各阶导数（供 resampleCurv 作为下一步积分初值）
            u       = this.u;
            ud      = this.ud;
            udd     = this.udd;
            uddd    = this.uddd;
        end

        function [this] = decreaseStopCounter(this)
        % decreaseStopCounter : 零速停留计时器递减一步
        %
        % 每个 dt 步调用一次，直到 stopCounter 降至 0：
        %   stopCounter > 0 : 继续停留，isAStop 保持 true，外层循环继续输出 u=1 的位置点
        %   stopCounter <= 0: 停留结束，清除 isAStop；设置 go_next=true 通知切换曲线；
        %                     设置 isOutsideRange=true 使本步不再产生采样点（避免多输出一个点）
            this.stopCounter    = this.stopCounter - 1;
            if( this.stopCounter <= 0 )
                this.isAStop        = false;  % 退出零速停留模式
                this.go_next        = true;   % 通知外层：切换到下一条曲线
                this.isOutsideRange = true;   % 本步不产生采样点（停留已结束）
            end
        end

        function [this] = startZeroStopTime( this )
        % startZeroStopTime : 以当前 dt 和 zeroStopTime 重新进入零速停留状态
        %
        % 便捷封装：内部复用 setZeroStop，无需外部再传入 dt 和 zeroStopTime 参数。
        % resampleCurv 在检测到零速边界时直接调用此方法触发停留。
            this = this.setZeroStop( this.dt, this.zeroStopTime );
        end

    end
end
