function remove_tool_offset( CurvStruct ) %#codegen
% Remove the tool offset to the curve structure.
if( ~CurvStruct.Info.TRAFO )
    off = [CurvStruct.tool.offset.x, ...
           CurvStruct.tool.offset.y, ...
           CurvStruct.tool.offset.z];
    CurvStruct.R0( cfg.indCart ) = ...
        CurvStruct.R0( cfg.indCart ) - off( : );
    CurvStruct.R1( cfg.indCart ) = ...
        CurvStruct.R1( cfg.indCart ) - off( : );
    if( CurvStruct.Info.Type == CurveType.Helix )
        CurvStruct.evec = CurvStruct.evec - off;
    end
end
end