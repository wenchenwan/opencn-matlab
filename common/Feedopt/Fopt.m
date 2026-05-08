classdef Fopt < int32
%#codegen
% Fopt : 进给率优化（Feedopt）有限状态机的状态枚举
% 继承自 int32，可在代码生成（coder）中使用
%
    enumeration
        Init(0)      % 初始状态，进入后立即跳转到 GCode
        GCode(1)     % G-code 解析阶段：读取 .ngc 文件 → 填充 q_gcode
        Check(2)     % 几何检查阶段：尖点检测、参数化验证
        Compress(3)  % 曲线压缩阶段：合并共线线段，拟合 B 样条 → 填充 q_compress
        Smooth(4)    % 平滑过渡阶段：在曲线连接处插入 5 次多项式过渡段 → 填充 q_smooth
        Split(5)     % 曲线分割阶段：将长曲线按长度分窗 → 填充 q_split
        Opt(6)       % LP 优化阶段：滑动窗口求解最优进给率 → 填充 q_opt
        Finished(67) % 终止状态（注意不是 7，避免与其他枚举值混淆）
    end

    methods(Static)  % C++ 代码生成选项，可以增加相应的命名空间前缀例如 Fopt_Init
        function value = addClassNameToEnumNames()
            % 代码生成时，在枚举名称前加上类名前缀（如 Fopt_Init）
            value = true;
        end
    end
end
