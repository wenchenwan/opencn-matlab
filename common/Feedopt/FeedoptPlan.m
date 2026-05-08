function [ ctx, optimized, opt_struct ] = FeedoptPlan( ctx )
%#codegen
% FeedoptPlan : 进给率优化有限状态机（FSM）单步执行函数
% 每次调用推进一个状态，由 FeedoptPlanRun 循环驱动
%
% Inputs :
%   ctx        : 计算链上下文
% Outputs :
%   ctx        : 更新后的上下文（op 字段指向下一个状态）
%   optimized  : 本次调用是否产出了一个优化好的曲线段
%   opt_struct : 优化好的曲线结构体（仅 Opt 阶段有意义）
%

optimized = false;         % 默认本次未产出优化结果
opt_struct = constrCurvStructType; % 默认空曲线结构体

% 每次进入前确认错误码为 NoError，保证错误已在调用方处理
ocn_assert( ctx.errcode == FeedoptPlanError.NoError, ...
    "FeedoptPlan: error code was not handled...", mfilename );

switch ctx.op

    %----------------------------------------------------------------------
    % 状态 0 → 1：初始化完成，直接跳转到 G-code 解析
    %----------------------------------------------------------------------
    case Fopt.Init
        ctx.op = Fopt.GCode;

    %----------------------------------------------------------------------
    % 状态 1：解析 G-code 文件，将每条指令转换为 CurvStruct，填入 q_gcode
    %----------------------------------------------------------------------
    case Fopt.GCode
        ctx.k0      = int32( 1 );           % 重置曲线计数器
        % 第一步：打开/加载 G-code 文件（Load 命令）
        status      = ReadGCode( ctx.cfg, ReadGCodeCmd.Load, ctx.cfg.source );
        CurvStruct  = opt_struct;
        CurvStruct.Info.Type = CurveType.None;
        DebugLog( DebugCfg.Validate, 'Reading G-code...\n' );

        % 第二步：逐条读取 G-code（Read 命令），直到解释器退出
        while status < ReadGCodeError.InterpNotOpen
            % 将上一次读到的有效曲线推入队列
            if( CurvStruct.Info.Type ~= CurveType.None )
                ctx.q_gcode.push( CurvStruct );
                ctx.k0 = ctx.k0 + 1;
            end

            if( status == ReadGCodeError.InterpExit ), break; end

            % 读取下一条 G-code 指令
            [ status, CurvStruct ] = ReadGCode( ctx.cfg, ReadGCodeCmd.Read, ...
                ctx.cfg.source );

            if( CurvStruct.Info.Type ~= CurveType.None )
                if( ctx.q_gcode.isempty )
                    prev_tool = constrToolStructType;
                else
                    prev_tool = ctx.q_gcode.rget(1).tool; % 取队列末尾的刀具信息

                    % 检测换刀：若当前曲线刀具与上一曲线不同，设置零速标记
                    if( ~toolIsEqual(prev_tool, CurvStruct.tool ) )
                        curv1 = ctx.q_gcode.rget(1);
                        % 换刀前最后一段：需要停止（ZZ 或 NZ）
                        if( isAZeroStart(curv1) )
                            curv1.Info.zspdmode = ZSpdMode.ZZ;
                        else
                            curv1.Info.zspdmode = ZSpdMode.NZ;
                        end
                        ctx.q_gcode.set(ctx.q_gcode.size, curv1);

                        % 换刀后第一段：需要从零速启动（ZZ 或 ZN）
                        if( isAZeroEnd(CurvStruct) )
                            CurvStruct.Info.zspdmode = ZSpdMode.ZZ;
                        else
                            CurvStruct.Info.zspdmode = ZSpdMode.ZN;
                        end
                    end
                end

                % 应用刀具偏移（工具长度补偿）到曲线坐标
                [CurvStruct] = add_tool_offset( CurvStruct, ...
                    ctx.cfg.indCart, prev_tool );
                % 旋转轴单位转换：度 → 弧度（轴索引 4 及以后为旋转轴）
                CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
                CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );

                % 将 NaN（未指定轴）替换为 0，保证后续计算不出现 NaN
                for j = 1 : StructTypeName.NumberAxisMax
                    if isnan( CurvStruct.R0( j ) ), CurvStruct.R0( j ) = 0; end
                    if isnan( CurvStruct.R1( j ) ), CurvStruct.R1( j ) = 0; end
                end

                % 断言：进给率必须为正值
                ocn_assert( CurvStruct.Info.FeedRate > 0.0, ...
                    "Feedrate is not valide...", mfilename );
            end
        end

        % 解析结束后 q_gcode 不能为空
        ocn_assert( ~ctx.q_gcode.isempty(), "Gcode queue is empty", mfilename );

        % 处理最后一个曲线段的零速标记
        last = ctx.q_gcode.rget(1);
        if( isAZeroStart(last) )
            last.Info.zspdmode = ZSpdMode.ZZ;
        else
            last.Info.zspdmode = ZSpdMode.NZ; % 最后一段必须以零速结束
        end
        ctx.q_gcode.set( ctx.q_gcode.size, last );

        % 验证队列合法性（几何、零速模式、参数化）
        ctx = assert_queue( ctx, ctx.op, ctx.q_gcode );
        ctx.op = Fopt.Check; % 跳转到下一状态

    %----------------------------------------------------------------------
    % 状态 2：几何检查（尖点检测）
    %----------------------------------------------------------------------
    case Fopt.Check
        if ~ctx.cfg.Cusp.Skip
            ctx = CheckCurvStructs( ctx ); % 检测 q_gcode 中的尖点，分割超阈值处
        end
        ctx = assert_queue( ctx, ctx.op, ctx.q_gcode );
        ctx.op  = Fopt.Compress; % 跳转到压缩阶段

    %----------------------------------------------------------------------
    % 状态 3：曲线压缩（合并共线线段，拟合 B 样条）
    %----------------------------------------------------------------------
    case Fopt.Compress
        if ctx.cfg.Compressing.Skip
            % 跳过压缩：直接将 q_gcode 复制到 q_compress
            for j = 1 : ctx.q_gcode.size
                ctx.q_compress.push( ctx.q_gcode.get( j ) );
            end
        else
            ctx = compressCurvStructs(ctx); % 执行 Lee 算法 B 样条拟合
        end
        ctx = assert_queue( ctx, ctx.op, ctx.q_compress );
        ctx.op = Fopt.Smooth;
        % 释放 q_gcode 内存（不再需要原始 G-code 队列）
        if( ctx.cfg.ReleaseMemoryOfTheQueues ), ctx.q_gcode.delete(); end

    %----------------------------------------------------------------------
    % 状态 4：平滑过渡（在曲线连接处插入 5 次多项式过渡段）
    %----------------------------------------------------------------------
    case Fopt.Smooth
        ctx = smoothCurvStructs(ctx); % 插入 TransP5 过渡曲线，保证 G2 连续
        ctx.op = Fopt.Split;
        ctx = assert_queue( ctx, ctx.op, ctx.q_smooth );
        if( ctx.cfg.ReleaseMemoryOfTheQueues ), ctx.q_compress.delete(); end

    %----------------------------------------------------------------------
    % 状态 5：曲线分割（将长曲线切成短段，适配优化窗口）
    %----------------------------------------------------------------------
    case Fopt.Split
        ctx     = splitQueue( ctx );   % 按 LSplit / LSplitZero 分割
        ctx.op  = Fopt.Opt;
        if( coder.target( 'MATLAB' ) )
            DebugOptimization.getInstance.reset; % 重置优化调试对象
        end
        ctx = assert_queue( ctx, ctx.op, ctx.q_split );
        if( ctx.cfg.ReleaseMemoryOfTheQueues ), ctx.q_smooth.delete(); end

    %----------------------------------------------------------------------
    % 状态 6：LP 优化（滑动窗口进给率规划，每次调用处理一个窗口）
    % 注意：此状态在 Opt 完成前会被多次重入，每次产出一个优化段
    %----------------------------------------------------------------------
    case Fopt.Opt
        if( ctx.q_opt.size() == 0 ), ctx.k0 = int32( 1 ); end
        % 调用进给率规划：对当前窗口求解 LP，将结果推入 q_opt
        [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx );
        if optimized
            ctx.go_next = true;           % 下次调用前进到下一个曲线段
            ctx.q_opt.push( opt_struct ); % 将优化好的段写入输出队列
        end
        if( quit ), return; end           % q_split 处理完毕，退出 Opt 状态

    %----------------------------------------------------------------------
    % 终止状态
    %----------------------------------------------------------------------
    case Fopt.Finished
        ctx.op = Fopt.Finished;

    otherwise
        DebugLog(DebugCfg.Global, 'FEEDOPT: WRONG STATE\n')
        ctx.op = Fopt.Finished;

end

end

%--------------------------------------------------------------------------
% 辅助函数：验证队列的三项合法性
%--------------------------------------------------------------------------
function [ ctx ] = assert_queue( ctx, op, queue)
msg = string( op );
% 验证 1：队列中所有曲线的几何参数合法（长度、起终点匹配等）
ocn_assert( checkGeometry( queue ), ...
    msg + " - Check geometry failed...", mfilename );

% 验证 2：零速模式（ZZ/ZN/NZ/NN）在相邻曲线间的传递关系合法
[ isValid, ctx ] = checkZSpdmode( ctx, queue );
ocn_assert( isValid, ...
    msg + " - Check zspdmode failed...", mfilename );

% 验证 3：曲线参数化（a_param/b_param）合法，u 范围在 [0,1] 内
isValid = checkParametrisationQueue( queue );
ocn_assert( isValid, ...
    msg + " - Check parametrisation failed...", mfilename );
end
