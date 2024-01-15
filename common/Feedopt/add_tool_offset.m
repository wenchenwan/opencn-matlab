function [ CurvStruct ] = add_tool_offset( CurvStruct, indCart, prev_tool ) 
%#codegen
% add_tool_offset : Add the tool offset to the curve structure.
% 
% Inputs :
% CurvStruct    : Curv structure
% indCart       : Index carthesien
% prev_tool     : Previous tool
% 
% Outputs:
% CurvStruct    : Curv structure

if( ~CurvStruct.Info.TRAFO )
    prev_off = [prev_tool.offset.x,prev_tool.offset.y, prev_tool.offset.z]; 
    off = [CurvStruct.tool.offset.x, ...
           CurvStruct.tool.offset.y, ...
           CurvStruct.tool.offset.z];
    CurvStruct.R0( indCart ) = ...
        CurvStruct.R0( indCart ) + prev_off( : );
    CurvStruct.R1( indCart ) = ...
        CurvStruct.R1( indCart ) + off( : );
    if ( CurvStruct.Info.Type == CurveType.Helix )
        CurvStruct.CorrectedHelixCenter = CurvStruct.CorrectedHelixCenter + off( : );
    end
end
end
