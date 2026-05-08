function [ CurvStruct ] = add_tool_offset( CurvStruct, indCart, prev_tool )
%#codegen
% add_tool_offset : 将刀具长度偏移量叠加到曲线起终点坐标上
%
% G-Code 以刀尖为基准编程，实际机床坐标需加上刀具偏移量（刀长补偿）。
% 起点 R0 使用上一把刀的偏移（保证与前段终点几何连续），
% 终点 R1 使用当前刀具的偏移。
% 5 轴联动（TRAFO=true）时由运动学模型统一处理，本函数不介入。
%
% Inputs :
%   CurvStruct : 当前曲线结构体（含 R0/R1 坐标及刀具信息）
%   indCart    : 笛卡尔轴在坐标向量中的索引（通常为 1:3，即 X/Y/Z）
%   prev_tool  : 上一段曲线所用刀具（提供起点偏移量）
%
% Outputs :
%   CurvStruct : 叠加偏移后的曲线结构体

if( ~CurvStruct.Info.TRAFO )
    % TRAFO=false：普通 3 轴，偏移量可直接叠加到笛卡尔坐标；
    % TRAFO=true ：5 轴联动，刀具方向随旋转轴变化，需经运动学变换补偿，
    %              由后续 ctx.kin.joint() 统一处理，此处跳过。

    % 提取上一把刀与当前刀的 XYZ 偏移量
    prev_off = [prev_tool.offset.x, prev_tool.offset.y, prev_tool.offset.z];
    off      = [CurvStruct.tool.offset.x, ...
                CurvStruct.tool.offset.y, ...
                CurvStruct.tool.offset.z];

    % 起点加上一把刀的偏移：起点在几何上与前段终点重合，须保持连续性
    CurvStruct.R0( indCart ) = CurvStruct.R0( indCart ) + prev_off( : );

    % 终点加当前刀的偏移
    CurvStruct.R1( indCart ) = CurvStruct.R1( indCart ) + off( : );

    % 螺旋线圆心也须随终点偏移量平移，否则圆弧几何形状会错位
    if ( CurvStruct.Info.Type == CurveType.Helix )
        CurvStruct.CorrectedHelixCenter = CurvStruct.CorrectedHelixCenter + off( : );
    end
end
end
