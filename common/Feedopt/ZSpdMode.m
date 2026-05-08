classdef ZSpdMode < int32
    %#codegen
    % ZSpdMode : 零速模式枚举——描述曲线段两端的速度约束类型
    %
    % 命名规则：首字母 = 起点，次字母 = 终点
    %   N = Normal（普通速度，由 LP 优化决定）
    %   Z = Zero  （零速，需要精确约束）
    %
    % 枚举值（int32 基类，可安全用于 codegen 生成的 C 代码）：
    %   NN(0) : 普通起始、普通终止（标准段，无零速约束）
    %   ZN(1) : 零速起始、普通终止（加速段，如出发点或停顿后恢复）
    %   NZ(2) : 普通起始、零速终止（减速段，如进入停顿点）
    %   ZZ(3) : 零速起始、零速终止（孤立短段，两端均需停顿）
    %
    % 【典型使用场景】
    %   - splitCurvStruct 调用 cutZeroStart/cutZeroEnd 后为子段设置此标记
    %   - smoothCurvStructs 中 create_zero_end 根据上下文设置零速模式
    %   - isAZeroStart / isAZeroEnd 读取此标记判断窗口边界
    %   - LP 优化的边界条件由 zspdmode 决定（v_0=0 还是 v_1=0）
    enumeration
        NN(0),   % Normal-Normal  : 两端均无零速约束
        ZN(1),   % Zero-Normal    : 起端为零速
        NZ(2),   % Normal-Zero    : 末端为零速
        ZZ(3)    % Zero-Zero      : 两端均为零速
    end

    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end
