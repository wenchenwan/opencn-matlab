function [CurvStruct] = add_tool_offset( CurvStruct, indCart, prev_tool ) 
%#codegen
% Add the tool offset to the curve structure.
if( ~CurvStruct.Info.TRAFO )
    prev_off = [prev_tool.offset.x,prev_tool.offset.y, prev_tool.offset.z]; 
    off = [CurvStruct.Tool.offset.x, ...
           CurvStruct.Tool.offset.y, ...
           CurvStruct.Tool.offset.z];
    CurvStruct.R0( indCart ) = ...
        CurvStruct.R0( indCart ) + prev_off( : );
    CurvStruct.R1( indCart ) = ...
        CurvStruct.R1( indCart ) + off( : );
    if ( CurvStruct.Info.Type == CurveType.Helix )
        CurvStruct.CorrectedHelixCenter = CurvStruct.CorrectedHelixCenter + off( : );
    end
end
end