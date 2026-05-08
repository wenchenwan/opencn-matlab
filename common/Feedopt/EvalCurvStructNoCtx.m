function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
%#codegen
% EvalCurvStructNoCtx : 在一组局部参数点 u_vec 处求曲线的位置和各阶导数
%
% 这是整个求值系统的核心函数，完成两件事：
%   1. 把局部参数 u_vec ∈ [0,1] → 全局参数 u_g = a*u + b（参数窗口映射）
%   2. 按曲线类型分支调用底层求值函数（Line/Helix/TransP5/Spline）
%   3. 对导数施加链式法则补偿（r1D × a，r2D × a²，r3D × a³）
%
% 参数映射原理（a_param / b_param）：
%   每段曲线在全局参数空间 [b, b+a] 上定义，局部参数 u_l ∈ [0,1] 通过
%       u_g = a_param × u_l + b_param
%   映射到全局参数，再交给底层函数求值。
%   截取后的子段 a_param < 1，b_param > 0，不需要改变底层几何数据。
%
% 链式法则（导数缩放）：
%   底层函数返回的是对全局参数 u_g 的导数 d/du_g。
%   因为 u_g = a·u_l + b，故 du_g/du_l = a，所以：
%       dr/du_l    = a  × dr/du_g       （一阶导 × a）
%       d²r/du_l²  = a² × d²r/du_g²    （二阶导 × a²）
%       d³r/du_l³  = a³ × d³r/du_g³    （三阶导 × a³）
%
% Helix 特殊处理：
%   笛卡尔轴（X/Y/Z）用 EvalHelix（圆弧公式）
%   旋转轴（B/C 等）用 EvalLine（旋转轴在圆弧过程中线性变化）
%
% Inputs :
%   cfg    : 配置结构体（含 NumberAxis / indCart / indRot / mask 等）
%   curv   : 曲线结构体（含 Type / a_param / b_param / R0 / R1 等）
%   spline : B 样条结构体（Type=Spline 时使用，其他类型传入默认值）
%   u_vec  : 局部参数向量（∈ [0,1]，行或列向量均可）
%
% Outputs :
%   r0D : [NumberAxis × N] 曲线位置（N = numel(u_vec)）
%   r1D : [NumberAxis × N] 一阶参数导数  dr/du_l
%   r2D : [NumberAxis × N] 二阶参数导数  d²r/du_l²
%   r3D : [NumberAxis × N] 三阶参数导数  d³r/du_l³
%

coder.inline("never");

ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );

Type = curv.Info.Type;
N    = numel( u_vec );
M    = cfg.NumberAxis;

% 预分配输出（默认零，未激活轴保持 0）
r0D = zeros( M, N );
r1D = r0D; r2D = r0D; r3D = r0D;

a = curv.a_param;   % 参数窗口宽度（截取子段时 < 1）
b = curv.b_param;   % 参数窗口起点（截取子段时 > 0）

% 将局部参数 u_vec ∈ [0,1] 映射到全局参数 u_g ∈ [b, b+a]
u_vec_tilda = a * u_vec + b;

indC     = cfg.indCart;   % 笛卡尔轴的索引（X/Y/Z）
indR     = cfg.indRot;    % 旋转轴的索引（B/C 等）
maskTot  = cfg.maskTot;   % 全轴掩码
maskRot  = cfg.maskRot;   % 旋转轴掩码
maskCart = cfg.maskCart;  % 笛卡尔轴掩码

switch Type
    case CurveType.Line
        % 直线：r(u) = P0*(1-u) + P1*u，所有激活轴统一处理
        [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );

    case CurveType.Helix
        % 圆弧/螺旋线：笛卡尔轴用圆弧公式，旋转轴线性插值
        if( cfg.NCart > 0 )
            [r0D(indC,:), r1D(indC,:), r2D(indC,:), r3D(indC,:)] = ...
                EvalHelix( curv, u_vec_tilda, maskCart );
        end
        if( cfg.NRot > 0 )
            % 五轴机：圆弧运动时旋转轴同步线性变化（插补同步）
            [r0D(indR,:), r1D(indR,:), r2D(indR,:), r3D(indR,:)] = ...
                EvalLine( curv, u_vec_tilda, maskRot );
        end

    case CurveType.TransP5
        % 五次多项式过渡曲线：逐阶对系数求导再求值
        [r0D, r1D, r2D, r3D] = EvalTransP5( curv, u_vec_tilda, maskTot );

    case CurveType.Spline
        % B 样条：调用 GSL 库（通过 bspline_eval_vec 包装）
        [r0D, r1D, r2D, r3D] = EvalBSpline( spline, u_vec_tilda );

    otherwise
        ocn_assert( false, "Unknown Curve Type for Eval...", mfilename );
end

% ── 链式法则补偿：底层返回 d/du_g，转换为 d/du_l ──────────────────────
% u_g = a·u_l + b → du_g/du_l = a（常数），由链式法则：
%   dr/du_l = a · dr/du_g   → 乘 a
%   d²r/du_l² = a² · d²r/du_g² → 乘 a²
%   d³r/du_l³ = a³ · d³r/du_g³ → 乘 a³
r1D = a    .* r1D;
r2D = a^2  .* r2D;
r3D = a^3  .* r3D;

end
