classdef CurveType < int32
%#codegen
% CurveType : 曲线类型枚举——标识曲线段使用哪种几何参数化
%
% 【各类型说明】
%   None(0)    : 未初始化或无效曲线（禁止参与计算）
%   Line(1)    : 直线段
%                  r(u) = P0·(1-u) + P1·u，u ∈ [0,1]
%                  弧长均匀（‖r'‖ = const），弧长 = ‖P1-P0‖
%   Helix(2)   : 圆弧 / 螺旋线
%                  r(u) = C + cos(θu)·CP0 + sin(θu)·(ê×CP0) + (p/2π)·θu·ê
%                  弧长均匀（‖r'‖ = const），纯圆弧时 p=0
%   Spline(3)  : B 样条曲线（Lee 算法，4 次，C2 连续）
%                  用于拟合 GCode 中的样条指令（G05 连续路径）
%                  弧长非均匀，需数值积分（GL-5 Gauss-Legendre）
%   TransP5(4) : 五次多项式过渡曲线（G2 Hermite 插值结果）
%                  由 calcTransition 生成，长度极短（约 0.2mm）
%                  弧长非均匀，需中点积分法（TransP5LengthApprox）
%
% 【在代码中的用法】
%   switch curv.Info.Type
%     case CurveType.Line   → EvalLine
%     case CurveType.Helix  → EvalHelix（+EvalLine 旋转轴）
%     case CurveType.Spline → EvalBSpline
%     case CurveType.TransP5→ EvalTransP5
%   end
        enumeration
            None(0),     % 未初始化
            Line(1),     % 直线段
            Helix(2),    % 圆弧 / 螺旋线
            Spline(3),   % B 样条曲线
            TransP5(4)   % 五次多项式过渡曲线
        end

        methods(Static)
            function value = addClassNameToEnumNames()
                value = true;
            end
        end
end
