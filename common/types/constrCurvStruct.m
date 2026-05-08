function [ CStrct ] = constrCurvStruct( gcodeInfoStruct, toolStruct, ...
                      spline, R0, R1, Cprim, delta, evec, theta, pitch, ...
                      CoeffP5, Coeff )
%#codegen
% constrCurvStruct : 构造曲线段结构体（CurvStruct）
% 这是整个流水线中最核心的数据载体，每条 G-code 指令
% 对应一个 CurvStruct，贯穿 q_gcode → q_compress → q_smooth → q_split → q_opt
%
% 字段用途说明：
%   Info    : G-code 元信息（曲线类型、进给率、主轴速度、零速标记等）
%   tool    : 刀具信息（偏移量、类型）
%   sp      : B 样条基（压缩后曲线使用）
%   R0/R1   : 曲线段起/终点的全轴位姿向量（[X,Y,Z,A,B,C]，单位 mm/rad）
%
%   --- 圆弧/螺旋线专用字段 ---
%   CorrectedHelixCenter (Cprim)  : 修正后的圆弧圆心（处理 G-code 精度误差）
%   delta   : 起终点半径差（螺旋线时非零）
%   evec    : 螺旋线轴方向单位向量
%   theta   : 螺旋线总旋转角（rad）
%   pitch   : 螺旋线每转线性位移（mm/rad）
%
%   --- 过渡曲线专用字段 ---
%   CoeffP5 : 5 次多项式过渡曲线系数
%
%   --- 优化结果字段 ---
%   Coeff   : LP 优化得到的 B 样条进给率系数（优化阶段写入）
%
%   --- 辅助字段 ---
%   sp_index      : 对应 q_spline 中 B 样条的索引
%   i_begin_sp    : 在 B 样条段中的起始索引
%   i_end_sp      : 在 B 样条段中的终止索引
%   index_smooth  : 在平滑后队列中的索引
%   UseConstJerk  : 是否使用恒跃度约束（零速段特殊处理）
%   ConstJerk     : 恒跃度值
%   a_param/b_param : 子参数化映射系数，u_local = a*u_global + b
%

coder.inline("never");

CStrct = struct(...
    'Info',                 gcodeInfoStruct, ...   % G-code 元信息（曲线类型、进给率等）
    'tool',                 toolStruct,...          % 刀具定义（偏移量）
    'sp',                   spline,...              % B 样条结构（压缩阶段填充）
    'R0',                   R0, ...                % 起点位姿 [X,Y,Z,A,B,C]（mm/rad）
    'R1',                   R1, ...                % 终点位姿 [X,Y,Z,A,B,C]（mm/rad）
    'CorrectedHelixCenter', Cprim, ...             % 修正圆心（圆弧/螺旋线用）
    'delta',                delta, ...             % 起终点半径差（螺旋线用）
    'evec',                 evec,...               % 螺旋线轴方向
    'theta',                theta,...              % 螺旋线总转角（rad）
    'pitch',                pitch,...              % 螺旋线螺距（mm/rad）
    'CoeffP5',              CoeffP5,...            % 5 次多项式过渡曲线系数
    'sp_index',             uint32(1),...          % 关联的 B 样条在 q_spline 中的索引
    'i_begin_sp',           int32(0),...           % B 样条段起始点索引
    'i_end_sp',             int32(0),...           % B 样条段终止点索引
    'index_smooth',         int32(0),...           % 平滑队列中的位置索引
    'UseConstJerk',         false,...              % 是否用恒跃度约束（零速段）
    'ConstJerk',            0,...                  % 恒跃度值（零速段减速计算）
    'Coeff',                Coeff,...              % LP 优化输出的进给率 B 样条系数
    'a_param',              1,...                  % 子参数化线性映射斜率（默认全段）
    'b_param',              0 ...                  % 子参数化线性映射偏移（默认全段）
    );

% 代码生成模式：声明可变尺寸字段和 C 结构体名称映射
if ~coder.target( 'MATLAB' )
    coder.varsize( 'CStrct.Coeff',      StructTypeName.dimCoeffOpt{ : } );
    coder.varsize( 'CStrct.R0' ,        StructTypeName.dimR{ : } );
    coder.varsize( 'CStrct.R1' ,        StructTypeName.dimR{ : } );
    coder.varsize( 'CStrct.CoeffP5' ,   StructTypeName.dimCoeffP5{ : } );

    coder.cstructname( CStrct.Info,     StructTypeName.GCodeInfo );
    coder.cstructname( CStrct.tool,     StructTypeName.Tool );
    coder.cstructname( CStrct.tool.offset, StructTypeName.Axes );
    coder.cstructname( CStrct.sp,       StructTypeName.Spline );
    coder.cstructname( CStrct.sp.Bl,    StructTypeName.BaseSpline );
    coder.cstructname( CStrct,          StructTypeName.Curve );
end
