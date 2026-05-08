classdef TransitionResult < int32
    %#codegen
    % TransitionResult : 过渡曲线计算结果枚举
    %
    % calcTransition 尝试在两段曲线的连接点处插入 G2 Hermite 过渡曲线，
    % 并将计算结果以此枚举返回给 smoothCurvStructs 决策处理方式。
    %
    % 枚举值：
    %   Ok(0)        : 过渡曲线计算成功，可直接插入
    %   Collinear(1) : 两曲线在连接点处切向共线（已满足 G1），不需要过渡曲线
    %                  （此情况通常由 check_smoothness 中 G1 检查提前发现，
    %                   但 calcTransition 内部也可检测并返回此值）
    %   NoSolution(2): 无有效解——G2 Hermite 多项式方程组无正实根，
    %                  或过渡曲线长度超出两侧曲线长度的 1/2（曲率过大），
    %                  此时 smoothCurvStructs 退回到强制零速停顿
    %
    % 【在 smoothCurvStructs 中的处理逻辑】
    %   TransitionResult.Ok        → push curv1C, curvT；curv ← curv2C
    %   TransitionResult.Collinear → 理论上不会走到 calcTransition
    %   TransitionResult.NoSolution→ create_zero_end + add_zero_stop
    enumeration
        Ok( 0 ),             % Transition succeed
        Collinear( 1 ),      % No need of a transition, curves are colinear
        NoSolution( 2 )      % No solutions found...
    end

    methods( Static )
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end
